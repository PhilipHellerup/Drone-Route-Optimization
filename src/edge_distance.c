
//Libraries Needed
#include <math.h>
#include "edge_distance.h"
#include <stdlib.h>

//calculate_edges() is the function that fills the distance matrix, which is used by the Branch & Bound
//algorithm to find the shortest route that visits each node exactly once:
void calculate_edges(const int size, int matrix[size][size], Node nodes[]) {
    //The two nested loops are used to iterate over every possible pair of nodes "(i, j)", where "i" is the
    //row index and "j" is the column index in the distance matrix:
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {

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
    int euclidean_distance(Node start, Node goal) {

        //Initializing the variable "dx" and "dy". "dx" is the horizontal distance between the two nodes and
        //"dy" is the vertical distance between the two nodes:
        int dx = abs(goal.x - start.x); //Calculates the difference between the x-coordinates of the two nodes.
        int dy = abs(goal.y - start.y); //Calculates the difference between the y-coordinates of the two nodes.

        //Finding the Euclidean distance between the "start" and "goal" node:

        //"dx * dx + dy * dy" applies the Pythagorean theorem to find the square of the
        //Euclidean distance. By squaring both "dx" and "dy", then adding the results, we get the square of
        //the straight-line distance.

        //The "sqrt()" function takes the square root of the sum, which results in the Euclidean distance between
        //the "start" and "goal" node.

        //Rounding up with "+0.5" before casting the equation to an "int", which result in the expression being
        //rounded to the nearest integer.
        return (int)(sqrt(dx * dx + dy * dy) + 0.5);

    }
