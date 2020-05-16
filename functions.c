#include "functions.h"

void conexiune (char* firstIsland, char* secondIsland, GraphMatrix *graph, char* argv[])
{
    FILE *fout = openAppend(argv);
    for(int i = 0 ; i < graph->vertex ; i++) 
        if(!strcmp(firstIsland,graph->insule[i].nume))  
            for(int j = 0 ; j < graph->vertex ; j++)
                if(!strcmp(secondIsland,graph->insule[j].nume))
                {
                    if(graph->AdjMatrix[i][j] != 0)
                    {
                        fprintf(fout,"OK\n");
                        fclose(fout);
                        return;
                    }
                    else
                    {
                        fprintf(fout,"NO\n");
                        fclose(fout);
                        return;
                    }
                    
                }
            
        
    
}

void legatura (char* islandName,GraphMatrix *graph, char* argv[])
{
    FILE *fout = openAppend(argv);
    for(int i = 0 ; i < graph->vertex ; i++)
    {
        if(!strcmp(islandName,graph->insule[i].nume))
        {
            for(int j = 0 ; j < graph->vertex ; j++)
            {
                if(graph->AdjMatrix[i][j] != 0)
                {
                    fprintf(fout,"%s ", graph->insule[j].nume);
                }
            }
            fprintf(fout,"\n");
            fclose(fout);
            return;
        }
    }
}

void adauga_zbor (char* firstIsland, char* secondIsland, int cost, GraphMatrix *graph)
{
    for(int i = 0 ; i < graph->vertex ; i++)
    {
        if(!strcmp(firstIsland,graph->insule[i].nume))
        {
            for(int j = 0 ; j < graph->vertex ; j++)
            {
                if(!strcmp(secondIsland,graph->insule[j].nume))
                {
                    graph->AdjMatrix[i][j] = cost;
                    graph->AdjMatrix[j][i] = cost;
                }
            }
            return; // return aici pentru ca am facut schimbarea,
                    // nu mai are rost sa continui cautarea insulelor
        }
    }
}

void anulare_zbor (char* firstIsland, char* secondIsland, GraphMatrix *graph)
{
    for(int i = 0 ; i < graph->vertex ; i++)
    {
        if(!strcmp(firstIsland,graph->insule[i].nume))
        {
            for(int j = 0 ; j < graph->vertex ; j++)
            {
                if(!strcmp(secondIsland,graph->insule[j].nume))
                {
                    graph->AdjMatrix[i][j] = 0;
                    graph->AdjMatrix[j][i] = 0;
                }
            }
            return; // return aici pentru ca am facut schimbarea,
                    // nu mai are rost sa continui cautarea insulelor
        }
    }
}

// pentru afisarea maximului de resurse si insulele corespondente
// ma folosesc de structura BST, numar nodurile, dupa care
//afisez numarul de noduri urmat de parcurgerea inorder cu afisare
void max_resurse(GraphMatrix *graph, char* argv[])
{
    FILE *fout = openAppend(argv);
    int max;
    OreBST *root =  NULL;
    for(int i = 0 ; i < graph->vertex ; i++)
        for( int j = 0 ; j < graph->insule[i].nrResurse ; j++)
            if(graph->insule[i].nrResurse != 0)
                root = insertNode(root, graph->insule[i].inventarResurse[j].nume);

    max = number_ofNodes(root);

    fprintf(fout, "%d ",max);
    inorderTraversal(root,fout);
    fprintf(fout,"\n");
    fclose(fout);
    deleteBST(root);
}


