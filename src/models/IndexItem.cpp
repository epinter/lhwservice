// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 10/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "models/IndexItem.h"

#include <utility>

namespace lhws {
    const std::string &IndexItem::getIdentifier() const {
        return identifier;
    }

    int IndexItem::getOffset() const {
        return offset;
    }

    int IndexItem::getSize() const {
        return size;
    }

    const std::string &IndexItem::getSensorName() const {
        return sensorName;
    }

    const std::string &IndexItem::getSensorType() const {
        return sensorType;
    }


    const std::string &IndexItem::getHardwareName() const {
        return hardwareName;
    }

    IndexItem::IndexItem(std::string identifier, int offset, int size, std::string sensorName,
                         std::string sensorType, std::string hardwareName)
            : identifier(std::move(identifier)),
              offset(offset),
              size(size),
              sensorName(std::move(sensorName)),
              sensorType(std::move(sensorType)),
              hardwareName(std::move(hardwareName)) {}

    IndexItem::IndexItem() = default;
}