// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 10/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <vector>
#include "SensorsDataLoader.h"
#include "models/Sensor.h"
#include "models/IndexItem.h"
#include "models/SmartAttribute.h"

namespace lhws {
    class SensorsParser {
    private:
        SensorsDataLoader &loader;

    public:
        [[maybe_unused]] explicit SensorsParser(SensorsDataLoader &aLoader) : loader(aLoader) {}

        std::vector<IndexItem> parseIndex();

        Sensor parseSensor(int const &offset, int const &size);
    };
}