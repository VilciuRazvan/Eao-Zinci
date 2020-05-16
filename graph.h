#ifndef GRAPH_H_
#define GRAPH_H_



#include "functions.h"
#include "utils.h"

//function to create graph with adjacency matrix
GraphMatrix *createGraphMatrix(int noIslands);
Island* islandVector(int noIslands);
GraphMatrix * File_toGraph(int *noIslands, char* argv[]);
Island addIsland(FILE **f);


#endif