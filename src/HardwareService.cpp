// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 13/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <boost/stacktrace.hpp>
#include <boost/algorithm/string.hpp>

#ifdef DEBUGBUILD
#include <boost/exception/diagnostic_information.hpp>
#endif

#include <HardwareService.h>
#include "Constants.h"
#include "data/SensorsDataLoader.h"
#include "data/HwStatusLoader.h"
#include "data/SensorsParser.h"
#include "data/HwStatusParser.h"
#include "data/HardwareTreeLoader.h"
#include "data/HardwareTreeParser.h"
#include "exceptions/SensorNotFoundException.h"
#include "exceptions/HardwareNotFoundException.h"
#include "exceptions/SensorReadException.h"

using std::cerr;
using std::endl;

namespace lhws {
    std::vector<Hardware> HardwareService::getHardwareTree() {
        try {
            HardwareTreeLoader loader;
            HardwareTreeParser parser(loader);
            hwTreeMetadata = loader.getMetadata();

            return parser.parseHardwareTree();
        } catch (std::exception const &e) {
            if constexpr (ISDEBUG) { // NOLINT
                cerr << e.what() << boost::stacktrace::stacktrace() << endl;
            }
            throw SensorReadException("an error occurred while reading hardware sensor data", e.what());
        }
    }

    std::vector<IndexItem> HardwareService::getIndex() {
        try {
            SensorsDataLoader loader;
            SensorsParser parser(loader);
            sensorsMetadata = loader.getMetadata();
            return parser.parseIndex();
        } catch (std::exception const &e) {
            if constexpr (ISDEBUG) { // NOLINT
                cerr << e.what() << boost::stacktrace::stacktrace() << endl;
            }
            throw SensorReadException("an error occurred while reading sensor index", e.what());
        }
    }

    Sensor HardwareService::getSensorById(const std::string &identifier) {
        try {
            SensorsDataLoader loader;
            SensorsParser parser(loader);
            sensorsMetadata = loader.getMetadata();

            std::vector<IndexItem> idx = parser.parseIndex();

            for (auto const &i: idx) {
                if (boost::iequals(i.getIdentifier(), identifier)) {
                    return parser.parseSensor(i.getOffset(), i.getSize());
                }
            }
        } catch (std::exception const &e) {
            if constexpr (ISDEBUG) { // NOLINT
                cerr << e.what() << boost::stacktrace::stacktrace() << endl;
            }
            throw SensorReadException("an error occurred while reading sensor data", e.what());
        }

        throw SensorNotFoundException("sensor not found");
    }

    Sensor HardwareService::getSensorByName(const std::string &sensorName, const std::string &sensorType,
                                            const std::string &hardwareName) {
        try {
            SensorsDataLoader loader;
            SensorsParser parser(loader);
            sensorsMetadata = loader.getMetadata();

            std::vector<IndexItem> idx = parser.parseIndex();

            for (auto const &i: idx) {
                if (boost::iequals(i.getSensorName(), sensorName) && boost::iequals(i.getSensorType(), sensorType)
                    && boost::iequals(i.getHardwareName(), hardwareName)) {
                    return parser.parseSensor(i.getOffset(), i.getSize());
                }
            }
        } catch (std::exception const &e) {
            if constexpr (ISDEBUG) { // NOLINT
                cerr << e.what() << boost::stacktrace::stacktrace() << endl;
            }
            throw SensorReadException("an error occurred while reading sensor data", e.what());
        }

        throw SensorNotFoundException("sensor not found");
    }

    std::vector<SmartAttribute> HardwareService::getSmartAttributes(std::string const &hardwareName,
                                                                    std::string const &hardwareType) {
        try {
            std::vector<std::vector<SmartAttribute>> ret;
            HwStatusLoader loader;
            HwStatusParser parser(loader);
            hwStatusMetadata = loader.getMetadata();

            HwStatus s = parser.parseHwStatus(hardwareName, hardwareType);

            if (s.getHwStatusType() == HwStatusType::STORAGE_SMART_ATA) {
                return s.getStatusData<std::vector<SmartAttribute>>();
            }
        } catch (std::exception const &e) {
            if constexpr (ISDEBUG) { // NOLINT
                cerr << e.what() << boost::stacktrace::stacktrace() << endl;
            }
            throw SensorReadException("an error occurred while reading ata-smart data", e.what());
        }

        throw HardwareNotFoundException("hardware not found");
    }

    NvmeSmart HardwareService::getNvmeSmart(std::string const &hardwareName, std::string const &hardwareType) {
        try {
            HwStatusLoader loader;
            HwStatusParser parser(loader);
            hwStatusMetadata = loader.getMetadata();

            HwStatus s = parser.parseHwStatus(hardwareName, hardwareType);

            if (s.getHwStatusType() == HwStatusType::STORAGE_SMART_NVME) {
                return s.getStatusData<NvmeSmart>();
            }
        } catch (std::exception const &e) {
            if constexpr (ISDEBUG) { // NOLINT
                cerr << e.what() << boost::stacktrace::stacktrace() << endl;
            }
            throw SensorReadException("an error occurred while reading nvme-smart data", e.what());
        }

        throw HardwareNotFoundException("hardware not found");
    }

    const Metadata &HardwareService::getSensorsMetadata() const {
        return sensorsMetadata;
    }

    const Metadata &HardwareService::getHwStatusMetadata() const {
        return hwStatusMetadata;
    }

    const Metadata &HardwareService::getHwTreeMetadata() const {
        return hwTreeMetadata;
    }

}