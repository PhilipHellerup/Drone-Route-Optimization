
//Libraries Needed
#include <math.h>
#include "edge_distance.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

//calculate_edges() is the function that fills the distance matrix, which is used by the Branch & Bound
//algorithm to find the shortest route that visits each node exactly once:

/**
 *
 * @param node_count number of nodes
 * @param matrix matrix stores edge weights
 * @param nodes array of all nodes
 */
void calculate_edges(const int node_count, int matrix[node_count][node_count], Node nodes[]) {
    //The two nested loops are used to iterate over every possible pair of nodes "(i, j)", where "i" is the
    //row index and "j" is the column index in the distance matrix:
    for (int i = 0; i < node_count; i++) {
        for (int j = i; j < node_count; j++) {

            // If i == j is set to zero as this is distance to self
            if (i == j) {
                matrix[i][j] = 0;
                // If j != j calculate edge of weight with Euclidean distance
            } else {
                matrix[i][j] = euclidean_distance(nodes[i], nodes[j]);
                matrix[j][i] = matrix[i][j];  // Symmetric assignment
            }
        }
    }
}


//euclidean_distance() function calculates the Euclidean distance between two nodes, "start" and "goal",
//which are represented by the "Node" structs containing "x" and "y" coordinates. The Euclidean distance is
//the "straight-line" distance between two nodes in a 2D plane:
/**
 *
 * @param start start node
 * @param goal end node
 * @return distance
 */
int euclidean_distance(const Node start, const Node goal) {
        // Using abs() to calculate the absolute difference between 'x' and 'y' coordinates.
    double dx = (double)goal.x - (double)start.x;
    double dy = (double)goal.y - (double)start.y;

        // Returning the distance between the two nodes.
            return (int)(sqrt(dx * dx + dy * dy) + 0.5); // Adding 0,5 before casting to an int, to round to nearest integer
}
//Finding the Euclidean distance between the "start" and "goal" node:

//"dx * dx + dy * dy" applies the Pythagorean theorem to find the square of the
//Euclidean distance. By squaring both "dx" and "dy", then adding the results, we get the square of
//the straight-line distance.

//The "sqrt()" function takes the square root of the sum, which results in the Euclidean distance between
//the "start" and "goal" node.