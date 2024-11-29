#pragma once
//
// Created by OEM on 22-11-2024.
//

#ifndef ADDRESS_GENERATOR_H
#define ADDRESS_GENERATOR_H

typedef struct {
    int x;
    int y;
} household;

void generate_addresses(const char *filepath, int nodes, int max_size);
int check_distance(household households[], int household_count, int x, int y);
#endif //ADDRESS_GENERATOR_H
