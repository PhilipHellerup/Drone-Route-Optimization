//
// Created by Jacob Larsen on 13/11/2024.
//

#include "load_nodes_from_file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_nodes_from_file(const char *filename, Node nodes[]) {
    // Using the implemented FILE struct from C to create a pointer to a files location
    FILE* fp = fopen(filename, "r");

    // If the file is not found, print it to the user
    if (!fp) {
        printf("Can't open file\n");
        printf("filename %s", filename);
    }

    else {
        // We create a buffer to store the information of each line of the .CSV file.
        // Each line can be max 1024 characters
        char buffer[1024];

        // Two counter are initialized to keep track of the row and colum
        int row = 0;
        int column = 0;

        // fgets() read one line of the document into the buffer. Thw while loop runs until it encounters and empty row.
        // Each time the while loop is run, row is incremented by one to parse through the file one row at a time.
        // The first row is row 1
        while (fgets(buffer, 1024, fp)) {
            column = 0;
            row++;

            // Skip the header
            if (row == 1)
                continue;

            // Using strtok() to split buffer at each comma ",", to return the first value of the x-coordinate
            char* value = strtok(buffer, ",");

            // This while loop integrates through the data of each row, and assings the x and y value of each node
            while (value) {
                // Convert the entire string to an integer using atoi()
                int value_int = atoi(value);

                // Column 1
                if (column == 0) {
                    nodes[row-2].x = value_int; // Assign x-value
                }

                // Column 2
                else if (column == 1) {
                    nodes[row-2].y = value_int; // Assign y-value
                }

                // Reads the next data from the line after comma ",", into value
                value = strtok(NULL, ",");
                // Colum is incremented as we are now working with the value in the next colum.
                column++;
            }
        }

        // Close the file
        fclose(fp);

        // Print the x and y value for each node
        for (int i = 0; i < N; i++) {
            printf("Node[%d].x = %d\n",i, nodes[i].x);
            printf("Node[%d].y = %d\n",i, nodes[i].y);
        }
    }
}
