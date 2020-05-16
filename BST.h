#ifndef BST_H_
#define BST_H_

#include "utils.h"
#include "files.h"
#include "BST.h"

OreBST* newNode(char *name);
OreBST *insertNode(OreBST *root, char *name);
void deleteBST(OreBST *root);
void inorderTraversal(OreBST *root, FILE *fout);
int number_ofNodes(OreBST *root);

#endif