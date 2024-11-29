//
// Created by OEM on 22-11-2024.
//
#include <stdio.h>
#include "address_generator.h"
#include <time.h>
#include <stdlib.h>


void generate_addresses(const char *filepath, int nodes, int max_size) {

    household households[nodes];

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
    for (int i = 0; i < nodes; i++) {
        // Generates random integer from 0 -> N + 1 (N + 1 can be any chosen value)
        do {
            households[i].x = rand() % max_size+1;
            households[i].y = rand() % max_size+1;
            // Check if the crated node is too close to another, if so, create a new one
        } while (check_distance(households, i, households[i].x, households[i].y));

        // Prints coordinates to the file
        fprintf(filepointer, "%d,%d \n", households[i].x,households[i].y);
    }

    fclose(filepointer);
}

// Checks if a created node is too close to another
int check_distance(household households[], int household_count, int x, int y) {
    for (int i = 0; i < household_count; i++) {
        // If the x and y both coordinates are within 20 of another node, return 1.
        if (households[i].x > x - 20 && households[i].x < x + 20
            && households[i].y > y - 20 && households[i].y < y + 20) {
            return 1;
        }
    }
    return 0;
}
