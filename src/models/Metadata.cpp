// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 29/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "models/Metadata.h"

namespace lhws {
    Metadata::Metadata(int updateInterval, long long int lastUpdate) : updateInterval(updateInterval),
                                                                       lastUpdate(lastUpdate) {}
}