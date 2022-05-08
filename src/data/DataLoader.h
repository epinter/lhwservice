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

#include <string>
#include "models/Metadata.h"

namespace lhws {
    class DataLoader {
    public:
        std::string getSystemError();

        bool isOffsetValid(long long regionSize, int offset, int size);

        template<typename T>
        T fromBytes(const char *bytes) {
            T ret = 0;
            std::memcpy(&ret, bytes, sizeof(T));
            return ret;
        }

        [[nodiscard]] virtual int getUpdateInterval() const = 0;

        [[nodiscard]] virtual long long getLastUpdate() const = 0;

        [[nodiscard]] virtual Metadata getMetadata() const = 0;
    };
}