void max_cantitate(GraphMatrix *graph,char *oreName, char *argv[])
{
    int max = 0;
    FILE *fout = openAppend(argv);
    // aflam care este cantitatea maxima
    for(int i = 0 ; i < graph->vertex ; i++)
        for(int j = 0 ; j < graph->insule[i].nrResurse ; j++)
                if(!strcmp(graph->insule[i].inventarResurse[j].nume,oreName))
                    if(graph->insule[i].inventarResurse[j].cantitate > max)
                        max = graph->insule[i].inventarResurse[j].cantitate; 
                
    
    // dupa ce am aflat maximul afisam toate tarile care au cantitatea
    // minereului egala cu max
    for(int i = 0 ; i < graph->vertex ; i++)
        for(int j = 0 ; j < graph->insule[i].nrResurse ; j++)
            if(!strcmp(graph->insule[i].inventarResurse[j].nume,oreName))
                if(graph->insule[i].inventarResurse[j].cantitate == max)
                    fprintf(fout,"%s ",graph->insule[i].nume);
    
    fprintf(fout,"\n");
    fclose(fout);
}

// functia ce imi citeste din fisier functiile si argumentele necesare
void readFunctions(FILE **f, GraphMatrix *graph, char *argv[], int *newIslands)
{
    int arg;
    char functionName[BUFSIZ], firstArg[BUFSIZ], secondArg[BUFSIZ];
    
    while((fscanf(*f," %s ",functionName) == 1) && (atoi(functionName) == 0))
    {         
        if (!strcmp(functionName,"max_resurse"))
        {
            max_resurse(graph,argv);
        }

        else if (!strcmp(functionName,"max_cantitate"))
        {
            fscanf(*f,"%s ",firstArg);
            max_cantitate(graph,firstArg,argv);
        }

        else if (!strcmp(functionName,"legatura"))
        {
            fscanf(*f,"%s ",firstArg);
            legatura(firstArg,graph,argv);
        }

        else if (!strcmp(functionName,"conexiune"))
        {
            fscanf(*f,"%s %s",firstArg,secondArg);
            conexiune(firstArg,secondArg,graph,argv);
        }

        else if (!strcmp(functionName,"adauga_zbor"))
        {
            fscanf(*f,"%s %s %d",firstArg,secondArg,&arg);
            adauga_zbor(firstArg,secondArg,arg,graph);
        }

        else if (!strcmp(functionName,"anulare_zbor"))
        {
            fscanf(*f,"%s %s",firstArg,secondArg);
            anulare_zbor(firstArg,secondArg,graph);
        }

        else if (!strcmp(functionName,"timp_zbor"))
        {
            fscanf(*f,"%s %s",firstArg,secondArg);
            timp_zbor(graph,firstArg,secondArg,argv);
        }

       else if (!strcmp(functionName,"drum_zbor"))
        {
            fscanf(*f,"%s %s",firstArg,secondArg);
            drum_zbor(graph,firstArg,secondArg,argv);
        }

        else if (!strcmp(functionName,"min_zbor"))
        {
            fscanf(*f,"%s %s",firstArg, secondArg);
            min_zbor(graph,firstArg,secondArg,argv);
        }
    }
    *newIslands = atoi(functionName);

}

int minDistance(int distances[], int sps[], int vertex)
{
    int min_index, min = INT_MAX;

    for(int i = 0 ; i < vertex ; i++)
        if (sps[i] == 0 && distances[i] <= min)
        {
            min = distances[i]; 
            min_index = i;
        }
    return min_index;
}

int dijkstra (GraphMatrix *graph, int startingPoint, int endPoint, int *pred)
{
    int *distances = NULL, *sps = NULL, aux;
    distances = (int*)malloc(sizeof(int)*graph->vertex);
    sps = (int*)malloc(sizeof(int)*graph->vertex);

    for (int i = 0 ; i < graph->vertex ; i++)
    {
        distances[i] = INT_MAX;
        pred[i] = -1;
        sps[i] = 0;
    }
    distances[startingPoint] = 0;

    for (int j = 0 ; j < graph->vertex-1 ; j++)
    {
        aux = minDistance (distances,sps, graph->vertex);
        sps[aux] = 1;

        for(int k = 0 ; k < graph->vertex ; k++)
        {
            if (sps[k] == 0 && graph->AdjMatrix[aux][k]!=0 && distances[aux] != INT_MAX &&
                distances[aux]+graph->AdjMatrix[aux][k] < distances[k])
                {
                    distances[k] = distances[aux] + graph->AdjMatrix[aux][k];
                    pred[k] = aux;
                }
        }
    }
    return distances[endPoint];

}

