//
// Created by Jacob Larsen on 13/11/2024.
//

#ifndef LOAD_NODES_FROM_FILE_H
#define LOAD_NODES_FROM_FILE_H
#pragma once

//Node struct to hold the coordinates of all the different nodes:
typedef struct {
    int x;
    int y;
} Node;

#endif //LOAD_NODES_FROM_FILE_H

void load_nodes_from_file(const char *filename, Node nodes_array[], int node_count);
int get_delivery_point_count(const char* filename);