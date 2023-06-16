# LibHardwareService
## A C++ client library for [LibreHardwareService](https://github.com/epinter/LibreHardwareService)

[![Latest Release](https://img.shields.io/github/release/epinter/lhwservice.svg)](https://github.com/epinter/lhwservice/releases/latest)
[![Downloads](https://img.shields.io/github/downloads/epinter/lhwservice/total.svg)](https://github.com/epinter/lhwservice/releases/latest)
[![Release Date](https://img.shields.io/github/release-date/epinter/lhwservice.svg)](https://github.com/epinter/lhwservice/releases/latest)
[![License](https://img.shields.io/github/license/epinter/lhwservice.svg)](https://github.com/epinter/lhwservice/blob/main/LICENSE)

This library is used to retrieve data from LibreHardwareService.

## Runtime Requirements

- [LibreHardwareService](https://github.com/epinter/LibreHardwareService)
- [Visual C++ Redistributable 2022](https://docs.microsoft.com/en-US/cpp/windows/latest-supported-vc-redist)
- [CMake](https://cmake.org/)
- [vcpkg](https://vcpkg.io/en/)
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/vs/community/)


## Building

```
./cmake/build.ps1
```

## Usage
```
#include <lhwservice/HardwareService.h>
...

int main() {
    lhws::HardwareService hwService;
    for (auto &a: hwService.getSmartAttributes("Harddisk Name", "Storage")) {
        std::cout << a.getName() << ": " << a.getValue() << std::endl;
    }

    try {
        lhws::Sensor a = hardwareService.getSensorByName("Sensor Name", "Temperature", "Hardware Name");
        std::cout << a.getName() << ": " << a.getValue() << std::endl;
    } catch (const SensorNotFoundException &e) {
        std::cerr << e.what() << endl;
    }

    try {
        lhws::Sensor a = hardwareService.getSensorById("/intelcpu/0/temperature/2");
        std::cout << a.getName() << ": " << a.getValue() << std::endl;
    } catch (const SensorNotFoundException &e) {
        std::cerr << e.what() << endl;
    }
}
```

For sensor types and names, run ShowSensors.exe from LibreHardwareService, or see LibreHardwareMonitor documentation / code.

## License

This software is licensed under the terms of [Mozilla Public License Version 2.0](https://www.mozilla.org/en-US/MPL/2.0/).
