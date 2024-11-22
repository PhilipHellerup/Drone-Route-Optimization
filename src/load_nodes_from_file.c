//
// Created by Jacob Larsen on 13/11/2024.
//

#include "load_nodes_from_file.h"
#include <stdio.h>

// This functions takes in the filepath to the input file as its only parameter.
// Each newline symbol ("\n") is counted, to return the number of nodes in the file
// Hence the last row does not contain a newline, we do not skip the header row.
int get_delivery_point_count(const char *filepath) {
    // Using the implemented FILE struct from C to create a pointer to a files location
    FILE* filepointer = fopen(filepath, "r");

    // If the file is not found, print it to the user and return
    if (!filepointer) {
        printf("Can't open file\n");
        printf("filename %s", filepath);
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

    // Skipping the firs line
    fgets(buffer, 100, fp); // Read and discard the first line

    // Iterating over each line, from the second line, and reads each coordinate pair into the nodes_array.
    for (int i = 0; i < node_count; i++) {

        fgets(buffer, 15, fp); // Reads a line into the butter

        sscanf(buffer, "%d,%d", &nodes_array[i].x, &nodes_array[i].y); // Scans the values of that line, into a node

        printf("Node %d: (%d,%d)\n",i, nodes_array[i].x, nodes_array[i].y); // Prints the node to the user
    }
}
