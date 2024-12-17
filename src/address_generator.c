#include <stdio.h>
#include "address_generator.h"
#include <time.h>
#include <stdlib.h>


// Function to generate a file with random x and y float coordinates.
/**
 * @param filepath Path to the output file.
 * @param n Number of random coordinate pairs to generate.
 * @param size Upper limit for the random values.
 */
void generate_addresses_float(const char* filepath, int n, int size) {
    // Open the file in write mode ("w").
    FILE* filepointer = fopen(filepath, "w");

    // Check if the file was successfully opened.
    if (!filepointer) {
        printf("Can't open file\n");
        printf("filename %s", filepath);
        exit(EXIT_FAILURE);
    }
    // Print the header of the file
    fprintf(filepointer, "x-value, y-value \n");

    // Initialize the random number generator using the current time so the numbers generated are different each time the program runs.
    srand(time(NULL));

    // Generate 'n' random coordinate pairs and write them to the file.
    for (int i = 0; i < n; i++) {
        // Generate random floating-point x and y values in the range [0, size].
        double x = (float)rand()/(float)(RAND_MAX) * size;
        double y = (float)rand()/(float)(RAND_MAX) * size;

        // Write the generated x and y values to the file with 3 decimal precision.
        fprintf(filepointer, "%.3lf,%.3lf \n", x,y);
    }
    // Close the file to save all written data and free up system resources.
    fclose(filepointer);
}

