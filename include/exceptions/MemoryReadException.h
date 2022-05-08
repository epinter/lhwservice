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
#include <utility>
#include "GenericException.h"

class MemoryReadException : public GenericException {
public:
    [[maybe_unused]] explicit MemoryReadException(const std::string &error) : GenericException(error) {
        setName(__func__);
    }

    [[maybe_unused]] MemoryReadException(const std::string &error, const std::string &whatCause) : GenericException(error,
                                                                                                                    whatCause) {
        setName(__func__);
    }
};