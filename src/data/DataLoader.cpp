// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 21/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "DataLoader.h"
#include <system_error>
#include <Windows.h>


namespace lhws {
    std::string DataLoader::getSystemError() {
        return std::system_category().message(static_cast<int>(GetLastError()));
    }

    bool DataLoader::isOffsetValid(long long int regionSize, int offset, int size) {
        return offset > 0 && size > 0 && (offset + size) < regionSize;
    }
}