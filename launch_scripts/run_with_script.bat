@echo off
cd /d "%~dp0..\build\Desktop_Qt_6_11_2_MinGW_64_bit_Debug"
shell-emulator.exe --script "..\scripts\test_basic.txt"
pause