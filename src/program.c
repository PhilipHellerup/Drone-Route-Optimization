
//Libraries Needed:
#include <stdio.h>
#include <stdlib.h>
#include "edge_distance.h"
#include "branch_and_bound.h"

// Function to load node coordinates from a text file
void load_nodes_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read each line as "node_id x y"
    int id, x, y;
    for (int i = 0; i < N && fscanf(file, "%d %d %d", &id, &x, &y) == 3; i++) {
        nodes[i].x = x;
        nodes[i].y = y;
    }
    fclose(file);
}

//main() function initializes the problem's data and calls the TSP() function to solve the Traveling
//Salesman Problem (TSP). Once the TSP() function finds the optimal route, main() function prints
//the minimum cost and the optimal route:
int main(void) {

    // Load node coordinates from file
    load_nodes_from_file("nodes.txt");

    //Declaring the 2D-array, "matrix[N][N]", which is going to represent the graph, where "N" is the
    //number of nodes. "matrix[N][N]" is the cost of traveling from node "i" to node "j".
    int matrix[N][N];

    //Running "calculate_edges()" function to assign the "matrix" with distances between all the give nodes.
    calculate_edges(matrix);

    //Running the TSP() function, with the "matrix[][]" array as an input parameter:

    //Inside the TSP() function, the algorithm calculates the optimal route, that visits each
    //node exactly once and returns to the starting node, minimizing the travel cost.

    //During this process, the function updates "final_result" with the minimum cost and "final_route"
    //with the order of nodes in that optimal route.
    TSP(matrix);

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
