echo off
set PREMAKE_URL="https://github.com/premake/premake-core/releases/download/v5.0.0-beta7/premake-5.0.0-beta7-windows.zip"
set PREMAKE_HASH="930710B7A86FF323D3AE5CEA9972CBA08DDC7018C240A457BD4D532828B0B747"
set PREMAKE_LICENSE="https://raw.githubusercontent.com/premake/premake-core/refs/heads/master/LICENSE.txt"

goto start

:InstallPremake

if not exist "external/premake/bin" mkdir "external/premake/bin"

powershell -NoProfile -NonInteractive -Command "Invoke-WebRequest %PREMAKE_URL% -OutFile external/premake/bin/premake.zip"

IF ERRORLEVEL 1 (
    echo "Error: Downloading premake failed!"
    exit 2
)

powershell -NoProfile -NonInteractive -Command "Invoke-WebRequest %PREMAKE_LICENSE% -OutFile external/premake/bin/LICENSE.txt"

IF ERRORLEVEL 1 (
    echo "Error: Downloading premake license failed!"
    exit 2
)

powershell -NoProfile -NonInteractive -Command "Expand-Archive -LiteralPath external/premake/bin/premake.zip -DestinationPath external/premake/bin -Force"
IF ERRORLEVEL 1 (
    echo "Error: Extraction failed!"
    exit 2
)

powershell -NoProfile -NonInteractive -Command "Remove-Item -Path external/premake/bin/premake.zip"

powershell -NoProfile -NonInteractive -Command "if ((Get-FileHash -LiteralPath external/premake/bin/premake5.exe -Algorithm SHA256).Hash -eq \"%PREMAKE_HASH%\") { exit 0 } else { exit 1 }"
IF ERRORLEVEL 1 (
    echo "Error: Hash verification failed!"
    powershell -NoProfile -NonInteractive -Command "Remove-Item -Path external/premake/bin/premake5.exe"
    exit 2
)

exit /B 0

cd %~dp0

:start

IF EXIST "external/premake/bin/premake5.exe" (
    external\premake\bin\premake5.exe --version >NUL
    IF NOT ERRORLEVEL 1 (
        goto runpremake
    )
)

echo "Installing premake"
call:InstallPremake
goto runpremake

:runpremake
git submodule update --init --recursive
external\premake\bin\premake5.exe vs2022
PAUSE
