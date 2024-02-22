@echo off


windres resources/res.rc -O coff -o resources/res.o
gcc -O1 -s src/*.c resources/res.o -o vuvuria.exe -mwindows
