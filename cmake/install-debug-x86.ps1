$ErrorActionPreference = "Stop"

$projectRoot = Resolve-Path "$PSScriptRoot/.."

if(!(Test-Path "$projectRoot/out/debug-msvc-x86")) {
    mkdir "$projectRoot/out/debug-msvc-x86"
}
$cwd = Get-Location
Set-Location "$projectRoot/out/debug-msvc-x86"

write-host "Starting cmake"
write-host $pwd
cmake --build . --target install --config Debug

Set-Location $cwd
