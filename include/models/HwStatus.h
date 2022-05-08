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
#include <utility>
#include <vector>
#include "HwStatusType.h"

namespace lhws {
    class HwStatus {
    private:
        std::string identifier{};
        HwStatusType hwStatusType{};
        std::string hardwareType{};
        std::string name{};
        std::vector<char> data{};

    public:
        HwStatus(std::string identifier, HwStatusType hwStatusType, std::string hardwareType, std::string name);

        HwStatus() = default;

        template<class T>
        T getStatusData();

        [[maybe_unused]] [[nodiscard]] const std::string &getIdentifier() const;

        [[maybe_unused]] [[nodiscard]] HwStatusType getHwStatusType() const;

        [[maybe_unused]] [[nodiscard]] const std::string &getHardwareType() const;

        [[maybe_unused]] [[nodiscard]] const std::string &getName() const;

        [[maybe_unused]] [[nodiscard]] std::vector<char> &getData();
    };
}