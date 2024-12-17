//Libraries Needed:
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "edge_distance.h"
#include "branch_and_bound.h"
#include <load_nodes_from_file.h>
#include <tgmath.h>

#include "address_generator.h"
#include "timer.h"

#ifdef _WIN32
#include <windows.h>
void enable_virtual_terminal_processing() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

//main() function initializes the problem's data and calls the TSP() function to solve the Traveling
//Salesman Problem (TSP). Once the TSP() function finds the optimal route, main() function prints
//the minimum cost and the optimal route:
int main(void) {

#ifdef _WIN32
    enable_virtual_terminal_processing();
#endif

    // Store the filepath of the input document in a variable
    const char* filepath = "assets/addresses.csv";

    // This function generates a random list of addresses
    // The function uses the filepath and an integer representing the amount of nodes wanted
    generate_addresses_float(filepath, 20, 2);

    // Get the size of the array, using "get_delivery_point_count()"
    // This function counts the number of nodes in the file
    const int node_count = get_node_count(filepath);
    if (node_count < 0) {
        printf("Error loading nodes");
        exit(EXIT_FAILURE);
    }

    // If number of nodes is below or equal to two, print a default statement
    if (node_count <= 2) {
        switch (node_count) {
            case 0: {
                printf("Error: Input file has no nodes \n");
                exit(EXIT_SUCCESS); // Exit the program
            }
            case 1: {
                printf("Error: Input only has one node \n");
                exit(EXIT_SUCCESS);
            }
            case 2: {
                printf("Error: Graph only has two nodes. \n");
                exit(EXIT_SUCCESS); // Exit the program
            }
            default: printf("Unexpected error: node_count is %lf which is invalid", node_count);
        }
    }

    Node nodes_array[node_count];

    // Declaring the 2D-array, "matrix[][]", which is going to represent the graph,
    // with each value inside of matrix[i][j], representing the cost of traveling from node "i" to node "j".

    double matrix[node_count][node_count];

    // Load (x and y) coordinates from file into node in the array.
    load_nodes_from_file(filepath, nodes_array, node_count);

    // Running "calculate_edges()" function to assign the "matrix" with distances between all the give nodes.
    calculate_edges(node_count, matrix, nodes_array);

    // Define variables for final_result, the distance covered, and final_route, an array representing the best route
    // Final_result is set to maximum integer value, and the size of final_route is set to node_count.
    double final_result = INT_MAX;
    int final_route[node_count];

    // Running the TSP() function, with the "matrix[][]" array as an input parameter:
    // Inside the TSP() function, the algorithm calculates the optimal route, that visits each
    // node exactly once and returns to the starting node, minimizing the travel cost.
    // During this process, the function updates "final_result" through a pointer with the minimum cost,
    // and "final_route" with the sequence of nodes in that optimal route.
    clock_t start = clock(); // start the timer
    TSP(node_count, matrix, &final_result, final_route);

    // After the TSP() function completes, main() function outputs the minimum cost and the optimal route:

    // Prints the lowest travel cost found.
    printf("Minimum cost: %lf\n", final_result);

    // Prints the sequence of nodes in the optimal route:
    // This for-loop iterates through the route, showing a complete route cycle,
    // that begins and ends in the starting node:
    printf("Path Taken: ");
    for (int i = 0; i <= node_count; i++) {
        printf("%d ", final_route[i]);
    }

    // Print time it takes to run the program
    printf("\n");
    print_execution_time(start);

    //Stops the program successfully:
    return EXIT_SUCCESS;
}

