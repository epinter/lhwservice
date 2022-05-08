// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 06/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string>
#include <vector>
#include "models/SensorValue.h"

namespace lhws {
    class Sensor {
    private:
        std::string identifier{};
        std::string name{};
        std::string sensorType{};
        std::string hardwareId{};
        std::string hardwareName{};
        std::string hardwareType{};
        float value{};
        float max{};
        float min{};
        long valuesTimeWindow{};
        std::vector<SensorValue> values{};

    public:
        Sensor(std::string identifier, std::string name, std::string sensorType, std::string hardwareId,
               std::string hardwareName, std::string hardwareType, float value, float max, float min,
               long valuesTimeWindow, std::vector<SensorValue> values);

        Sensor() = default;

        [[nodiscard]] [[maybe_unused]] const std::string &getIdentifier() const;

        [[nodiscard]] [[maybe_unused]] const std::string &getName() const;

        [[nodiscard]] [[maybe_unused]] const std::string &getSensorType() const;

        [[nodiscard]] [[maybe_unused]] const float &getValue() const;

        [[nodiscard]] [[maybe_unused]] const float &getMax() const;

        [[nodiscard]] [[maybe_unused]] const float &getMin() const;

        [[nodiscard]] [[maybe_unused]] long getValuesTimeWindow() const;

        [[nodiscard]] [[maybe_unused]] std::vector<SensorValue> &getValues();

        [[nodiscard]] [[maybe_unused]] const std::string &getHardwareId() const;

        [[nodiscard]] [[maybe_unused]] const std::string &getHardwareName() const;

        [[nodiscard]] [[maybe_unused]] const std::string &getHardwareType() const;
    };

    std::ostream &operator<<(std::ostream &stream, std::vector<SensorValue> const &v);
}