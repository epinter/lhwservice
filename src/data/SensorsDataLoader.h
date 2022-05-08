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

#include <string>
#include <vector>
#include "models/IndexFormat.h"
#include "DataLoader.h"
#include "models/Metadata.h"

namespace lhws {
    class SensorsDataLoader : DataLoader {
    private:
        std::vector<char> index{};
        std::vector<char> data{};
        IndexFormat indexFormat{};
        Metadata metadata{};

        void loadMemMapSensors();

    public:
        SensorsDataLoader();

        [[nodiscard]] const std::vector<char> &getIndex() const;

        [[nodiscard]] const std::vector<char> &getData() const;

        [[nodiscard]] IndexFormat getIndexFormat() const;

        [[nodiscard]] [[maybe_unused]] int getUpdateInterval() const override;

        [[nodiscard]] [[maybe_unused]] long long getLastUpdate() const override;

        [[nodiscard]] [[maybe_unused]] Metadata getMetadata() const override;
    };
}