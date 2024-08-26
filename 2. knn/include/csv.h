#ifndef CSV_H
#define CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double** read_csv(char* filepath, int N_SAMPLES, int N_FEATURES){
    char buffer[1000];
    char *data;
    char *ptr;
    double value;

    // Initialize array of data
    double** X = (double **)malloc(N_SAMPLES * sizeof(double *));
    for (int i = 0; i< N_SAMPLES; i++){
        X[i] = (double *)malloc(N_FEATURES * (sizeof(double)));
    }

    FILE *fileData = fopen(filepath, "r");
    
    // Check if it's null
    if(fileData == NULL){
        printf("Error could not open file\n");
        exit(-1);
    } else {
        printf("I was able to open the file\n");
    }

    // Get the first line (Column names)
    fgets(buffer, sizeof(buffer), fileData);

    // Get the data
    int i = 0;
    while(fgets(buffer, sizeof(buffer), fileData)){
        // Get the id
        strtok(buffer, ",");
        for (int j = 0; j < N_FEATURES; j++){
            data = strtok(NULL, ",");
            value = strtod(data, &ptr); 
            
            X[i][j] = value;
            
            // printf("%.2lf\n", value);
            
        }
        i++;
    }

    fclose(fileData);

    return X;
}

#endif