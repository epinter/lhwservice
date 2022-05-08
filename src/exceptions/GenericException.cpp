// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 29/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "exceptions/GenericException.h"

#include <utility>

GenericException::GenericException(std::string error) : error(std::move(error)) {
    setName(__func__);
}

GenericException::GenericException(std::string aError, std::string aWhatCause) : error(std::move(aError)),
                                                                                 cause(std::move(aWhatCause)) {
    setName(__func__);
}

const char *GenericException::what() const noexcept {
    return fullMsg.c_str();
}

void GenericException::setName(const std::string &aName) {
    name = aName;
    if (!cause.empty()) {
        fullMsg = std::string(aName).append(": ").append(error)
                .append(".\n Cause: ").append(cause);
    } else {
        fullMsg = std::string(name).append(": ").append(error);
    }
}