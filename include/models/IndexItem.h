// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 06/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string>

namespace lhws {
    class IndexItem {
    private:
        std::string identifier{};
        int offset{};
        int size{};
        std::string sensorName{};
        std::string sensorType{};
        std::string hardwareName{};

    public:
        IndexItem(std::string identifier, int offset, int size, std::string sensorName, std::string sensorType,
                  std::string hardwareName);

        IndexItem();

        [[nodiscard]] const std::string &getIdentifier() const;

        [[nodiscard]] int getOffset() const;

        [[nodiscard]] int getSize() const;

        [[nodiscard]] const std::string &getSensorName() const;

        [[nodiscard]] const std::string &getSensorType() const;

        [[nodiscard]] const std::string &getHardwareName() const;
    };
}