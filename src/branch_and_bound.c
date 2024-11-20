
//Libraries Needed:
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "branch_and_bound.h"

#include <stdio.h>


//TSP() function sets up the initial values and calls the recursion function, TSP_Recursion() to solve
//the Traveling Salesman Problem (TSP) using the Branch and Bound algorithm. The function initialized
//the needed structures, calculates the initial bound and starts the recursive exploration to find
//the optimal route (in this case the fastest route, which means the route that has the lowest cost):
void TSP(int size, int matrix[size][size],int* final_result, int final_route[]) {


    int visited[size];

    //Initializing the "current_route[]" array, which will store the current route of nodes being explored.
    //It has "N+1" elements, which makes it so it can store a full route, that includes returning to
    //the starting node:
    int current_route[size + 1];

    //Initializing "current_bound" variable, which represents an initial lower bound of the travel cost.
    //This value helps in excluding routes in the Branch & Bound algorithm, by estimating a minimal
    //possible cost for the current route:
    int current_bound = 0; //Initially set to 0.

    //Sets all the elements in current_route[] to -1, signifying that no nodes have been visited or
    //assigned yet in the current_route[] array:
    memset(current_route, -1, sizeof(current_route));

    //Sets all the elements in visited[] to 0, marking all nodes as unvisited:
    memset(visited, 0, sizeof(visited));

    //This for-loop iterates over all nodes and calculates "current_bound", based on the formula:
    //T = 1 / 2 * (sum of "first_minimum" + "second_minimum") for each node's outgoing edges.
    for (int i = 0; i < size; i++) {

        //For each "i", it adds the values returned by "first_minimum(matrix, i)", which is the smallest
        //outgoing edge cost, and "second_minimum(matrix, i)", which is the second-smallest
        //outgoing edge cost, to "current_bound". This is to compute a realistic initial estimate
        //of the minimal route cost, which will help the Branch and Bound algorithm in deciding
        //which routes to explore further.
        current_bound += (first_minimum(size, matrix, i) + second_minimum(size, matrix, i));

    }

    //After finding the sum of the edge cost, then "current_bound" is divided by 2 to complete
    //the bound calculation. If "current_bound" is odd, it gets rounded up by adding 1, which
    //ensures the bound remains an integer. This integer "current_bound", represents the estimated
    //minimal route cost, from the starting node, which helps the Branch and Bound algorithm in
    //deciding which specific routes, that need to be excluded/pruned.
    current_bound = (current_bound & 1) ? current_bound / 2 + 1 : current_bound / 2;
    //The "&" symbol in this case is not a logical "AND", but a bitwise "AND". This means that in
    //this case we say that, "current_bound & 1" performs a "Bitwise AND" between "current_bound" and
    //"1". The number "1" in binary is "0001", which means when "current_bound & 1" is evaluated:
    // - If the last bit of "current_bound" is "1", the result is "1", meaning "current_bound" is odd.
    // - If the last bit of "current_bound" is "0", the result is "0", meaning "current_bound" is even.


    //The TSP route is initialized to start from node 0:
    visited[0] = 1;         //visited[0] = 1; marks node 0 as visited.
    current_route[0] = 0;   //current_route[0] = 0; places node 0 at the beginning of "current_route[]".

    //Run the TSP_Recursion() function to begin recursion exploration:

    //Input parameters are:
    // - "matrix": The adjacency matrix representing costs between nodes.
    // - "current_bound": The initial calculated bound.
    // - "current_weight = 0": This represents the current route's weight (starting from 0,
    //                         given that no travel has occurred yet).
    // - "level = 1": This indicates that we are at the first level of the route (only starting node).
    // - "current_route": The route array with node 0 as the starting node.
    TSP_Recursion(size, matrix, current_bound, 0, 1, current_route, final_result, visited, final_route);

}


