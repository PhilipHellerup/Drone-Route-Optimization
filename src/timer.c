//
// Created by Jacob Larsen on 29/11/2024.
//

#include "timer.h"
#include <stdio.h>

//Function that prints the execution time of the program ones finished
void print_execution_time(clock_t start_time) {
    clock_t end_time = clock(); // Stop the timer
    //  = end_time - start_time
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution time: %.3f seconds\n", execution_time); // Print timer to user
}