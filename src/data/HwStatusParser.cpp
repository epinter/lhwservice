// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 21/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "HwStatusParser.h"
#include "Converters.h"

namespace lhws {
    [[maybe_unused]] HwStatus HwStatusParser::parseHwStatus(std::string const &name, std::string const &hardwareType) {
        HwStatus ret;
        for (auto &s: loader.getData()) {
            HwStatus status = Converters::hwStatusFromJson(s);
            if (status.getName() == name && status.getHardwareType() == hardwareType) {
                return status;
            }
        }

        return ret;
    }
} // lhws