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
#include <chrono>
#include "DataLoader.h"
#include "models/Metadata.h"

namespace lhws {
    class HwStatusLoader : DataLoader {
    private:
        std::vector<std::vector<char>> data;
        Metadata metadata;

        void load();

    public:
        HwStatusLoader();

        [[nodiscard]] const std::vector<std::vector<char>> &getData() const;

        [[nodiscard]] [[maybe_unused]] int getUpdateInterval() const override;

        [[nodiscard]] [[maybe_unused]] long long getLastUpdate() const override;

        [[nodiscard]] [[maybe_unused]] Metadata getMetadata() const override;
    };

}
