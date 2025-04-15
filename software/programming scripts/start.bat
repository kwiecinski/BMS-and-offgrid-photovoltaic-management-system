@echo off
start "UART" powershell -NoExit -Command "python uart.py"
start "PROG" powershell -NoExit -Command "python program.py"