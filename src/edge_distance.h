
//Symbolic variables
#pragma once

//Number of nodes:
#define N 20


//Structs:

//Node struct to hold the coordinates of all the different nodes:
typedef struct {
    int x;
    int y;
} Node;


//In our case we need to use "extern", because we have global variables or functions that need to be accessed
//across multiple files in the program without duplicating their definitions. In simple terms, "extern" is
//used to declare a variable or function, that is defined in another file. It essentially tells the compiler:
//"This variable or function exist, but its definition is elsewhere."

//Declaration of the array of nodes:
extern Node nodes[N];       //Can be found in "edge_distance.c" file.


//Declaration of function prototypes and any other declarations
void calculate_edges(int matrix[N][N], Node nodes[]);
void printMatrix(int matrix[N][N]);
int euclidean_distance(Node start, Node goal);


