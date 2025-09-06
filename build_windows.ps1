$ErrorActionPreference = "Stop"

# Configure + build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

# Install to user prefix
$prefix = "$env:LOCALAPPDATA\Programs\sshtron"
cmake --install build --prefix "$prefix"

$bin = "$prefix\bin"
if (-not ($env:Path -split ';' | Where-Object { $_ -eq $bin })) {
  [Environment]::SetEnvironmentVariable("Path", $env:Path + ";" + $bin, "User")
  Write-Host "Added $bin to PATH for current user. Open a new terminal."
}

Write-Host "Done. Run 'sshtron' in a new terminal."
