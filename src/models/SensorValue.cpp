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
#include "models/SensorValue.h"

namespace lhws {
    SensorValue::SensorValue(float aValue, std::string aTime) : value(aValue), time(std::move(aTime)) {}

    float SensorValue::getValue() const {
        return value;
    }

    const std::string &SensorValue::getTime() const {
        return time;
    }

    std::ostream &operator<<(std::ostream &stream, const SensorValue &v) {
        return stream << boost::format("{%1%,%2}") % v.getValue() % v.getTime();
    }

    bool SensorValue::operator!=(const SensorValue &i) const {
        return i.getValue() != value && i.getTime() != time;
    }
}