//Symbolic variables
#pragma once
#include "load_nodes_from_file.h"

//In our case we need to use "extern", because we have global variables or functions that need to be accessed
//across multiple files in the program without duplicating their definitions. In simple terms, "extern" is
//used to declare a variable or function, that is defined in another file. It essentially tells the compiler:
//"This variable or function exist, but its definition is elsewhere."


//Declaration of function prototypes and any other declarations
void calculate_edges(int matrix[N][N], Node nodes[]);
int euclidean_distance(Node start, Node goal);


