#include "BST.h"

// tipul de structura BST l-am gandit mai mult pentru functia max_resurse
//intrucat trebui sa analizam numarul de resurse si sa le ordonam
//lexicografic, un BST mi s-a parut solutia optima

// functie de creare nod BST
OreBST *newNode (char *name)
{
    OreBST *node = (OreBST*)malloc(sizeof(OreBST));
    node->name = (char*) malloc(sizeof(char)*strlen(name)+1);
    strcpy(node->name,name);
    node->left = node->right = NULL;
    return node;
}

//functie de bagat nume in bst
OreBST *insertNode(OreBST *root, char *name)
{
    if(root == NULL)
        return newNode(name);
    
    // daca numele exista deja in BST, nu il mai adaug
    if(!strcmp(root->name,name))
        return root;
    
    // daca numele de adaugat in bst este mai mic dpdv lexicografic,
    // adaug la stanga, altfel la dreapta
    else if (strcmp(root->name,name) < 0)
        root->right = insertNode(root->right, name);
    
    else
        root->left = insertNode(root->left, name);

    return root;
}

// functie de eliberare a memoriei
void deleteBST(OreBST *root)
{
    if(!root)
        return;
    
    deleteBST(root->left);
    deleteBST(root->right);
    free(root);
}

// daca parcurgem arborele in inordine, atunci afisarea ar fi
// in ordine lexicografica
void inorderTraversal(OreBST *root, FILE *fout)
{
    if(!root)
        return;

    inorderTraversal(root->left,fout);

    fprintf(fout,"%s ",root->name);

    inorderTraversal(root->right,fout);
        
}

// functie ce imi calculeaza cate noduri sunt in BST
// cu alte cuvinte, numarul de resurse diferite
int number_ofNodes(OreBST *root)
{
    if (!root)
        return 0;
    
    else
        return 1 + number_ofNodes(root->left) + number_ofNodes(root->right);
}