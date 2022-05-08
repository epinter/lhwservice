// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 23/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace lhws {
    class Metadata {
    private:
        int updateInterval{};
        long long lastUpdate{};

    public:
        Metadata(int updateInterval, long long int lastUpdate);

        Metadata() = default;

        [[nodiscard]] [[maybe_unused]] int getUpdateInterval() const {
            return updateInterval;
        }

        [[nodiscard]] [[maybe_unused]] long long getLastUpdate() const {
            return lastUpdate;
        }

        [[maybe_unused]] void setUpdateInterval(int const &aUpdateInterval) {
            Metadata::updateInterval = aUpdateInterval;
        }

        [[maybe_unused]] void setLastUpdate(long long int const &aLastUpdate) {
            Metadata::lastUpdate = aLastUpdate;
        }
    };
}