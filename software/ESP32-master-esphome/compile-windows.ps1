# Short physical paths avoid Windows MAX_PATH failures in ESP-IDF/Arduino.
# Environment overrides apply only while this script runs.
param(
    [string]$IdfPath = 'C:\eh-idf',
    [string]$DataPath = 'C:\eh-data',
    [string]$BuildPath = 'C:\eh-build'
)

$overrides = @{
    ESPHOME_ESP_IDF_PREFIX = $IdfPath
    ESPHOME_DATA_DIR = $DataPath
    ESPHOME_BUILD_PATH = $BuildPath
}
$previous = @{}
foreach ($name in $overrides.Keys) {
    $previous[$name] = [Environment]::GetEnvironmentVariable($name, 'Process')
}
$compileExit = 1
Push-Location $PSScriptRoot
try {
    foreach ($name in $overrides.Keys) {
        [Environment]::SetEnvironmentVariable($name, $overrides[$name], 'Process')
    }
    & esphome compile esp32-master.yaml
    $compileExit = $LASTEXITCODE
} finally {
    foreach ($name in $overrides.Keys) {
        [Environment]::SetEnvironmentVariable($name, $previous[$name], 'Process')
    }
    Pop-Location
}
exit $compileExit
