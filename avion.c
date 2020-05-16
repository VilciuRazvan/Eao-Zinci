#include "utils.h"
#include "graph.h"
#include "BST.h"
#include "files.h"
#include "functions.h"

int main(int argc, char* argv[])
{
    int noIslands;
    GraphMatrix *graf = NULL;
    FILE *fout = openWrite(argv);
    fprintf(fout,"");
    fclose(fout);
    graf = File_toGraph(&noIslands,argv);

    return 0;
}