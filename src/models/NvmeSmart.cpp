// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 22/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "models/NvmeSmart.h"

#include <utility>

namespace lhws {
    NvmeSmart::NvmeSmart(unsigned char availableSpare, unsigned char availableSpareThreshold, unsigned long controllerBusyTime,
                         unsigned int criticalCompositeTemperatureTime, unsigned char criticalWarning, unsigned long dataUnitRead,
                         unsigned long dataUnitWritten, unsigned long errorInfoLogEntryCount, unsigned long hostReadCommands,
                         unsigned long hostWriteCommands, unsigned long mediaErrors, unsigned char percentageUsed,
                         unsigned long powerCycle, unsigned long powerOnHours, int temperature,
                         std::vector<int> temperatureSensors, unsigned long unsafeShutdowns,
                         unsigned int warningCompositeTemperatureTime) : availableSpare(availableSpare),
                                                                         availableSpareThreshold(availableSpareThreshold),
                                                                         controllerBusyTime(controllerBusyTime),
                                                                         criticalCompositeTemperatureTime(
                                                                                 criticalCompositeTemperatureTime),
                                                                         criticalWarning(criticalWarning),
                                                                         dataUnitRead(dataUnitRead),
                                                                         dataUnitWritten(dataUnitWritten),
                                                                         errorInfoLogEntryCount(errorInfoLogEntryCount),
                                                                         hostReadCommands(hostReadCommands),
                                                                         hostWriteCommands(hostWriteCommands),
                                                                         mediaErrors(mediaErrors), percentageUsed(percentageUsed),
                                                                         powerCycle(powerCycle), powerOnHours(powerOnHours),
                                                                         temperature(temperature),
                                                                         temperatureSensors(std::move(temperatureSensors)),
                                                                         unsafeShutdowns(unsafeShutdowns),
                                                                         warningCompositeTemperatureTime(
                                                                                 warningCompositeTemperatureTime) {}

    unsigned char NvmeSmart::getAvailableSpare() const {
        return availableSpare;
    }

    unsigned char NvmeSmart::getAvailableSpareThreshold() const {
        return availableSpareThreshold;
    }

    unsigned long NvmeSmart::getControllerBusyTime() const {
        return controllerBusyTime;
    }

    unsigned int NvmeSmart::getCriticalCompositeTemperatureTime() const {
        return criticalCompositeTemperatureTime;
    }

    unsigned char NvmeSmart::getCriticalWarning() const {
        return criticalWarning;
    }

    unsigned long NvmeSmart::getDataUnitRead() const {
        return dataUnitRead;
    }

    unsigned long NvmeSmart::getDataUnitWritten() const {
        return dataUnitWritten;
    }

    unsigned long NvmeSmart::getErrorInfoLogEntryCount() const {
        return errorInfoLogEntryCount;
    }

    unsigned long NvmeSmart::getHostReadCommands() const {
        return hostReadCommands;
    }

    unsigned long NvmeSmart::getHostWriteCommands() const {
        return hostWriteCommands;
    }

    unsigned long NvmeSmart::getMediaErrors() const {
        return mediaErrors;
    }

    unsigned char NvmeSmart::getPercentageUsed() const {
        return percentageUsed;
    }

    unsigned long NvmeSmart::getPowerCycle() const {
        return powerCycle;
    }

    unsigned long NvmeSmart::getPowerOnHours() const {
        return powerOnHours;
    }

    int NvmeSmart::getTemperature() const {
        return temperature;
    }

    const std::vector<int> &NvmeSmart::getTemperatureSensors() const {
        return temperatureSensors;
    }

    unsigned long NvmeSmart::getUnsafeShutdowns() const {
        return unsafeShutdowns;
    }

    unsigned int NvmeSmart::getWarningCompositeTemperatureTime() const {
        return warningCompositeTemperatureTime;
    }
}
