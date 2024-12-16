//
// Created by Jacob Larsen on 13/11/2024.
//

#include "load_nodes_from_file.h"
#include <stdio.h>
#include <tgmath.h>
#include "stdlib.h"

// This functions takes in the filepath to the input file as its only parameter.
// Each newline symbol ("\n") is counted, to return the number of nodes in the file
// Hence the last row does not contain a newline, we do not skip the header row.

int get_node_count(const char *filename) {
    // Using the implemented FILE struct from C to create a pointer to a files location
    FILE* filepointer = fopen(filename, "r");

    // If the file is not found, print it to the user and return
    if (!filepointer) {
        printf("Can't open file\n");
        printf("filepath %s", filename);
        return -1;
    }

    // Create a counter to return the total number og nodes
    int count = -1;
    // Each character in the file is read, until it is equal to the value of "EOF" (end-of-file)
    for (char c = getc(filepointer); c != EOF; c = getc(filepointer))
        if (c == '\n') // Increment count for each newline in the file
            count += 1;

    // Close the file and return count
    fclose(filepointer);
    printf("The number of nodes is: %d\n", count); // Print the number of nodes to the user
    return count;
}

// This function takes in the filepath og the inputfile, the nodes array, and the node_count as parameters
// Each line of the input file is read using fgets() and sscanf(), to give a value to each node in the nodes_array
void load_nodes_from_file(const char *inputfile, Node nodes_array[], int node_count) {
    // Using the implemented FILE struct from C to create a pointer to a files location
    FILE* fp = fopen(inputfile, "r");

    // If the file is not found, print an error to the user, and return.
    if (!fp) {
        printf("Error: Filepath not found\n");
        printf("filename %s", inputfile);
        return;
    }

    // Setting a buffer to read each line onto, the buffer is set to hold 100 characters
    char buffer[100];
    fgets(buffer, 100, fp); // Read and discard the first line

    // Iterating over each line, from the second line, and reads each coordinate pair into the nodes_array.
    for (int i = 0; i < node_count; i++) {
        double x_value = 0.0, y_value = 0.0;

        // Read a line from the file
        if (!fgets(buffer, sizeof(buffer), fp)) {
            fprintf(stderr, "Error: Failed to read line %d from input file\n", i + 1);
            exit(EXIT_FAILURE);
        }
        // Scan the coordinates from a line
        if (sscanf(buffer, "%lf,%lf", &x_value, &y_value) != 2) {
            fprintf(stderr, "Error: Line %d is not formatted correctly: %s(should be x_value,y_value)", i + 1, buffer);
            exit(EXIT_FAILURE);
        }
        // Round and assign the values to each node
        nodes_array[i].x = (x_value);
        nodes_array[i].y = (y_value);
        // Print the node details
        printf("Node %d: (%.3lf, %.3lf)\n", i, nodes_array[i].x, nodes_array[i].y);
    }
}
