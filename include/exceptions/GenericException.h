// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 29/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <exception>
#include <string>

class GenericException : public std::exception {
private:
    std::string cause{};
    std::string error{};
    std::string fullMsg{};

protected:
    std::string name{};
public:
    [[maybe_unused]] explicit GenericException(std::string error);

    [[maybe_unused]] explicit GenericException(std::string error, std::string whatCause);

    void setName(const std::string &aName);

    [[nodiscard]] [[maybe_unused]] const char *what() const noexcept override;
};