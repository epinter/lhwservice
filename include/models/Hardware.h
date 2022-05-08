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
#include "models/Sensor.h"

namespace lhws {
    class Hardware {
    private:
        std::string hardwareType{};
        std::string identifier{};
        std::string name{};
        std::string parent{};
        std::vector<Sensor> sensors{};
        std::vector<Hardware> subHardware{};
    public:
        Hardware(std::string hardwareType, std::string identifier, std::string name, std::string parent,
                 std::vector<Sensor> sensors, std::vector<Hardware> subHardware);

        Hardware() = default;

        [[maybe_unused]] [[nodiscard]] const std::string &getHardwareType() const;

        [[maybe_unused]] [[nodiscard]] const std::string &getIdentifier() const;

        [[maybe_unused]] [[nodiscard]] const std::string &getName() const;

        [[maybe_unused]] [[nodiscard]] const std::string &getParent() const;

        [[maybe_unused]] [[nodiscard]] const std::vector<Sensor> &getSensors() const;

        [[maybe_unused]] [[nodiscard]] const std::vector<Hardware> &getSubHardware() const;
    };
}