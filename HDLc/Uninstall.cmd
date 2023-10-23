@echo off
cls
title HDLc
echo Uninstalling...
reg delete HKLM\Software\Microsoft\Windows\CurrentVersion\Run /v HDLc /f
taskkill /F /IM HDLc.exe
pause