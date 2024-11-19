//
// Created by Jacob Larsen on 13/11/2024.
//

#include "load_nodes_from_file.h"
#include <stdio.h>

int get_delivery_point_count(const char *filename) {
    // Create a counter to return, count in initialized as 1, because the last line does not contain a linebreak "\n"
    int count = 1;

    // Using the implemented FILE struct from C to create a pointer to a files location
    FILE* filepointer = fopen(filename, "r");

    // If the file is not found, print it to the user
    if (!filepointer) {
        printf("Can't open file\n");
        printf("filename %s", filename);
        return -1;
    } else {
        for (char c = getc(filepointer); c != EOF; c = getc(filepointer))
            if (c == '\n') // Increment count if this character is newline
                count += 1;

        // Close the file and return count
        fclose(filepointer);
        printf("The number of nodes is: %d\n", count);
        return count;
    }
}


void load_nodes_from_file(const char *inputfile, Node nodes_array[], int node_count) {
    // Using the implemented FILE struct from C to create a pointer to a files location
    FILE* fp = fopen(inputfile, "r");

    // If the file is not found, print an error to the user
    if (!fp) {
        printf("Error: Filepath not found\n");
        printf("filename %s", inputfile);
    }

    char buffer[15];


    for (int i = 0; i < node_count; i++) {

        fgets(buffer, 15, fp);

        sscanf(buffer, "%d,%d", &nodes_array[i].x, &nodes_array[i].y);

        printf("Node %d: (%d,%d)\n",i, nodes_array[i].x, nodes_array[i].y);
    }
}
