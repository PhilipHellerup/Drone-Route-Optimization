#pragma once // Ensures this header file is only included once in each compilation

//Declaration of function prototypes
void TSP(int size, int matrix[size][size], int* final_result, int final_route[]);
int first_minimum(int size, int matrix[size][size], int i);
int second_minimum(int size, int matrix[size][size], int i);
void TSP_Recursion(int size, int matrix[size][size], int current_bound, int current_weight, int level, int current_route[], int* final_result, int visited[], int final_route[]);
void copy_To_Final(int size, int current_route[], int final_route[]);