void timp_zbor (GraphMatrix *graph, char *firstIsland, char *secondIsland, char *argv[])
{   
    int *pred = NULL;
    pred = (int*)malloc(sizeof(int)*graph->vertex);
    FILE *fout = openAppend(argv);
    int cost;
    for (int i = 0 ; i < graph->vertex ; i++)
    {
        if(!strcmp(graph->insule[i].nume,firstIsland))
        {
            for (int j = 0 ; j < graph->vertex ; j++)
            {
                if(!strcmp(graph->insule[j].nume,secondIsland))
                {
                    cost = dijkstra(graph, i, j, &(*pred));
                    break;
                }
            }
        }
    }

    if(cost == INT_MAX)
    {
        fprintf(fout,"INF\n");
        fclose(fout);
        return;
    }
    fprintf(fout,"%d\n",cost);
    fclose(fout);
}

void drum_zbor (GraphMatrix *graph, char *firstIsland, char *secondIsland, char *argv[])
{
    int *pred = NULL, cost, j;
    pred = (int*)malloc(sizeof(int)*graph->vertex);
    FILE *fout = openAppend(argv);

        for (int i = 0 ; i < graph->vertex ; i++)
            if(!strcmp(graph->insule[i].nume,firstIsland))
                for ( j = 0 ; j < graph->vertex ; j++)
                    if(!strcmp(graph->insule[j].nume,secondIsland))
                    {
                        cost = dijkstra(graph, i, j, &(*pred));
                        break;
                    }
                        
    printPredecessor(graph,j,pred,fout);

    if (cost == INT_MAX)
        fprintf(fout,"NO");
    fprintf(fout,"\n");
    fclose(fout);

}

// stim predecesorii insulei destinatie, insa trebuie sa afisam insulele
// in ordinea in care le parcurgem, asa ca in mod recursiv putem sa facem chiar asta
void printPredecessor (GraphMatrix *graph,int j, int *pred, FILE *fout)
{
    if(pred[j] != -1)
    {
        printPredecessor(graph,pred[j],pred,fout);
        fprintf(fout,"%s ",graph->insule[j].nume);
    }
}

void min_zbor (GraphMatrix *graph, char *firstIsland, char *secondIsland, char *argv[])
{
    int cost;
    FILE *fout = openAppend(argv);

        for (int i = 0 ; i < graph->vertex ; i++)
            if(!strcmp(graph->insule[i].nume,firstIsland))
                for (int j = 0 ; j < graph->vertex ; j++)
                    if(!strcmp(graph->insule[j].nume,secondIsland))
                    {
                        cost = dijkstraSpecial(graph, i, j);
                        break;
                    }

    fprintf(fout,"%d\n",cost);
    fclose(fout);
}

// functie de calculat numarul de predecesori, pentru drum_zbor
int countPredecessors(GraphMatrix *graph, int j, int *pred)
{
    if(pred[j] != -1)
        return 1 + countPredecessors(graph, pred[j], pred);
}


int dijkstraSpecial (GraphMatrix *graph, int startingPoint, int endPoint)
{
    int *distances = NULL, *sps = NULL, aux;
    distances = (int*)malloc(sizeof(int)*graph->vertex);
    sps = (int*)malloc(sizeof(int)*graph->vertex);

    for (int i = 0 ; i < graph->vertex ; i++)
    {
        distances[i] = INT_MAX;
        sps[i] = 0;
    }
    distances[startingPoint] = 0;

    for (int j = 0 ; j < graph->vertex-1 ; j++)
    {
        aux = minDistance (distances,sps, graph->vertex);
        sps[aux] = 1;

        for(int k = 0 ; k < graph->vertex ; k++)
        {
            if (sps[k] == 0 && graph->AdjMatrix[aux][k]!=0 && distances[aux] != INT_MAX &&
                distances[aux]+graph->AdjMatrix[aux][k]  < distances[k])
                {
                    // pentru fiecare insula pe care stationam adaugam +15 la distanta
                    distances[k] = distances[aux] + graph->AdjMatrix[aux][k]+15;
                }
        }
    }// returnam -15 pentru ca nu stationam si pe insula destinatie
    return distances[endPoint]-15;

}