//first_minimum() function finds the minimum edge (smallest cost) from a given node to any other node.
//This function helps in calculating a lower bound in the Branch and Bound approach to
//the Traveling Salesman Problem (TSP), which is used to determine if certain routes should be
//explored further or excluded/pruned:

//Input parameters:
//matrix[N][N] = The adjacency matrix of the graph, where matrix[i][j] represent the cost of going
//from node i to node j.
//i = The index of the node for which we want to find the minimum outgoing edge cost.

int first_minimum(int size, int matrix[size][size], int i) {

    //Initializing the "first" variable to INT_MAX, which is the highest possible integer value. This
    //is to ensure that any smaller value encountered in the loop will replace "first".
    int first = INT_MAX;

    //This for-loop iterates over all nodes (j from 0 to N-1 (j < N)) to check travel cost from
    //node i to each node j:
    for (int j = 0; j < size; j++) {

        //Checks if "i != j" to exclude self-loops (given that the cost to go from node A to itself is
        //not relevant for this program). It also checks if "matrix[i][j] < first", which means
        //if the cost to go from node i to node j (matrix[i][j]) is less than the current "first",
        //then it updates "first" with the smallest cost.
        if (matrix[i][j] < first && i != j) {
            first = matrix[i][j];
        }

    }

    //Return the integer variable "first", which represents the minimum cost from
    //node i to any other node j (excluding itself of course):
    return first;

}


//second_minimum() function finds the second-smallest edge (cost) from a given node to any other node.
//This function is useful in calculating a tighter bound in the Branch and Bound approach for
//the Traveling Salesman (TSP) by providing additional information about the second-lowest cost edge,
//which helps to better estimate the minimum cost for a route.

//Input parameters:
//matrix[N][N] = The adjacency matrix of the graph, where matrix[i][j] represent the cost of going
//from node i to node j.
//i = The index of the node for which we want to find the second minimum outgoing edge cost.

int second_minimum(int size, int matrix[size][size], int i) {

    //Initializing the "first" and "second" variable to INT_MAX, which is the highest possible integer
    //value. "first" will store the smallest outgoing edge cost, and "second" will store the
    //second smallest. INT_MAX is to ensure that any smaller value encountered in the loop will
    //replace "first" or "second", depending on the scenario:
    int first = INT_MAX;
    int second = INT_MAX;

    //This for-loop iterates over all nodes (j from 0 to N-1 (j < N)) to check travel cost from
    //node i to each node j:
    for (int j = 0; j < size; j++) {

        //Checks if "i == j", which means that if its true it will skip the current iteration of
        //the for-loop and go to "j+1" iteration. We do this, because we don't want the cost of going
        //from a node to itself:
        if (i == j) {
            continue; //Skip the current iteration of the for-loop.

        }

        //Checks if the cost "matrix[i][j]" is smaller or equal to "first" (current smallest edge cost):
        if (matrix[i][j] <= first) {

            //"second" is set to the current value of "first" (shifting the previous smallest cost
            //to "second"):
            second = first;

            //"first" is updated to "matrix[i][j]", the newest smallest edge cost.
            first = matrix[i][j]; //Sets the "first" cost to the cost of the current matrix[i][j] iteration.

        //Else if "matrix[i][j]" is smaller than "second", but not equal to "first", then "second" is
        //updated to matrix[i][j].
        } else if (matrix[i][j] <= second && matrix[i][j] != first) {

            //"second" is updated to "matrix[i][j]":
            second = matrix[i][j];

        }

    }

    //Return the integer variable "second", which represents the second-smallest cost from
    //node i to any other node j (excluding itself of course):
    return second;

}


