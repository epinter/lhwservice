// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 09/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#define HARDWARETREE_FILENAME "Global\\LibreHardwareService/json/all/data"
#define HARDWARETREE_MUTEX "Global\\LibreHardwareService/json/all/data/MUTEX"
#define SENSORS_FILENAME "Global\\LibreHardwareService/json/sensors/data"
#define SENSORS_MUTEX "Global\\LibreHardwareService/json/sensors/data/MUTEX"
#define HWSTATUS_FILENAME "Global\\LibreHardwareService/json/status/data"
#define HWSTATUS_MUTEX "Global\\LibreHardwareService/json/status/data/MUTEX"
#if DEBUGBUILD
static constexpr bool ISDEBUG = true;
#else
static constexpr bool ISDEBUG = false;
#endif

#define MUTEX_WAIT_MS 10