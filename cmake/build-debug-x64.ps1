$ErrorActionPreference = "Stop"

$projectRoot = Resolve-Path "$PSScriptRoot/.."

if(!(Test-Path "$projectRoot/out/debug-msvc-x64")) {
    mkdir "$projectRoot/out/debug-msvc-x64"
}
$cwd = Get-Location
Set-Location "$projectRoot/out/debug-msvc-x64"

write-host "Starting cmake"
write-host $pwd
cmake "$projectRoot" -G "Visual Studio 17 2022" -T v143,host=x64 -A x64 -DCMAKE_TOOLCHAIN_FILE="$($Env:VCPKG_ROOT)/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-static-md -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Debug

cmake --build . --config Debug

Set-Location $cwd
