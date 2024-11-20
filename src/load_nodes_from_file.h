#pragma once // Ensures this header file is only included once in each compilation

//Node struct to hold the coordinates of all the different nodes:
typedef struct {
    int x;
    int y;
} Node;

//Declaration of function prototypes
void load_nodes_from_file(const char *filepath, Node nodes_array[], int node_count);
int get_delivery_point_count(const char* filename);