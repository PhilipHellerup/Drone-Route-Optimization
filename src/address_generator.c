//
// Created by OEM on 22-11-2024.
//
#include <stdio.h>
#include "address_generator.h"
#include <time.h>
#include <stdlib.h>

void generate_addresses(const char *filepath, int n) {

    FILE* filepointer = fopen(filepath, "w");

    if (!filepointer) {
        printf("Can't open file\n");
        printf("filename %s", filepath);
        exit(EXIT_FAILURE);
    }
    fprintf(filepointer, "x-value, y-value \n");
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        int x = rand() % n+1;
        int y = rand() % n+1;
        fprintf(filepointer, "%i,%i \n", x,y);
    }

    fclose(filepointer);
}
