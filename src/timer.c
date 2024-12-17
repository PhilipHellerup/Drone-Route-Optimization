#include "timer.h"
#include <stdio.h>

// It takes the starting time (start_time) as input.
void print_execution_time(clock_t start_time) {

    // Record the end time using clock() function.
    clock_t end_time = clock();

    // Calculate the execution time by subtracting start_time from end_time.
    // Divide by CLOCKS_PER_SEC to convert clock ticks to seconds.
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Print the execution time with precision up to 3 decimal places.
    printf("Execution time: %.3f seconds\n", execution_time);
}