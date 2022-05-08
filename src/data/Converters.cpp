// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 14/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <boost/json/src.hpp>
#include "Converters.h"
#include "models/Sensor.h"
#include "models/Hardware.h"
#include "models/SensorValue.h"
#include "models/IndexItem.h"
#include "models/HwStatus.h"
#include "models/SmartAttribute.h"
#include "models/NvmeSmart.h"
#include "exceptions/JsonInvalidDataException.h"

namespace lhws {
    template<>
    Sensor Converters::fromJson<Sensor>(boost::json::value const &jv) {
        boost::json::object const &j = jv.as_object();
        try {
            Sensor s(
                    boost::json::value_to<std::string>(j.at("identifier").is_string() ? j.at("identifier") : ""),
                    boost::json::value_to<std::string>(j.at("name").is_string() ? j.at("name") : ""),
                    boost::json::value_to<std::string>(j.at("sensorType").is_string() ? j.at("sensorType") : ""),
                    boost::json::value_to<std::string>(j.at("hardwareId").is_string() ? j.at("hardwareId") : ""),
                    boost::json::value_to<std::string>(j.at("hardwareName").is_string() ? j.at("hardwareName") : ""),
                    boost::json::value_to<std::string>(j.at("hardwareType").is_string() ? j.at("hardwareType") : ""),
                    boost::json::value_to<float>(j.at("value").is_number() ? j.at("value") : 0),
                    boost::json::value_to<float>(j.at("max").is_number() ? j.at("max") : 0),
                    boost::json::value_to<float>(j.at("min").is_number() ? j.at("min") : 0),
                    boost::json::value_to<long>(j.at("valuesTimeWindow").is_number() ? j.at("valuesTimeWindow") : 0),
                    boost::json::value_to<std::vector<SensorValue>>(
                            j.at("values").is_array() ? j.at("values") : boost::json::array())
            );
            return s;
        } catch (std::exception const &e) {
            throw JsonInvalidDataException("error parsing json (Sensor)", e.what());
        }
    }

    void Converters::hwStatusDataFromJson(NvmeSmart &nvmeSmart, HwStatus &s) {
        boost::json::value json = boost::json::parse(std::string(s.getData().begin(), s.getData().end()));
        nvmeSmart = boost::json::value_to<NvmeSmart>(json);
    }

    void Converters::hwStatusDataFromJson(std::vector<SmartAttribute> &attributes, HwStatus &s) {
        boost::json::value json = boost::json::parse(std::string(s.getData().begin(), s.getData().end()));
        attributes = boost::json::value_to<std::vector<SmartAttribute>>(json);
    }

    Sensor Converters::sensorFromJson(const std::string &document) {
        boost::json::value json = boost::json::parse(document);
        return boost::json::value_to<Sensor>(json);
    }

    std::vector<Hardware> Converters::hardwareTreeFromJson(const std::string &document) {
        boost::json::value json = boost::json::parse(document);
        return boost::json::value_to<std::vector<Hardware>>(json);
    }

    std::vector<IndexItem> Converters::indexFromJson(const std::string &document) {
        boost::json::value json = boost::json::parse(document);
        return boost::json::value_to<std::vector<IndexItem>>(json);
    }

    HwStatus Converters::hwStatusFromJson(const std::vector<char> &data) {
        int hwInfoSize = 0;
        int hwStatusType = 0;
        int hwStatusDataSize = 0;
        int offset = 0;

        std::memcpy(&hwInfoSize, data.data(), sizeof(hwInfoSize));
        offset += sizeof(hwInfoSize);

        std::memcpy(&hwStatusType, data.data() + offset, sizeof(hwStatusType));
        offset += sizeof(hwStatusType);

        std::string document(data.begin() + offset, data.begin() + offset + hwInfoSize);

        offset += hwInfoSize;
        std::memcpy(&hwStatusDataSize, data.data() + offset, sizeof(hwStatusDataSize));
        offset += sizeof(hwStatusDataSize);

        try {
            boost::json::value json = boost::json::parse(document);
            auto s = boost::json::value_to<HwStatus>(json);
            s.getData().resize(hwStatusDataSize);
            std::memcpy(s.getData().data(), data.data() + offset, hwStatusDataSize);
            return s;
        } catch (std::exception const &e) {
            throw JsonInvalidDataException("error parsing json (HwStatus)", e.what());
        }
    }

