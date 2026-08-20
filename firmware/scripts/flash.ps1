param(
    [Parameter(Mandatory = $true)][string]$BinPath
)

if (-not (Test-Path $BinPath)) {
    Write-Error "Binary not found: $BinPath"
    exit 1
}

# Nucleo/Discovery boards expose their onboard ST-Link as a USB mass-storage
# drive (mbed DAPLink). Volume label is typically NODE_<mcu> (Nucleo) or
# DIS_<mcu> (Discovery); older firmware uses MBED.
$drive = Get-Volume -ErrorAction SilentlyContinue |
    Where-Object { $_.FileSystemLabel -match '^(NODE_|DIS_|MBED)' } |
    Select-Object -First 1

if (-not $drive) {
    Write-Error "ST-Link mass-storage drive not found. Connect the board via the ST-Link USB port and try again."
    exit 1
}

$dest = "$($drive.DriveLetter):\"
Write-Host "Flashing $BinPath -> $dest ($($drive.FileSystemLabel))"
Copy-Item -Path $BinPath -Destination $dest -Force
Write-Host "Done. Board resets automatically after the copy completes."
