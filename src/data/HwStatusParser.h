// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 21/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <vector>
#include "models/HwStatus.h"
#include "HwStatusLoader.h"

namespace lhws {
    class HwStatusParser {
    private:
        HwStatusLoader &loader;

    public:
        [[maybe_unused]] explicit HwStatusParser(HwStatusLoader &aLoader) : loader(aLoader) {}

        HwStatus parseHwStatus(std::string const &name, std::string const &hardwareType);
    };
}