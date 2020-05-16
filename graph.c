#include "graph.h"

GraphMatrix *createGraphMatrix(int noIslands)
{
    GraphMatrix *graph = NULL;
    
    graph = (GraphMatrix*)malloc(sizeof(GraphMatrix));
    if(!graph)
    {
        printf("Nu s-a putut aloca memorie la crearea GraphMatrix");
        exit(-10);
    }

    graph->vertex = noIslands;

    graph->insule = (Island*)malloc(sizeof(Island) * noIslands);
    if(graph->insule == NULL)
    {
        printf("Nu s-a putut aloca memorie pentru Insule");
        exit(-10);
    }

    graph->AdjMatrix = (int**)malloc(sizeof(int*) * graph->vertex);
    if(graph->AdjMatrix == NULL)
    {
        printf("Nu s-a putut aloca memorie pentru AdjMatrix");
        exit(-10);
    }

    for(int i = 0 ; i < graph->vertex ; i++)
        graph->AdjMatrix[i] = (int*)calloc(graph->vertex, sizeof(int)); // sizeof(int)*graph->vertex?
    graph->edge = 0;

    return graph;
}

// functia ce creaza un vector de structuri de tip Island
Island* islandVector(int noIslands)
{
    Island* insule = NULL;
    insule = (Island*)malloc(sizeof(Island) * noIslands);

    if(!insule)
    {
        printf("Nu s-a putut aloca memorie pentru insule");
        exit(-10);
    }
    return insule;
}

// functia principala ce imi ia datele din fisier si le baga in graf,
// celelalte functii importante sunt apelate tot in interiorul acestei functii
GraphMatrix * File_toGraph(int *noIslands, char* argv[])
{
    char firstIsland[BUFSIZ],secondIsland[BUFSIZ];
    int cost, newIslands, toleranta;
    GraphMatrix *graph = NULL, *graphGestiune = NULL;
    FILE *finput;
    if((finput=fopen(argv[1],"r"))==NULL)
    {
        printf("Nu s-a putut deschide fiesierul pentru citire");
        exit(-20);
    }

    fscanf(finput,"%d",noIslands);
    graph = createGraphMatrix(*noIslands);// stiu cate noduri sunt pentru a crea graful
    graph->insule = islandVector(*noIslands);
   
    for(int i = 0 ; i < (*noIslands) ; i++)
    { // stim numarul de insule, deci stim cate structuri de tip island trebuie
      // citite si bagate in vector
        graph->insule[i] = addIsland(&finput);
    }
    // acum putem citi numarul de muchii din graf
    fscanf(finput,"%d",&graph->edge);


    for(int i = 0 ; i < graph->edge ; i++)
    {   // \[-] pentru a ignora - cand citim IslandX - IslandY cost
        // pentru a nu folosi metoda cu strtok
        fscanf(finput," %s \- %s %d ",firstIsland,secondIsland,&cost);

        for(int j = 0 ; j < graph->vertex ; j++)
            if(!strcmp(graph->insule[j].nume,firstIsland))
                for(int k = 0 ; k < graph->vertex ; k++)
                    if(!strcmp(graph->insule[k].nume,secondIsland))
                    {
                        graph->AdjMatrix[j][k] = cost;
                        graph->AdjMatrix[k][j] = cost;
                    }

    }
    readFunctions(&finput,graph,argv,&newIslands);
    // graful vechi nu mai este necesar, asa ca eliberam memoria
    deleteGraph(graph);
    // cream un nou graf pentru partea de gestiune
    graphGestiune = createGraphMatrix(newIslands);

    fscanf(finput,"%d",&toleranta);
    for (int i = 0 ; i < graphGestiune->vertex ; i ++)
        graphGestiune->insule[i].tolAvioane = toleranta;

    // citim numarul de avioane si alocam memoria necesara pentru fiecare 
    // vector de avioane
    for (int i = 0 ; i < graphGestiune->vertex ; i++)
    {
         fscanf(finput,"%d ",&graphGestiune->insule[i].nrAvioane);
         graphGestiune->insule[i].avioane = (int*)malloc(sizeof(int)*graphGestiune->insule[i].nrAvioane);
    }

    // citim ID-urile avioanelor din fisier
    for (int i = 0 ; i < graphGestiune->vertex ; i++)
        for(int j = 0 ; j < graphGestiune->insule[i].nrAvioane ; j++)
             fscanf(finput,"%d ",&graphGestiune->insule[i].avioane[j]);

    // citim matricea de adiacenta din fisier
    for (int i = 0 ; i < graphGestiune->vertex ; i++)
        for (int j = 0 ; j < graphGestiune->vertex ; j++)
            fscanf(finput,"%d ",&graphGestiune->AdjMatrix[i][j]);
        
    gestiune(graphGestiune,argv);
    fclose(finput);
    deleteGraph(graphGestiune);
}

// functia ce imi citeste din fisier o insula pentru a o adauga in graf
Island  addIsland(FILE **f)
{
    Island *insula;
    insula = (Island*)malloc(sizeof(Island));
   // insule = islandVector(noIslands);
    char str[BUFSIZ];
    int cant;
    fscanf(*f,"%s",str);
    insula->nume = malloc(strlen(str)+1);
    strcpy(insula->nume,str);

    fscanf(*f,"%d",&insula->nrResurse);

    insula->inventarResurse = (Resursa*)malloc(sizeof(Resursa) * insula->nrResurse);

    for(int i = 0 ; i < insula->nrResurse ; i++)
    {
        fscanf(*f," %s %d ",str,&cant);
        insula->inventarResurse[i].cantitate = cant;
        insula->inventarResurse[i].nume = malloc(strlen(str)+1);
        strcpy(insula->inventarResurse[i].nume,str);
    }
    return *insula;
}

// functia de stergere a grafului
void deleteGraph(GraphMatrix *graph)
{ int i, j , k; 
    
    //graph->insule->inventarResurse
    for ( i = 0 ; i < graph->vertex ; i++)
    {
        if(graph->insule != NULL && graph->insule[i].inventarResurse != NULL)
        {
          for( j = 0 ; j < graph->insule[i].nrResurse ; j++)
            free(graph->insule[i].inventarResurse[j].nume);
        graph->insule[i].inventarResurse = NULL;
        }   
        else break;
    }

    for( i = 0 ; i < graph->vertex; i++)
       free(graph->insule[i].avioane);    

    if(graph->insule != NULL)
        free(graph->insule);

    for (i = 0 ; i < graph->vertex ; i++)
        free(graph->AdjMatrix[i]);
    free(graph->AdjMatrix);
}

