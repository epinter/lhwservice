$ErrorActionPreference = "Stop"

$projectRoot = Resolve-Path "$PSScriptRoot/.."

if(!(Test-Path "$projectRoot/out/debug-msvc-x64")) {
    mkdir "$projectRoot/out/debug-msvc-x64"
}
$cwd = Get-Location
Set-Location "$projectRoot/out/debug-msvc-x64"

write-host "Starting cmake"
write-host $pwd
cmake --build . --target install --config Debug

Set-Location $cwd
