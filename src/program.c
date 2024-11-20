
//Libraries Needed:
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "edge_distance.h"
#include "branch_and_bound.h"
#include <load_nodes_from_file.h>


//main() function initializes the problem's data and calls the TSP() function to solve the Traveling
//Salesman Problem (TSP). Once the TSP() function finds the optimal route, main() function prints
//the minimum cost and the optimal route:
int main(void) {
    // Store the filepath of the input document in a variable
    const char* filepath = "assets/addresses.csv";

    // Get the size of the array, using "get_delivery_point_count()"
    const int node_count = get_delivery_point_count(filepath);

    // Declaring an array to store the delivery coordinates for all the households in the list
    Node nodes_array[node_count];

    //Declaring the 2D-array, "matrix[][]", which is going to represent the graph
    //number of nodes. "matrix[][]" is the cost of traveling from node "i" to node "j".
    int matrix[node_count][node_count]; // Fix this.

    // Load (x and y) coordinates from file into node in the array
    load_nodes_from_file(filepath, nodes_array, node_count);

    //Running "calculate_edges()" function to assign the "matrix" with distances between all the give nodes.
    calculate_edges(matrix, nodes_array);

    // Define variables for final_result, the distance covered, and final_route, an array representing the best route
    int final_result = INT_MAX;
    int final_route[node_count];

    //Running the TSP() function, with the "matrix[][]" array as an input parameter:

    //Inside the TSP() function, the algorithm calculates the optimal route, that visits each
    //node exactly once and returns to the starting node, minimizing the travel cost.

    //During this process, the function updates "final_result" with the minimum cost and "final_route"
    //with the order of nodes in that optimal route.
    TSP(node_count, matrix, &final_result, final_route);

    //After the TSP() function completes, main() function outputs the minimum cost and the optimal route:

    //Prints the lowest travel cost found.
    printf("Minimum cost: %d\n", final_result);

    //Prints the order of nodes in the optimal route:
    printf("Path Taken: ");

    //Given that "final_route[N]" is set to "final_route[0]" (the starting node), this for-loop
    //iterates through the route, showing a complete route cycle, that
    //begins and ends in the starting node:
    for (int i = 0; i <= N; i++) {
        printf("%d ", final_route[i]);
    }

    //Stops the program successfully:
    return EXIT_SUCCESS;
}

