@echo off
gcc test.c csv.c ./../cnumpy/cnumpy.c -o test.exe
echo Build complete.
test.exe
echo Run complete.
del test.exe
del new_csv.csv