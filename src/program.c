
//Libraries Needed:
#include <stdio.h>
#include <stdlib.h>
#include "branch_and_bound.h"



//main() function initializes the problem's data and calls the TSP() function to solve the Traveling
//Salesman Problem (TSP). Once the TSP() function finds the optimal route, main() function prints
//the minimum cost and the optimal route:
int main(void) {

    //Initializing the 2D-array, "matrix[N][N]", which represents the graph, where "N" is the
    //number of nodes. "matrix[N][N]" is the cost of traveling from node "i" to node "j". A value
    //of 0 along the diagonal (matrix[i][i] = 0) indicates there is no cost to stay in the same node:
    int matrix[N][N] = { {0, 10, 15, 20},
                         {10, 0, 35, 25},
                         {15, 35, 0, 30},
                         {20, 25, 30, 0} };

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
