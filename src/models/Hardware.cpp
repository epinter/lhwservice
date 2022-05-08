// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 10/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "models/Hardware.h"

#include <utility>

namespace lhws {
    [[maybe_unused]] const std::string &Hardware::getHardwareType() const {
        return hardwareType;
    }

    [[maybe_unused]] const std::string &Hardware::getIdentifier() const {
        return identifier;
    }

    [[maybe_unused]] const std::string &Hardware::getName() const {
        return name;
    }

    [[maybe_unused]] const std::string &Hardware::getParent() const {
        return parent;
    }

    [[maybe_unused]] const std::vector<Sensor> &Hardware::getSensors() const {
        return sensors;
    }

    [[maybe_unused]] const std::vector<Hardware> &Hardware::getSubHardware() const {
        return subHardware;
    }

    Hardware::Hardware(std::string hardwareType, std::string identifier, std::string name,
                       std::string parent, std::vector<Sensor> sensors, std::vector<Hardware> subHardware)
            : hardwareType(std::move(hardwareType)),
              identifier(std::move(identifier)),
              name(std::move(name)),
              parent(std::move(parent)),
              sensors(std::move(sensors)),
              subHardware(std::move(subHardware)) {}
}