@echo off
g++ helloworld.cpp -o helloworld.exe
if %errorlevel% neq 0 goto :error

helloworld.exe PowerGrid/grid-6-7 out.txt -v
if %errorlevel% neq 0 goto :error

goto :EOF

:error
echo An error occurred during the execution of the script.
pause