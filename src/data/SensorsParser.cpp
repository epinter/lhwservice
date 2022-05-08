// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 10/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <msgpack.hpp>
#include "SensorsParser.h"
#include "models/Sensor.h"
#include "models/SensorValue.h"
#include "models/IndexItem.h"
#include "Converters.h"
#include "exceptions/SensorParseException.h"

namespace lhws {
    [[maybe_unused]] std::vector<IndexItem> SensorsParser::parseIndex() {
        std::vector<IndexItem> idx;

        if (loader.getIndexFormat() == IndexFormat::MSGPACK) {
            try {
                msgpack::object_handle oh = msgpack::unpack(loader.getIndex().data(), loader.getIndex().size());
                msgpack::object deserialized = oh.get();

                idx = deserialized.as<std::vector<IndexItem>>();
            } catch (std::exception const &e) {
                throw SensorParseException("Error parsing msgpack. Check if the msgpack data have any null values.",
                                           e.what());
            }
        } else if (loader.getIndexFormat() == IndexFormat::JSON) {
            try {
                idx = Converters::indexFromJson(std::string(loader.getIndex().begin(), loader.getIndex().end()));
            } catch (std::exception const &e) {
                throw SensorParseException("Error parsing index (json)", e.what());
            }
        } else {
            throw SensorParseException("Invalid index format");
        }

        return idx;
    }

    [[maybe_unused]] Sensor SensorsParser::parseSensor(int const &offset, int const &size) {
        std::string document(loader.getData().begin() + offset, loader.getData().begin() + offset + size);
        try {
            return Converters::sensorFromJson(document);
        } catch (std::exception const &e) {
            throw SensorParseException("error parsing sensor (json)", e.what());
        }
    }
}