//TSP_Recursion() function is the building stone of the recursive Branch and Bound algorithm used to
//solve the Traveling Salesman Problem (TSP). This function explores potential routes recursively,
//calculates cost, and excludes routes, that is greater in cost than the current best known
//solution ("final_result"). It updates the best route and cost as it finds better (faster) solutions:
void TSP_Recursion(int size, int matrix[size][size], int current_bound, int current_weight, int level, int current_route[], int *final_result, int visited[], int final_route[]) {

    for (int i = 0; i < size; i++) {
        printf("Current route: ");
        printf("%d ", current_route[i]);
    }
    printf("\n");

    //When "level == N", it means all nodes have been visited:
    if (level == size) {

        //Checks if there's a route back to the starting node (ensuring the route is a complete cycle).
        //If "matrix[current_route[level - 1]][current_route[0]]" is not 0 (indicating a route back exist):
        if (matrix[current_route[level - 1]][current_route[0]] != 0) {

            //Initializing the variable "current_result" to the total cost of the current route, by
            //adding the cost of returning to the starting node.
            int current_result = current_weight + matrix[current_route[level - 1]][current_route[0]];

            //Check if "current_result" is less than "final_result" (the minimum cost found so far),
            //it updates "final_result" and saves the route by calling/running copy_To_Final() function:
            printf("%d, %d\n", current_result, *final_result);
            if (current_result < *final_result) {
                copy_To_Final(size, current_route, final_route);
                *final_result = current_result;
            }


        }

        //After updating "final_result" and "final_route", the "return" statement is executed.
        //This "return" exits the TSP_Recursion() function and prevents further recursive calls from
        //being made along this route. This is important, because once all nodes have been visited
        //and the route cost is calculated, there's no need to continue exploring any further in
        //this specific branch of recursion:
        return;

    }

    //For levels below "N", the function iterates over all nodes (i = 0 to N - 1) to find potential
    //nodes to visit next:
    for (int i = 0; i < size; i++) {

        //It considers node "i" as the next destination if "matrix[current_route[level - 1]][i] is
        //not 0, meaning there is a route from the current node to node "i" "&&" (AND) if "visited[i]"
        //is 0, meaning that the node "i" has not been visited
        if (matrix[current_route[level - 1]][i] != 0 && visited[i] == 0) {

            //If the statement is true, which means node "i" is chosen as the next destination, then
            //"temp" temporarily stores "current_bound" for later backtracking.
            int temp = current_bound;

            //"current_weight" is updated to include the cost of traveling from the current node to
            //node "i":
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
            //The previous if-statement adjusts "current_bound" downward, estimating the cost for the
            //remaining route.

            //Checks if the sum of "current_bound" + "current_weight" is less than "final_results".
            printf("Current bound: %d, Current weight: %d, Best distance result so far%d\n", current_bound, current_weight, *final_result);
            if (current_bound + current_weight < *final_result) {

                //If true, it will continue exploring this route so:

                // - "current_route[level] = i": records node "i" in the route:
                current_route[level] = i;

                // - "visited[i] = 1": marks node "i" as visited:
                visited[i] = 1;

                // - "TSP_Recursion()": Is called recursively to move to the next level:
                TSP_Recursion(size, matrix, current_bound, current_weight, level + 1, current_route, final_result, visited, final_route);

            }

            //After exploring a route, the function "backtracks" to restore the state before visiting
            //node "i":

            //"current_weight" is reduced by the cost of traveling to node "i", and "current_bound" is
            //reset to "temp".
            current_weight -= matrix[current_route[level - 1]][i];
            current_bound = temp;

            //The "visited[]" node just backtracked from is reset to mark only nodes up to the current level as visited,
            //ensuring each recursive call works with an accurate state.
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

    //This for-loop copies each node from "current_route[]" to "final_route[]". Iterates through
    //the first "N" elements in "current_route[]", which represents nodes visited in the current
    //route, and copies them into "final_route[]":
    for (int i = 0; i < size; i++) {
        final_route[i] = current_route[i];

    }

    //After the for-loop has been terminated it sets "final_route[N]" to "current_route[0]". This
    //completes the route, by returning to the starting node, so "final_route[]" will now represent
    //a full route cycle:
    final_route[size] = current_route[0];

}


