// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 22/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "models/SmartAttribute.h"

namespace lhws {
    unsigned char SmartAttribute::getId() const {
        return id;
    }

    const std::string &SmartAttribute::getName() const {
        return name;
    }

    [[maybe_unused]] unsigned short SmartAttribute::getFlags() const {
        return flags;
    }

    [[maybe_unused]] std::vector<unsigned char> SmartAttribute::getRawValue() const {
        return rawValue;
    }

    unsigned char SmartAttribute::getCurrentValue() const {
        return currentValue;
    }

    unsigned char SmartAttribute::getWorstValue() const {
        return worstValue;
    }

    unsigned char SmartAttribute::getThreshold() const {
        return threshold;
    }

    [[maybe_unused]] bool SmartAttribute::isAdvisory() const {
        return advisory;
    }

    bool SmartAttribute::isPrefail() const {
        return prefail;
    }

    SmartAttribute::SmartAttribute(unsigned char id, std::string name, unsigned short flags, std::vector<unsigned char> rawValue,
                                   unsigned char currentValue, unsigned char worstValue, unsigned char threshold, bool advisory,
                                   bool prefail)
            : id(id), name(std::move(name)), flags(flags), rawValue(std::move(rawValue)), currentValue(currentValue),
              worstValue(worstValue),
              threshold(threshold), advisory(advisory), prefail(prefail) {}
}