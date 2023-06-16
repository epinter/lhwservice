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

static constexpr auto HARDWARETREE_FILENAME = "Global\\LibreHardwareService/json/all/data";
static constexpr auto HARDWARETREE_MUTEX = "Global\\LibreHardwareService/json/all/data/MUTEX";
static constexpr auto SENSORS_FILENAME = "Global\\LibreHardwareService/json/sensors/data";
static constexpr auto SENSORS_MUTEX = "Global\\LibreHardwareService/json/sensors/data/MUTEX";
static constexpr auto HWSTATUS_FILENAME = "Global\\LibreHardwareService/json/status/data";
static constexpr auto HWSTATUS_MUTEX = "Global\\LibreHardwareService/json/status/data/MUTEX";
#if DEBUGBUILD
static constexpr bool ISDEBUG = true;
#else
static constexpr bool ISDEBUG = false;
#endif

#define MUTEX_WAIT_MS 10
