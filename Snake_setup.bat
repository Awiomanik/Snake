@ECHO OFF
:: Welcome message
ECHO Welcome to the Snake Setup Wizard!
ECHO This wizard will help you install the Snake game on your system.
ECHO.

:: Check IF g++ is installed
ECHO Checking for G++ compiler...
g++ --version >NUL 2>&1
IF ERRORLEVEL 1 (
    ECHO G++ compiler is not installed or not found in PATH.
    ECHO Please install G++ and add it to PATH before running this script.
    PAUSE 
    EXIT /b
)

:: Compile the resource file (icon)
ECHO Compiling resources...
windres src/Snake.rc -O coff -o src/Snake_res.o
IF ERRORLEVEL 1 (
    ECHO Resource compilation failed. Check src/Snake.rc and src/icon.ico.
    PAUSE 
    EXIT /b
)

:: Compile the program
ECHO Compiling the game...
g++ src/Snake_classes_bodies.cpp src/Snake_main.cpp src/Snake_res.o -o Snake.exe -lwinmm -lgdi32
IF ERRORLEVEL 1 (
    ECHO Compilation failed. Check your source files for errors.
    PAUSE 
    EXIT /b
)
ECHO.
ECHO Compilation successful!
ECHO Snake.exe has been created in the current directory.
ECHO.

:: Whethetr the user wants to create a desktop shortcut
FOR /f "usebackq" %%d IN (`powershell -NoProfile -Command ^
    "[Environment]::GetFolderPath('Desktop')"`) DO SET desktop=%%d
SET "shortcut_choice="
SET "shortcut_path=%desktop%\Snake.lnk"
SET "target_path=%cd%\Snake.exe"

:shortcut_prompt
SET /p "shortcut_choice=Do you want to create a desktop shortcut for Snake? (y/n): "
IF /i "%shortcut_choice%"=="y" (
    powershell -ExecutionPolicy Bypass -Command ^
        "$ws = New-Object -ComObject WScript.Shell; $shortcut = $ws.CreateShortcut('%desktop%\Snake.lnk'); $shortcut.TargetPath = '%cd%\Snake.exe'; $shortcut.WorkingDirectory = '%cd%'; $shortcut.Save(); Write-Host 'Shortcut created successfully.'"
    IF ERRORLEVEL 1 (
        ECHO Failed to create desktop shortcut. 
        ECHO.
        PAUSE 
        EXIT /b
    )
) ELSE IF /i "%shortcut_choice%"=="n" (
    ECHO Skipping shortcut creation.
    ECHO.
) ELSE (
    ECHO Invalid input. Please enter 'y' or 'n'.
    GOTO shortcut_prompt
)

:: Ask IF the user wants to run the program immediately
SET "run_choice="
:run_prompt
SET /p "run_choice=Do you want to run the Snake game now? (y/n): "
IF /i "%run_choice%"=="y" (
    ECHO Starting the game...
    START "" "%cd%\Snake.exe"
) ELSE IF /i "%run_choice%"=="n" (
    ECHO You can run the game later by executing Snake.exe.
    :: Finish
    ECHO.
    ECHO Setup complete! Thank you for using the Snake Setup Wizard.
    PAUSE 
) ELSE (
    ECHO Invalid input. Please enter 'y' or 'n'.
    GOTO run_prompt
)

EXIT /b