    template<>
    Hardware Converters::fromJson<Hardware>(boost::json::value const &jv) {
        boost::json::object const &j = jv.as_object();

        try {
            Hardware h(
                    boost::json::value_to<std::string>(j.at("hardwareType").is_string() ? j.at("hardwareType") : ""),
                    boost::json::value_to<std::string>(j.at("identifier").is_string() ? j.at("identifier") : ""),
                    boost::json::value_to<std::string>(j.at("name").is_string() ? j.at("name") : ""),
                    boost::json::value_to<std::string>(j.at("parent").is_string() ? j.at("parent") : ""),
                    boost::json::value_to<std::vector<Sensor>>(j.at("sensors").is_array() ? j.at("sensors") : boost::json::array()),
                    boost::json::value_to<std::vector<Hardware>>(
                            j.at("subHardware").is_array() ? j.at("subHardware") : boost::json::array())
            );
            return h;
        } catch (std::exception const &e) {
            throw JsonInvalidDataException("error parsing json (Hardware)", e.what());
        }
    }

    template<>
    SensorValue Converters::fromJson<SensorValue>(boost::json::value const &jv) {
        boost::json::object const &j = jv.as_object();
        try {
            SensorValue sv(
                    boost::json::value_to<float>(j.at("value").is_number() ? j.at("value") : 0),
                    boost::json::value_to<std::string>(j.at("time").is_string() ? j.at("time") : "")
            );
            return sv;
        } catch (std::exception const &e) {
            throw JsonInvalidDataException("error parsing json (SensorValue)", e.what());
        }
    }

    template<>
    IndexItem Converters::fromJson<IndexItem>(boost::json::value const &jv) {
        boost::json::object const &j = jv.as_object();
        try {
            IndexItem idx(
                    boost::json::value_to<std::string>(j.at("identifier").is_string() ? j.at("identifier") : ""),
                    boost::json::value_to<int>(j.at("offset").is_number() ? j.at("offset") : 0),
                    boost::json::value_to<int>(j.at("size").is_number() ? j.at("size") : 0),
                    boost::json::value_to<std::string>(j.at("sensorName").is_string() ? j.at("sensorName") : ""),
                    boost::json::value_to<std::string>(j.at("sensorType").is_string() ? j.at("sensorType") : ""),
                    boost::json::value_to<std::string>(j.at("hardwareName").is_string() ? j.at("hardwareName") : "")
            );
            return idx;
        } catch (std::exception const &e) {
            throw JsonInvalidDataException("error parsing json (IndexItem)", e.what());
        }
    }

    template<>
    SmartAttribute Converters::fromJson<SmartAttribute>(boost::json::value const &jv) {
        boost::json::object const &j = jv.as_object();

        try {
            SmartAttribute attr(
                    boost::json::value_to<unsigned char>(j.at("id").is_number() ? j.at("id") : 0),
                    boost::json::value_to<std::string>(j.at("name").is_string() ? j.at("name") : ""),
                    boost::json::value_to<unsigned short>(j.at("flags").is_number() ? j.at("flags") : 0),
                    boost::json::value_to<std::vector<unsigned char>>(
                            j.at("rawValue").is_array() ? j.at("rawValue") : boost::json::array()),
                    boost::json::value_to<unsigned char>(j.at("currentValue").is_number() ? j.at("currentValue") : 0),
                    boost::json::value_to<unsigned char>(j.at("worstValue").is_number() ? j.at("worstValue") : 0),
                    boost::json::value_to<unsigned char>(j.at("threshold").is_number() ? j.at("threshold") : 0),
                    boost::json::value_to<bool>(j.at("advisory").is_bool() ? j.at("advisory") : false),
                    boost::json::value_to<bool>(j.at("prefail").is_bool() ? j.at("prefail") : false)
            );
            return attr;
        } catch (std::exception const &e) {
            throw JsonInvalidDataException("error parsing json (SmartAttribute)", e.what());
        }
    }

