//
// Created by OEM on 22-11-2024.
//
#include <stdio.h>
#include "address_generator.h"
#include <time.h>
#include <stdlib.h>
void generate_addresses_float(const char* filepath, int n, int size) {
    FILE* filepointer = fopen(filepath, "w");

    // If the file is not found, print to the user and EXIT
    if (!filepointer) {
        printf("Can't open file\n");
        printf("filename %s", filepath);
        exit(EXIT_FAILURE);
    }
    // Print the header of the file
    fprintf(filepointer, "x-value, y-value \n");
    srand(time(NULL));

    // Generate the specified number of coordinate sets
    for (int i = 0; i < n; i++) {
        // Generates random float values from 0 -> size, (Size is specified in the function call)
        double x = (float)rand()/(float)(RAND_MAX) * size;
        double y = (float)rand()/(float)(RAND_MAX) * size;

        // Prints coordinates to the file
        fprintf(filepointer, "%.3lf,%.3lf \n", x,y);
    }
    fclose(filepointer);
}

