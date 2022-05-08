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

namespace lhws {
    class SmartAttribute {
    private:
        unsigned char id{};
        std::string name{};
        unsigned short flags{};
        std::vector<unsigned char> rawValue{};
        unsigned char currentValue{};
        unsigned char worstValue{};
        unsigned char threshold{};
        bool advisory{};
        bool prefail{};

    public:
        SmartAttribute(unsigned char id, std::string name, unsigned short flags, std::vector<unsigned char> rawValue,
                       unsigned char currentValue,
                       unsigned char worstValue, unsigned char threshold, bool advisory, bool prefail);

        SmartAttribute() = default;

        [[nodiscard]] [[maybe_unused]] unsigned char getId() const;

        [[nodiscard]] [[maybe_unused]] const std::string &getName() const;

        [[nodiscard]] [[maybe_unused]] unsigned short getFlags() const;

        [[nodiscard]] [[maybe_unused]] std::vector<unsigned char> getRawValue() const;

        [[nodiscard]] [[maybe_unused]] unsigned char getCurrentValue() const;

        [[nodiscard]] [[maybe_unused]] unsigned char getWorstValue() const;

        [[nodiscard]] [[maybe_unused]] unsigned char getThreshold() const;

        [[nodiscard]] [[maybe_unused]] bool isAdvisory() const;

        [[nodiscard]] [[maybe_unused]] bool isPrefail() const;
    };
}