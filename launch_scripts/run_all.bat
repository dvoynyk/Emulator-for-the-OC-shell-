@echo off
cd /d "%~dp0..\build\Desktop_Qt_6_11_2_MinGW_64_bit_Debug"
shell-emulator.exe --vfs "..\vfs\filesystem.zip" --script "..\scripts\test_all.txt"
pause