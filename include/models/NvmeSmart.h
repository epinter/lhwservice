// Copyright (C) 2022 Emerson Pinter - All Rights Reserved
//
// Created by epinter on 22/05/2022.
//

/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <vector>

namespace lhws {
    class NvmeSmart {
    private:
        unsigned char availableSpare{};
        unsigned char availableSpareThreshold{};
        unsigned long controllerBusyTime{};
        unsigned int criticalCompositeTemperatureTime{};
        unsigned char criticalWarning{};
        unsigned long dataUnitRead{};
        unsigned long dataUnitWritten{};
        unsigned long errorInfoLogEntryCount{};
        unsigned long hostReadCommands{};
        unsigned long hostWriteCommands{};
        unsigned long mediaErrors{};
        unsigned char percentageUsed{};
        unsigned long powerCycle{};
        unsigned long powerOnHours{};
        int temperature{};
        std::vector<int> temperatureSensors{};
        unsigned long unsafeShutdowns{};
        unsigned int warningCompositeTemperatureTime{};

    public:
        NvmeSmart(unsigned char availableSpare, unsigned char availableSpareThreshold, unsigned long controllerBusyTime,
                  unsigned int criticalCompositeTemperatureTime, unsigned char criticalWarning, unsigned long dataUnitRead,
                  unsigned long dataUnitWritten, unsigned long errorInfoLogEntryCount, unsigned long hostReadCommands,
                  unsigned long hostWriteCommands, unsigned long mediaErrors, unsigned char percentageUsed,
                  unsigned long powerCycle, unsigned long powerOnHours, int temperature, std::vector<int> temperatureSensors,
                  unsigned long unsafeShutdowns, unsigned int warningCompositeTemperatureTime);

        NvmeSmart() = default;

        [[maybe_unused]] [[nodiscard]] unsigned char getAvailableSpare() const;

        [[maybe_unused]] [[nodiscard]] unsigned char getAvailableSpareThreshold() const;

        [[maybe_unused]] [[nodiscard]] unsigned long getControllerBusyTime() const;

        [[maybe_unused]] [[nodiscard]] unsigned int getCriticalCompositeTemperatureTime() const;

        [[maybe_unused]] [[nodiscard]] unsigned char getCriticalWarning() const;

        [[maybe_unused]] [[nodiscard]] unsigned long getDataUnitRead() const;

        [[maybe_unused]] [[nodiscard]] unsigned long getDataUnitWritten() const;

        [[maybe_unused]] [[nodiscard]] unsigned long getErrorInfoLogEntryCount() const;

        [[maybe_unused]] [[nodiscard]] unsigned long getHostReadCommands() const;

        [[maybe_unused]] [[nodiscard]] unsigned long getHostWriteCommands() const;

        [[maybe_unused]] [[nodiscard]] unsigned long getMediaErrors() const;

        [[maybe_unused]] [[nodiscard]] unsigned char getPercentageUsed() const;

        [[maybe_unused]] [[nodiscard]] unsigned long getPowerCycle() const;

        [[maybe_unused]] [[nodiscard]] unsigned long getPowerOnHours() const;

        [[maybe_unused]] [[nodiscard]] int getTemperature() const;

        [[maybe_unused]] [[nodiscard]] const std::vector<int> &getTemperatureSensors() const;

        [[maybe_unused]] [[nodiscard]] unsigned long getUnsafeShutdowns() const;

        [[maybe_unused]] [[nodiscard]] unsigned int getWarningCompositeTemperatureTime() const;
    };
}