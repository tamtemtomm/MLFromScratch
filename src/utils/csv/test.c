#include "csv.h"

int main(void)
{
    
    Matrix mat = csv_read("csv.csv", true);
    matrix_print(&mat);

    csv_write("new_csv.csv", &mat);

    return 0;
}