@echo off
gcc main.c ./../utils/cnumpy/cnumpy.c ./../utils/csv/csv.c ./linear_regression.c  -o main
echo Build complete.
main.exe
echo Run complete.
del main.exe