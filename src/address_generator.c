//
// Created by OEM on 22-11-2024.
//
#include <stdio.h>
#include "address_generator.h"
#include <time.h>
#include <stdlib.h>

void generate_addresses(const char *filepath, int n, int size) {
    FILE* filepointer = fopen(filepath, "w");

    // If the file is not found, print to the user and EXIT
    if (!filepointer) {
        printf("Can't open file\n");
        printf("filename %s", filepath);
        exit(EXIT_FAILURE);
    }
    // Print first line of the file
    fprintf(filepointer, "x-value, y-value \n");
    srand(time(NULL));

    // Generates the correct number of random coordinates
    for (int i = 0; i < n; i++) {
        // Generates random integer from 0 -> N + 1 (N + 1 can be any chosen value)
        int x = rand() % size+1;
        int y = rand() % size+1;

        // Prints coordinates to the file
        fprintf(filepointer, "%d,%d \n", x,y);
    }
    fclose(filepointer);
}

void generate_addresses_float(const char* filepath, int n, int size) {
    FILE* filepointer = fopen(filepath, "w");

    // If the file is not found, print to the user and EXIT
    if (!filepointer) {
        printf("Can't open file\n");
        printf("filename %s", filepath);
        exit(EXIT_FAILURE);
    }
    // Print first line of the file
    fprintf(filepointer, "x-value, y-value \n");
    srand(time(NULL));

    // Generates the correct number of random coordinates
    for (int i = 0; i < n; i++) {
        // Generates random integer from 0 -> N + 1 (N + 1 can be any chosen value)
        double x = (float)rand()/(float)(RAND_MAX) * size;
        double y = (float)rand()/(float)(RAND_MAX) * size;

        // Prints coordinates to the file
        fprintf(filepointer, "%.3lf,%.3lf \n", x,y);
    }
    fclose(filepointer);
}