void gestiune (GraphMatrix *graph, char *argv[])
{
    FILE *fout = openAppend(argv);
    int allPlanes = 0, *remainingPlanes = NULL, extraPlanes, extraIndex, counter = 0;
    bool noChange = true;

    // pentru stackoverflow
    for (int i = 0 ; i < graph->vertex ; i++)
        allPlanes += graph->insule[i].nrAvioane;

    if (allPlanes > (graph->insule[0].tolAvioane * graph->vertex))
    {
        fprintf(fout,"Stack overflow!\n");
        return;
    }
        
    
    for (int i = 0 ; i < graph->vertex ; i++)
        if (graph->insule[i].nrAvioane > graph->insule[0].tolAvioane)
            noChange = false;

    // in cazul in care nu trebuie efectuata nicio schimbare
    // afisez insulele cu avioanele precum in input
    if (noChange)
    {
        for (int i = 0 ; i < graph->vertex ; i++)
        {
            fprintf(fout,"Island%d\n",i+1);
            for (int j = 0 ; j < graph->insule[i].nrAvioane ; j++)
                fprintf(fout,"%d ",graph->insule[i].avioane[j]);
            fprintf(fout,"\n");
        }
        return;    
    }

    // in cazul in care trebuie facute schimbari
    else
    {
            // vad care sunt avioanele in plus si imi creez un vector cu acestea
        for (int i = 0 ; i < graph->vertex ; i++)
            if(graph->insule[i].nrAvioane > graph->insule[i].tolAvioane)
            {
                extraPlanes = graph->insule[i].nrAvioane - graph->insule[i].tolAvioane;
                remainingPlanes = (int*)malloc(sizeof(int) * extraPlanes);
                extraIndex = i; // pentru a sti care este insula cu avioane in plus
                
                for (int j = 0 ; j < extraPlanes ; j++)
                    remainingPlanes[j] = graph->insule[i].avioane[graph->insule[i].nrAvioane - extraPlanes + j];

                break; // odata ce am gasit insula cu exces de avioane nu are rost  sa mai cautam
            }
        
        // intai de toate verificam daca exista tari care pot sustine numarul de avioane
        // dar care nu sunt conectate pentru a face modificarile intre vectorii de avioane
        // inainte de a fi afisati in for-ul urmator
        for(int i = 0 ; i < graph->vertex ; i++)
        {   
            if( (graph->insule[i].tolAvioane - graph->insule[i].nrAvioane) >= extraPlanes && graph->AdjMatrix[i][extraIndex] == 0)
            {   // cautam insulele care sunt conectate cu insula cu surplus de avioane
                for (int j = 0 ; j < graph->vertex ; j++)
                    if (graph->AdjMatrix[extraIndex][j] != 0)
                    {       // daca insula gasita este de asemenea conectata cu
                            // insula ce poate sustine surplusul de avioane
                            if (graph->AdjMatrix[j][i] != 0)
                            {   // maresc numarul de avioane 
                                graph->insule[i].avioane = realloc(graph->insule[i].avioane, sizeof(int) * (graph->insule[i].nrAvioane + extraPlanes));
                                for (int k = graph->insule[j].nrAvioane - extraPlanes ; k < graph->insule[j].nrAvioane ; k++)
                                {   // mut avioanele de pe insula intermediara pe insula ce poate sustine surplusul
                                    graph->insule[i].avioane[graph->insule[i].nrAvioane + counter] = graph->insule[j].avioane[k];
                                    counter++;
                                }
                                // odata ce am adaugat surplusul de avioane
                                // crestem si numarul de avioane de pe insula
                                graph->insule[i].nrAvioane += extraPlanes;
                                counter = 0;
                                for (int k = graph->insule[j].nrAvioane - extraPlanes ; k<graph->insule[j].nrAvioane ; k++ )
                                  {  // pe insula intermediara de punem surplusul initial de avioane
                                     graph->insule[j].avioane[k] = remainingPlanes[counter];
                                     counter++;
                                  }
                                break;     
                            }
                    }
                    // am adaugat avioane pe insula ce poate sustine avioanele,
                    // insa nu stim daca acestea sunt in ordine crescatoare
                    // asa ca le ordonam
                    int temp;
                    for(int j = 0 ; j < graph->insule[i].nrAvioane-1 ; j++)
                        for(int k = j+1 ; k < graph->insule[i].nrAvioane ; k++)
                        {
                            if(graph->insule[i].avioane[j] > graph->insule[i].avioane[k])
                            {
                                temp = graph->insule[i].avioane[j];
                                graph->insule[i].avioane[j] = graph->insule[i].avioane[k];
                                graph->insule[i].avioane[k] = temp;
                            }
                        }
            }   
        }

        // in acest for afisez insulele in urma gestiunii
        for (int i = 0 ; i < graph->vertex ; i++)
        {       // daca am o conexiune directa cu o insula ce poate
                // sustine surplusul de avioane
                 if ( (graph->insule[i].tolAvioane - graph->insule[i].nrAvioane) >= extraPlanes && graph->AdjMatrix[i][extraIndex] != 0)
                {
                    fprintf(fout,"Island%d\n",i+1);
                    combinations(graph,remainingPlanes,i,&fout);
                }

            // daca aceasta este insula cu surplusul de avioane, realoc vectorul
            // de avioane si afisez restul avioanelor ramase
            else if (graph->insule[i].nrAvioane > graph->insule[i].tolAvioane)
                {
                    graph->insule[i].avioane = realloc(graph->insule[i].avioane,sizeof(int)*graph->insule[i].nrAvioane - extraPlanes);
                    graph->insule[i].nrAvioane -= extraPlanes;
                    fprintf(fout,"Island%d\n",i+1);
                    for (int j = 0 ; j < graph->insule[i].nrAvioane; j++)
                        fprintf(fout,"%d ",graph->insule[i].avioane[j]);
                    fprintf(fout,"\n");
                }
            
            // altfel, daca e o insula "basic", ce nu necesita schimbari
            else 
                {
                    fprintf(fout,"Island%d\n",i+1);
                    for (int j = 0 ; j < graph->insule[i].nrAvioane ; j++)
                        fprintf(fout,"%d ",graph->insule[i].avioane[j]);
                    fprintf(fout,"\n");
                }
        }
    }
    
    fclose(fout);
}


void combinations(GraphMatrix *graph, int *extraPlanes, int index, FILE **fout)
{
    int extraNumber = sizeof(extraPlanes)/sizeof(int);

    // stim ca initial vom avea avioanele unei insule + avioanele extra
    printPlanes(graph->insule[index],fout);
    for (int i = 0 ; i < extraNumber; i++)
        fprintf (*fout,"%d ",extraPlanes[i]);
    fprintf(*fout,"\n");

    // dupa vom avea avioanele insulei + combinatii dintre avioanele extra
    for(int i = extraNumber-1 ; i >= 0 ; i--)
    {
        printPlanes(graph->insule[index],fout);
        fprintf(*fout,"%d ",extraPlanes[i]);
        fprintf(*fout,"\n");
    }

    // iar la final vom avea doar avioanele insulei, fara avioane extra
    printPlanes(graph->insule[index],fout);
    fprintf(*fout,"\n");
    
}
    // functie ce genereaza avioanele unei insule
void printPlanes (Island insula, FILE **fout)
{
    for (int i = 0 ; i < insula.nrAvioane ; i++)
        fprintf(*fout,"%d ",insula.avioane[i]);
}