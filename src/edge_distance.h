//Symbolic variables
#pragma once
#include "load_nodes_from_file.h"

//Declaration of function prototypes
void calculate_edges(int node_count, double matrix[node_count][node_count], Node nodes[]);
double euclidean_distance(Node start, Node goal);


