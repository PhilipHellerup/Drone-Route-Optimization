
//Declaration of function prototypes and any other declarations
#pragma once
void TSP(int size, int matrix[size][size], int* final_result, int final_route[]);
int first_minimum(int size, int matrix[size][size], int i);
int second_minimum(int size, int matrix[size][size], int i);
void TSP_Recursion(int size, int matrix[size][size], int current_bound, int current_weight, int level, int current_route[], int* final_result, int visited[], int final_route[]);
void copy_To_Final(int size, int current_route[], int final_route[]);


//In our case we need to use "extern", because we have global variables or functions that need to be accessed
//across multiple files in the program without duplicating their definitions. In simple terms, "extern" is
//used to declare a variable or function, that is defined in another file. It essentially tells the compiler:
//"This variable or function exist, but its definition is elsewhere."
