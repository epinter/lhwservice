// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 10/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <boost/format.hpp>
#include <utility>
#include "models/Sensor.h"

namespace lhws {
    const std::string &Sensor::getIdentifier() const {
        return identifier;
    }

    const std::string &Sensor::getName() const {
        return name;
    }

    const std::string &Sensor::getSensorType() const {
        return sensorType;
    }

    const float &Sensor::getValue() const {
        return value;
    }

    long Sensor::getValuesTimeWindow() const {
        return valuesTimeWindow;
    }

    const float &Sensor::getMax() const {
        return max;
    }

    const float &Sensor::getMin() const {
        return min;
    }

    std::vector<SensorValue> &Sensor::getValues() {
        return values;
    }

    const std::string &Sensor::getHardwareId() const {
        return hardwareId;
    }

    const std::string &Sensor::getHardwareName() const {
        return hardwareName;
    }

    const std::string &Sensor::getHardwareType() const {
        return hardwareType;
    }

    Sensor::Sensor(std::string identifier, std::string name, std::string sensorType,
                   std::string hardwareId, std::string hardwareName, std::string hardwareType, float value,
                   float max, float min, long valuesTimeWindow, std::vector<SensorValue> values)
            : identifier(std::move(identifier)),
              name(std::move(name)),
              sensorType(std::move(sensorType)),
              hardwareId(std::move(hardwareId)),
              hardwareName(std::move(hardwareName)),
              hardwareType(std::move(hardwareType)),
              value(value), max(max),
              min(min),
              valuesTimeWindow(valuesTimeWindow),
              values(std::move(values)) {}

    std::ostream &operator<<(std::ostream &stream, std::vector<SensorValue> const &v) {
        std::string ret;
        ret.append("[");
        for (auto &i: v) {
            ret.append((boost::format("{%1%,%2%}") % i.getValue() % i.getTime()).str());
            if (i != v.back()) {
                ret.append(",");
            }
        }
        ret.append("]");

        return stream << ret;
    }
}