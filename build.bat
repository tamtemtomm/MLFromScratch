@echo off
gcc main.c ./src/utils/cnumpy/cnumpy.c ./src/utils/csv/csv.c ./src/linear_regression/linear_regression.c  -o main
echo Build complete.
main.exe
echo Run complete.
del main.exe