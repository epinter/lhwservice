// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 21/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "HwStatusLoader.h"
#include <Windows.h>
#include <boost/format.hpp>
#include "Constants.h"
#include "models/Metadata.h"
#include "exceptions/MemoryReadException.h"

namespace lhws {
    HwStatusLoader::HwStatusLoader() {
        load();
    }

    void HwStatusLoader::load() {
        std::string sensorsFilename(HWSTATUS_FILENAME);
        std::string mutexName(HWSTATUS_MUTEX);

        // create mutex to avoid overwrite while we read
        auto mutex = OpenMutex(
                SYNCHRONIZE,              // dwDesiredAccess
                FALSE,             // bInheritHandle
                mutexName.c_str());
        if (mutex == nullptr) {
            std::string errorMessage = (boost::format("Error opening mutex: %1%.\n") % getSystemError()).str();
            throw MemoryReadException(errorMessage);
        }
        //acquire mutex so the service can wait for a short time while we read
        WaitForSingleObject(mutex, MUTEX_WAIT_MS);

        //open non-persisted memory mapped file
        auto hMapFile = (OpenFileMapping(
                FILE_MAP_READ,   // read access
                FALSE,                 // do not inherit the name
                sensorsFilename.c_str()));
        if (!hMapFile) {
            ReleaseMutex(mutex);
            CloseHandle(mutex);
            std::string errorMessage = (boost::format("Could not open file mapping object: %1%.\n") % getSystemError()).str();
            throw MemoryReadException(errorMessage);
        }

        //create view
        auto pBuf = static_cast<LPCSTR>(MapViewOfFile(hMapFile, // handle to map object
                                                      FILE_MAP_READ,  // read permission
                                                      0,
                                                      0,
                                                      0));
        if (!pBuf) {
            ReleaseMutex(mutex);
            CloseHandle(mutex);
            CloseHandle(hMapFile);
            std::string errorMessage = (boost::format("Could not map view of file: %1%.\n") % getSystemError()).str();
            throw MemoryReadException(errorMessage);
        }

        MEMORY_BASIC_INFORMATION memMapInfo;
        SIZE_T mbiSize = VirtualQuery(pBuf, &memMapInfo, sizeof(memMapInfo));
        if (!mbiSize) {
            ReleaseMutex(mutex);
            CloseHandle(mutex);
            UnmapViewOfFile(pBuf);
            CloseHandle(hMapFile);
            std::string errorMessage = (boost::format("Could not query memory map information: %1%.\n") % getSystemError()).str();
            throw MemoryReadException(errorMessage);
        }

        //read header from memory map file
        int metadataSize = fromBytes<int>(pBuf);
        int metadataBlockSize = 4 + metadataSize;
        auto updateInterval = fromBytes<int>(pBuf + 4);
        auto lastUpdate = fromBytes<long long>(pBuf + 8);
        metadata = Metadata(updateInterval, lastUpdate);

        int dataSize = fromBytes<int>(pBuf + metadataBlockSize);
        int regionSize = static_cast<int>(memMapInfo.RegionSize);

        if (dataSize <= 0 || dataSize >= regionSize) {
            ReleaseMutex(mutex);
            CloseHandle(mutex);
            UnmapViewOfFile(pBuf);
            CloseHandle(hMapFile);
            throw MemoryReadException("invalid data");
        }

        int offset = 4 + metadataBlockSize;

        while (offset < dataSize) {
            std::vector<char> d;
            int itemSize = fromBytes<int>(pBuf + offset);
            offset += sizeof(int);

            if (itemSize > dataSize) {
                ReleaseMutex(mutex);
                CloseHandle(mutex);
                UnmapViewOfFile(pBuf);
                CloseHandle(hMapFile);
                throw MemoryReadException("invalid item size");
            }
            d.resize(itemSize);
            std::memcpy(d.data(), pBuf + offset, itemSize);
            data.push_back(d);
            offset += itemSize; //skip 1 null byte between hwStatus data items
        }

        ReleaseMutex(mutex);
        CloseHandle(mutex);
        UnmapViewOfFile(pBuf);
        CloseHandle(hMapFile);
    }

    const std::vector<std::vector<char>> &HwStatusLoader::getData() const {
        return data;
    }

    int HwStatusLoader::getUpdateInterval() const {
        return metadata.getUpdateInterval();
    }

    long long HwStatusLoader::getLastUpdate() const {
        return metadata.getLastUpdate();
    }

    Metadata HwStatusLoader::getMetadata() const {
        return metadata;
    }
} // lhws