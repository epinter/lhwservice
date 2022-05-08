$ErrorActionPreference = "Stop"

$projectRoot = Resolve-Path "$PSScriptRoot/.."

if(!(Test-Path "$projectRoot/out/release-msvc-x86")) {
    mkdir "$projectRoot/out/release-msvc-x86"
}
$cwd = Get-Location
Set-Location "$projectRoot/out/release-msvc-x86"

write-host "Starting cmake"
write-host $pwd
cmake --build . --target package --config Release
cmake --build . --target install --config Release

Set-Location $cwd