    template<>
    NvmeSmart Converters::fromJson<NvmeSmart>(boost::json::value const &jv) {
        boost::json::object const &j = jv.as_object();

        try {
            NvmeSmart nvmeSmart(
                    boost::json::value_to<unsigned char>(j.at("availableSpare").is_number() ? j.at("availableSpare") : 0),
                    boost::json::value_to<unsigned char>(
                            j.at("availableSpareThreshold").is_number() ? j.at("availableSpareThreshold") : 0),
                    boost::json::value_to<unsigned long>(j.at("controllerBusyTime").is_number() ? j.at("controllerBusyTime") : 0),
                    boost::json::value_to<unsigned int>(
                            j.at("criticalCompositeTemperatureTime").is_number() ? j.at("criticalCompositeTemperatureTime") : 0),
                    boost::json::value_to<unsigned char>(j.at("criticalWarning").is_number() ? j.at("criticalWarning") : 0),
                    boost::json::value_to<unsigned long>(j.at("dataUnitRead").is_number() ? j.at("dataUnitRead") : 0),
                    boost::json::value_to<unsigned long>(j.at("dataUnitWritten").is_number() ? j.at("dataUnitWritten") : 0),
                    boost::json::value_to<unsigned long>(
                            j.at("errorInfoLogEntryCount").is_number() ? j.at("errorInfoLogEntryCount") : 0),
                    boost::json::value_to<unsigned long>(j.at("hostReadCommands").is_number() ? j.at("hostReadCommands") : 0),
                    boost::json::value_to<unsigned long>(j.at("hostWriteCommands").is_number() ? j.at("hostWriteCommands") : 0),
                    boost::json::value_to<unsigned long>(j.at("mediaErrors").is_number() ? j.at("mediaErrors") : 0),
                    boost::json::value_to<unsigned char>(j.at("percentageUsed").is_number() ? j.at("percentageUsed") : 0),
                    boost::json::value_to<unsigned long>(j.at("powerCycle").is_number() ? j.at("powerCycle") : 0),
                    boost::json::value_to<unsigned long>(j.at("powerOnHours").is_number() ? j.at("powerOnHours") : 0),
                    boost::json::value_to<int>(j.at("temperature").is_number() ? j.at("temperature") : 0),
                    boost::json::value_to<std::vector<int>>(
                            j.at("temperatureSensors").is_array() ? j.at("temperatureSensors") : boost::json::array()),
                    boost::json::value_to<unsigned long>(j.at("unsafeShutdowns").is_number() ? j.at("unsafeShutdowns") : 0),
                    boost::json::value_to<unsigned int>(
                            j.at("warningCompositeTemperatureTime").is_number() ? j.at("warningCompositeTemperatureTime") : 0)
            );
            return nvmeSmart;
        } catch (std::exception const &e) {
            throw JsonInvalidDataException("error parsing json (NvmeSmart)", e.what());
        }
    }

    template<>
    HwStatus Converters::fromJson<HwStatus>(boost::json::value const &jv) {
        boost::json::object const &j = jv.as_object();
        HwStatusType t;
        try {
            auto hwStatusTypeStr = boost::json::value_to<std::string>(j.at("hwStatusType").is_string() ? j.at("hwStatusType") : "");

            if (hwStatusTypeStr == "STORAGE_SMART_NVME") {
                t = HwStatusType::STORAGE_SMART_NVME;
            } else {
                t = HwStatusType::STORAGE_SMART_ATA;
            }

            HwStatus hwStatus(
                    boost::json::value_to<std::string>(j.at("identifier").is_string() ? j.at("identifier") : ""),
                    t,
                    boost::json::value_to<std::string>(j.at("hardwareType").is_string() ? j.at("hardwareType") : ""),
                    boost::json::value_to<std::string>(j.at("name").is_string() ? j.at("name") : "")
            );
            return hwStatus;
        } catch (std::exception const &e) {
            throw JsonInvalidDataException("error parsing json (HwStatus object)", e.what());
        }
    }
}
