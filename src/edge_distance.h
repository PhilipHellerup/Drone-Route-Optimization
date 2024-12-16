//Symbolic variables
#pragma once
#include "load_nodes_from_file.h"

//Declaration of function prototypes and any other declarations
void calculate_edges(int node_count, double matrix[node_count][node_count], Node nodes[]);
int euclidean_distance(Node start, Node goal);


