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

namespace lhws {
    class SensorValue {
    private:
        float value{};
        std::string time{};

    public:
        SensorValue(float value, std::string aTime);

        [[nodiscard]] float getValue() const;

        [[nodiscard]] const std::string &getTime() const;

        bool operator!=(const SensorValue &i) const;
    };
}