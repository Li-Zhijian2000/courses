@echo off
:loop
    python3 data.py
    g++ b.cpp -o my
    my < input.txt > my.txt
    g++ std.cpp -o std
    std < input.txt > std.txt
    fc my.txt std.txt
if not errorlevel 1 goto loop  
pause
goto loop