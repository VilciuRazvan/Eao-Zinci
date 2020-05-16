#include "files.h"

//functie de deschidere a unui fisier cu rol de write
FILE *openWrite(char *argv[])
{
    FILE *fout;
    if((fout= fopen(argv[2],"w")) == NULL)
    {
        fprintf(fout,"Eroare la deschiderea rezultate.out pentru write");
        exit(-10);
    }
    return fout;
}

//functie de deschidere a unui fisier cu rol de append
FILE *openAppend(char *argv[])
{
     FILE *fout;
    if((fout= fopen(argv[2],"a")) == NULL)
    {
        fprintf(fout,"Eroare la deschiderea rezultate.out pentru append");
        exit(-10);
    }
    return fout;
}



