// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 13/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <iostream>
#include "models/Sensor.h"
#include "models/IndexItem.h"
#include "models/Hardware.h"
#include "models/Metadata.h"
#include "models/SmartAttribute.h"
#include "models/NvmeSmart.h"

namespace lhws {
    class [[maybe_unused]] HardwareService {
    private:
        Metadata sensorsMetadata{};
        Metadata hwStatusMetadata{};
        Metadata hwTreeMetadata{};

    public:
        HardwareService() = default;

        [[nodiscard]] [[maybe_unused]] std::vector<Hardware> getHardwareTree();

        [[nodiscard]] [[maybe_unused]] Sensor getSensorById(std::string const &identifier);

        [[nodiscard]] [[maybe_unused]] Sensor
        getSensorByName(std::string const &sensorName, std::string const &sensorType, std::string const &hardwareName);

        [[nodiscard]] [[maybe_unused]] std::vector<IndexItem> getIndex();

        [[nodiscard]] [[maybe_unused]] const Metadata &getSensorsMetadata() const;

        [[nodiscard]] [[maybe_unused]] const Metadata &getHwStatusMetadata() const;

        [[nodiscard]] [[maybe_unused]] const Metadata &getHwTreeMetadata() const;

        [[nodiscard]] [[maybe_unused]] std::vector<SmartAttribute>
        getSmartAttributes(std::string const &hardwareName, std::string const &hardwareType);

        [[nodiscard]] [[maybe_unused]] NvmeSmart getNvmeSmart(std::string const &hardwareName, std::string const &hardwareType);
    };
}