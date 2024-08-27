#ifndef CSV_H
#define CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double **read_csv(char *filepath, int N_SAMPLES, int N_FEATURES)
{
    // Initialize few variables (Buffer and a couples of pointers)
    char buffer[1000];
    char *data;
    char *ptr;
    double value;

    // Initialize array of data
    double **X = (double **)malloc(N_SAMPLES * sizeof(double *));
    for (int i = 0; i < N_SAMPLES; i++)
    {
        X[i] = (double *)malloc(N_FEATURES * (sizeof(double)));
    }

    // Open the file
    FILE *fileData = fopen(filepath, "r");

    // Check if it's null
    if (fileData == NULL)
    {
        printf("Error could not open file\n");
        exit(-1);
    }
    // else
    // {
    //     printf("I was able to open the file\n");
    // }

    // Get the first line (Column names)
    fgets(buffer, sizeof(buffer), fileData);

    // Iterate trough the rows
    int i = 0;
    while (fgets(buffer, sizeof(buffer), fileData))
    {
        // Get the id
        strtok(buffer, ",");
        for (int j = 0; j < N_FEATURES; j++)
        {
            // Get the data
            data = strtok(NULL, ",");
            // Convert into double
            value = strtod(data, &ptr);
            // Append into arrays
            X[i][j] = value;

            // printf("%.2lf\n", value);
        }
        i++;
    }

    // Close the file
    fclose(fileData);

    return X;
}

char **read_csv_label(char *filepath, int N_SAMPLES, int N_FEATURES)
{
    // Initialize some variables
    char buffer[1000];
    char *data;
    double value;

    // Initialize array of data
    char **y = (char **)malloc(N_SAMPLES * sizeof(char *));

    // Open the file
    FILE *fileData = fopen(filepath, "r");

    // Check if it's null
    if (fileData == NULL)
    {
        printf("Error could not open file\n");
        exit(-1);
    }
    // else
    // {
    //     printf("I was able to open the file\n");
    // }

    // Get the first line (Column names)
    fgets(buffer, sizeof(buffer), fileData);

    // Iterate trough the data
    int i = 0;
    while (fgets(buffer, sizeof(buffer), fileData))
    {
        // Get the id
        strtok(buffer, ",");
        for (int j = 0; j < N_FEATURES; j++)
        {
            // Get the feature value
            strtok(NULL, ",");
        }
        // Get the label
        data = strtok(NULL, ",");

        // Trim any newline characters
        data[strcspn(data, "\r\n")] = 0;

        // Allocate memory for the label and copy it
        y[i] = (char *)malloc(strlen(data) + 1);
        strcpy(y[i], data);

        i++;
    }

    // Close the file
    fclose(fileData);

    return y;
}

int convert_label_string_to_int(char* label_string){
    if (strcmp(label_string, "Iris-setosa") == 0) return 0;
    else if(strcmp(label_string, "Iris-versicolor") == 0) return 1;
    else if(strcmp(label_string, "Iris-virginica") == 0) return 2;
    else return -1;  // Return -1 to indicate an error if the label doesn't match
}

#endif