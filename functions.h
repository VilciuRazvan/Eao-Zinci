#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "utils.h"
#include "graph.h"
#include "files.h"
#include "BST.h"

void conexiune (char* firstIsland, char* secondIsland, GraphMatrix *graph, char* argv[]);
void legatura (char* islandName,GraphMatrix *graph, char* argv[]);
void adauga_zbor (char* firstIsland, char* secondIsland, int cost, GraphMatrix *graph);
void anulare_zbor (char* firstIsland, char* secondIsland, GraphMatrix *graph);
void max_resurse (GraphMatrix *graph, char* argv[]);
void max_cantitate(GraphMatrix *graph,char *oreName, char *argv[]);
void readFunctions(FILE **f, GraphMatrix *graph, char *argv[], int *newIslands);
int minDistance(int distances[], int sps[], int vertex);
int dijkstra (GraphMatrix *graph, int startingPoint, int endPoint, int *pred);
void timp_zbor (GraphMatrix *graph, char *firstIsland, char *secondIsland, char *argv[]);
void drum_zbor (GraphMatrix *graph, char *firstIsland, char *secondIsland, char *argv[]);
void printPredecessor (GraphMatrix *graph,int j, int *pred, FILE *fout);
void min_zbor (GraphMatrix *graph, char *firstIsland, char *secondIsland, char *argv[]);
int countPredecessors(GraphMatrix *graph, int j, int *pred);
int dijkstraSpecial (GraphMatrix *graph, int startingPoint, int endPoint);
void gestiune (GraphMatrix *graph, char *argv[]);
void combinations(GraphMatrix *graph, int *remainingPlanes, int index, FILE **fout);
void printPlanes (Island insula, FILE **fout);


#endif