@echo off
gcc test.c cnumpy.c -o test.exe -lm
echo Build complete.
test.exe
echo Run complete.
del test.exe