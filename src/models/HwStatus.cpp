// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 22/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "models/HwStatus.h"
#include "models/SmartAttribute.h"
#include "models/NvmeSmart.h"

#include "data/Converters.h"

namespace lhws {
    HwStatus::HwStatus(std::string identifier, HwStatusType hwStatusType, std::string hardwareType, std::string name)
            : identifier(std::move(identifier)), hwStatusType(hwStatusType), hardwareType(std::move(hardwareType)),
              name(std::move(name)) {}

    const std::string &HwStatus::getIdentifier() const {
        return identifier;
    }

    HwStatusType HwStatus::getHwStatusType() const {
        return hwStatusType;
    }

    const std::string &HwStatus::getHardwareType() const {
        return hardwareType;
    }

    const std::string &HwStatus::getName() const {
        return name;
    }

    std::vector<char> &HwStatus::getData() {
        return data;
    }

    template<>
    std::vector<SmartAttribute> HwStatus::getStatusData<std::vector<SmartAttribute>>() {
        std::vector<SmartAttribute> attrList;
        Converters::hwStatusDataFromJson(attrList, *this);
        return attrList;
    }

    template<>
    NvmeSmart HwStatus::getStatusData<NvmeSmart>() {
        NvmeSmart n;
        Converters::hwStatusDataFromJson(n, *this);
        return n;
    }

}
