
//Libraries Needed:
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "branch_and_bound.h"

#include <stdbool.h>
#include <stdio.h>
#include <tgmath.h>


//TSP() function sets up the initial values and calls the recursion function, TSP_Recursion() to solve
//the Traveling Salesman Problem (TSP) using the Branch and Bound algorithm. The function initialized
//the needed structures, calculates the initial bound and starts the recursive exploration to find
//the optimal route (in this case the fastest route, which means the route that has the lowest cost):
void TSP(int size, double matrix[size][size], double* final_result, int final_route[]) {
    printf("\033[32;1mLoading ... \033[0m \n");
    fflush(stdout);

    int visited[size]; // Keeps track of visited nodes
    int current_route[size + 1]; // size + 1 to have space for appending the starting node to end
    double upper_bound = 0; //Initially set current_bound to 0.

    memset(current_route, -1, sizeof(current_route)); // -1 indicates a blanc space in the array
    memset(visited, 0, sizeof(visited)); // 0 = "not visited", 1 = "visited"

    //The TSP route is initialized to start from node 0:
    visited[0] = 1;         //visited[0] = 1; marks node 0 as visited.
    current_route[0] = 0;   //current_route[0] = 0; places node 0 at the beginning of "current_route[]".

    // Use calculate upper bound function
    upper_bound = calculate_upper_bound(size, matrix, visited, 0);

    //Run the TSP_Recursion() function to begin recursion exploration:
    TSP_Recursion(size, matrix, upper_bound, 0, 1,
        current_route, final_result, visited, final_route);

}


//TSP_Recursion() function is the building stone of the recursive Branch and Bound algorithm used to
//solve the Traveling Salesman Problem (TSP). This function explores potential routes recursively,
//calculates cost, and excludes routes, that is greater in cost than the current best known
//solution ("final_result"). It updates the best route and cost as it finds better (faster) solutions:

void TSP_Recursion(int size, double matrix[size][size], double upper_bound, double current_weight,
    int level, int current_route[], double *final_result, int visited[], int final_route[]) {
    if (level == size) { // Check is all nodes have been visited

            //Initializing the variable "current_result"
            double current_result = current_weight + matrix[current_route[level - 1]][current_route[0]];

            //Check if "current_result" is less than "final_result"
            if (current_result < *final_result) {
                copy_To_Final(size, current_route, final_route);
                *final_result = current_result;
            }

        //After updating "final_result" and "final_route"
        return;
    }

    // It all nodes have not been visited
    for (int i = 0; i < size; i++) {

        // Consider travel cost to the next not visited node
        if (matrix[current_route[level - 1]][i] != 0 && visited[i] == 0) {

            // Store the current bound in temp
            double temp = upper_bound;

            // Add the cost of traveling to node[i] to current_weight
            current_weight += matrix[current_route[level - 1]][i];

            // Add node[i] to the rute
            current_route[level] = i;
            visited[i] = 1;

            // Calculate upper bound from this position
            upper_bound = calculate_upper_bound(size, matrix, visited, i);


            // If true, prune this branch from the tree
            if (upper_bound + current_weight < *final_result) {

                // - "TSP_Recursion()": Is called to move to the next level:
                TSP_Recursion(size, matrix, upper_bound, current_weight, level + 1,
                    current_route, final_result, visited, final_route);
            }

            // To prune the branch, backtrack one node
            current_weight -= matrix[current_route[level - 1]][i];
            upper_bound = temp;
            visited[i] = 0;
        }
    }
}

double calculate_upper_bound(int size, double matrix[size][size], int visited[], int i) {
    double total_cost = 0;
    double num_visited = 1;
    int current_node = i;
    int MST_visited[size];

    // Copy the current state of visited[] to MST_visited[] for local usa
    for (int m = 0; m < size; m++) {
        MST_visited[m] = visited[m];
    }

    // Run until all nodes have been visited
    while (num_visited < size) {
        int nearest_neighbor = -1;
        double min_cost = MAXFLOAT;

        // Find the nearest unvisited neighbor
        for (int j = 0; j < size; j++) {
            if (MST_visited[j] == 0 && matrix[current_node][j] < min_cost) {
                     min_cost = matrix[current_node][j];
                      nearest_neighbor = j;
            }
        }

            // If all nodes in the spanning graph have been marked as visited
        if (nearest_neighbor == -1) {
            break;
       }

       // Update total cost and move to the nearest neighbor
       total_cost += min_cost;
       current_node = nearest_neighbor;
       MST_visited[current_node] = 1;
       num_visited++;
    }


    // Add the cost of traveling to node "0"
    total_cost += matrix[current_node][0];
    return total_cost;
}


//copy_To_Final() function is simple utility function, that copies a temporary route (stored in
//"current_route[]") to the global array final_route[], which stores the best route found so far.
//This function is called whenever the algorithm finds a complete route with a lower cost than the
//current minimum ("final_result"), so that the best solution is always saved:

//Input parameters:
//current_route[] = Holds the current route.

void copy_To_Final(int size, int current_route[], int final_route[]) {

    //This for-loop copies each node from "current_route[]" to "final_route[]". Iterates through
    //the first elements in "current_route[]" up to "i < size", which represents nodes visited in the current
    //route, and copies them into "final_route[]":
    for (int i = 0; i < size; i++) {
        final_route[i] = current_route[i];

    }

    //After the for-loop has been terminated it sets "final_route[]" to "current_route[0]". This
    //completes the route, by returning to the starting node, so "final_route[]" will now represent
    //a full route cycle:
    final_route[size] = current_route[0];
}


