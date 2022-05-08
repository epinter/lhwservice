// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 10/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "HardwareTreeParser.h"
#include "models/Sensor.h"
#include "models/SensorValue.h"
#include "Converters.h"
#include "exceptions/SensorParseException.h"

namespace lhws {
    [[maybe_unused]] std::vector<Hardware> HardwareTreeParser::parseHardwareTree() {
        std::string document(loader.getData().begin(), loader.getData().end());
        try {
            return Converters::hardwareTreeFromJson(document);
        } catch (std::exception const &e) {
            throw SensorParseException("error parsing hardware data (json)", e.what());
        }
    }
}