#ifndef UTILS_H_
#define UTILS_H_

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

typedef struct Resursa
{
    char *nume;
    int cantitate;
}Resursa;

typedef struct Island
{
    char *nume;
    int nrResurse;
    Resursa *inventarResurse;
    int nrAvioane;
    int *avioane;
    int tolAvioane;
}Island;

typedef struct graph
{
    int vertex;
    int edge;
    int **AdjMatrix;
    Island *insule;
}GraphMatrix;

typedef struct BST
{
    char *name;
    struct BST *right;
    struct BST *left;
}OreBST;


#endif