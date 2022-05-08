// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 10/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <Windows.h>
#include <boost/format.hpp>
#include "SensorsDataLoader.h"
#include "Constants.h"
#include "exceptions/MemoryReadException.h"

namespace lhws {
    SensorsDataLoader::SensorsDataLoader() {
        loadMemMapSensors();
    }

    const std::vector<char> &SensorsDataLoader::getIndex() const {
        return index;
    }

    const std::vector<char> &SensorsDataLoader::getData() const {
        return data;
    }

    IndexFormat SensorsDataLoader::getIndexFormat() const {
        return indexFormat;
    }

    void SensorsDataLoader::loadMemMapSensors() {
        std::string sensorsFilename = SENSORS_FILENAME;
        std::string mutexName(SENSORS_MUTEX);

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
        auto updateInterval = fromBytes<int>(pBuf + 4);
        auto lastUpdate = fromBytes<long long>(pBuf + 8);
        metadata = Metadata(updateInterval, lastUpdate);
        int offset = 4 + metadataSize;
        int indexSize = fromBytes<int>(pBuf + offset);
        int indexOffset = fromBytes<int>(pBuf + offset + 4);
        indexFormat = static_cast<IndexFormat>(fromBytes<int>(pBuf + offset + 8));
        int dataSize = fromBytes<int>(pBuf + offset + 12);
        int dataOffset = fromBytes<int>(pBuf + offset + 16);
        int regionSize = static_cast<int>(memMapInfo.RegionSize);

        if (!isOffsetValid(regionSize, indexOffset, indexSize) || !isOffsetValid(regionSize, dataOffset, dataSize)) {
            ReleaseMutex(mutex);
            CloseHandle(mutex);
            UnmapViewOfFile(pBuf);
            CloseHandle(hMapFile);
            throw MemoryReadException("invalid index");
        }

        index.resize(indexSize);
        data.resize(dataSize);
        std::memcpy(index.data(), pBuf + indexOffset, indexSize);
        std::memcpy(data.data(), pBuf + dataOffset, dataSize);

        ReleaseMutex(mutex);
        CloseHandle(mutex);
        UnmapViewOfFile(pBuf);
        CloseHandle(hMapFile);
    }

    int SensorsDataLoader::getUpdateInterval() const {
        return metadata.getUpdateInterval();
    }

    long long SensorsDataLoader::getLastUpdate() const {
        return metadata.getLastUpdate();
    }

    Metadata SensorsDataLoader::getMetadata() const {
        return metadata;
    }
}