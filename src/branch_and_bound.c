
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

void TSP(int size, int matrix[size][size],int* final_result, int final_route[]) {

    int visited[size]; // Keep track of visited nodes
    int current_route[size + 1]; // Keep track of the current route
    int current_bound = 0; // Curren bound initially set to 0.

    memset(current_route, -1, sizeof(current_route)); //Sets all the elements in current_route[] to -1
    memset(visited, 0, sizeof(visited)); // Set all elements in visited to "0"

    //This for-loop iterates over all nodes and calculates "current_bound"
    for (int i = 0; i < size; i++) {

        // Smallest and second-smallest edge weight from each node is added
        current_bound += (first_minimum(size, matrix, i) + second_minimum(size, matrix, i));
    }

    // Calculate current bound
    current_bound = (current_bound % 2) ? current_bound / 2 + 1 : current_bound / 2;

    //The TSP route is initialized to start from node 0:
    visited[0] = 1;         //visited[0] = 1; marks node 0 as visited.
    current_route[0] = 0;   //current_route[0] = 0; places node 0 at the beginning of "current_route[]".

    //Run the TSP_Recursion() function to begin recursion exploration:
    TSP_Recursion(size, matrix, current_bound, 0, 1,
        current_route, final_result, visited, final_route);
}


//first_minimum() function finds the minimum edge (smallest cost) from a given node to any other node.
//This function helps in calculating a lower bound in the Branch and Bound approach to
//the Traveling Salesman Problem (TSP), which is used to determine if certain routes should be
//explored further or excluded/pruned:

//Input parameters:
//matrix[][] = The adjacency matrix of the graph, where matrix[i][j] represent the cost of going
//from node i to node j.
//i = The index of the node for which we want to find the minimum outgoing edge cost.

int first_minimum(int size, int matrix[size][size], int i) {
    int first = INT_MAX;

    // Check travel cost to all nodes
    for (int j = 0; j < size; j++) {

        // Find the node with the shortest distance, which is not to itself
        if (matrix[i][j] < first && i != j) {
            first = matrix[i][j];
        }
    }
    return first; // Return lowest cost
}


//second_minimum() function finds the second-smallest edge (cost) from a given node to any other node.
//This function is useful in calculating a tighter bound in the Branch and Bound approach for
//the Traveling Salesman (TSP) by providing additional information about the second-lowest cost edge,
//which helps to better estimate the minimum cost for a route.

//Input parameters:
//matrix[][] = The adjacency matrix of the graph, where matrix[i][j] represent the cost of going
//from node i to node j.
//i = The index of the node for which we want to find the second minimum outgoing edge cost.

int second_minimum(int size, int matrix[size][size], int i) {
    int first = INT_MAX;
    int second = INT_MAX;

    // Check travel cost to all nodes
    for (int j = 0; j < size; j++) {
        if (i == j) {
            continue; // Skip checking for the node to itself
        }

        //Checks if the cost "matrix[i][j]" is smaller or equal to "first" (current smallest edge cost):
        if (matrix[i][j] <= first) {
            second = first; // Previous smallest to second
            first = matrix[i][j]; // Update first

        //Else if "matrix[i][j]" is smaller than "second", but not smallet for equal for first
        } else if (matrix[i][j] <= second && matrix[i][j] != first) {
            second = matrix[i][j]; // Update seconcd
        }
    }
    return second; // Return second lowest cost
}


//TSP_Recursion() function is the building stone of the recursive Branch and Bound algorithm used to
//solve the Traveling Salesman Problem (TSP). This function explores potential routes recursively,
//calculates cost, and excludes routes, that is greater in cost than the current best known
//solution ("final_result"). It updates the best route and cost as it finds better (faster) solutions:
void TSP_Recursion(int size, int matrix[size][size], int current_bound, int current_weight,
    int level, int current_route[], int *final_result, int visited[], int final_route[]) {

    //When "level == size", it means all nodes have been visited:
    if (level == size) {

        //Checks if there's a route back to the starting node
        if (matrix[current_route[level - 1]][current_route[0]] != 0) {

            //Initializing the variable "current_result"
            int current_result = current_weight + matrix[current_route[level - 1]][current_route[0]];

            //Check if "current_result" is less than "final_result"
            if (current_result < *final_result) {
                copy_To_Final(size, current_route, final_route);
                *final_result = current_result;
            }
        }
        //After updating "final_result" and "final_route"
        return;
    }

    // If all not are not visited
    for (int i = 0; i < size; i++) {
        // Consider node "i" as the next destination if there is a route, and not visited
        if (matrix[current_route[level - 1]][i] != 0 && visited[i] == 0) {
            // "temp" stores "current_bound" for later backtracking.
            int temp = current_bound;
            // Update current weight
            current_weight += matrix[current_route[level - 1]][i];

            //If node "level == 1", it uses the first minimum edge cost from the current and next
            //node:
            if (level == 1) {
                current_bound -= (first_minimum(size, matrix, current_route[level - 1])
                                 + first_minimum(size, matrix, i)) / 2;

            //For all other levels, it uses the second minimum edge cost from the current node and
            //the first minimum for the next node:
            } else {
                current_bound -= (second_minimum(size, matrix, current_route[level - 1])
                                 + first_minimum(size, matrix, i)) / 2;
            }

            //Checks if the sum of "current_bound" + "current_weight" is less than "final_results".
            if (current_bound + current_weight < *final_result) {
                // - "current_route[level] = i": records node "i" in the route:
                current_route[level] = i;
                // - "visited[i] = 1": marks node "i" as visited:
                visited[i] = 1;

                // - "TSP_Recursion()": Is called recursively to move to the next level:
                TSP_Recursion(size, matrix, current_bound, current_weight, level + 1,
                    current_route, final_result, visited, final_route);
            }

            // Backtracking one node
            current_weight -= matrix[current_route[level - 1]][i];
            current_bound = temp;
            visited[i] = 0;
        }
    }
}


//copy_To_Final() function is simple utility function, that copies a temporary route (stored in
//"current_route[]") to the global array final_route[], which stores the best route found so far.
//This function is called whenever the algorithm finds a complete route with a lower cost than the
//current minimum ("final_result"), so that the best solution is always saved:

//Input parameters:
//current_route[] = Holds the current route.

void copy_To_Final(int size, int current_route[], int final_route[]) {

    // Copy current route to final route
    for (int i = 0; i < size; i++) {
        final_route[i] = current_route[i];
    }

    // Returning to the starting node
    final_route[size] = current_route[0];
}


