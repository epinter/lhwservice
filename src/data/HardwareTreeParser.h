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
#include "HardwareTreeLoader.h"
#include "models/Hardware.h"

namespace lhws {
    class HardwareTreeParser {
    private:
        HardwareTreeLoader &loader;

    public:
        explicit HardwareTreeParser(HardwareTreeLoader &aLoader) : loader(aLoader) {}

        std::vector<Hardware> parseHardwareTree();
    };
}