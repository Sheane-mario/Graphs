#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph_matrix.h"

struct GraphM *createGraphM(int V)
{
    struct GraphM *newGraph = (struct GraphM *)malloc(sizeof(struct GraphM));
    newGraph->V = V;

    newGraph->adjMatrix = (int **)malloc(V * sizeof(int *));
    /* Dynamically allocate memory for an array of pointers to integers */
    for (int i = 0; i < V; i++)
    {
        newGraph->adjMatrix[i] = (int *)malloc(V * sizeof(int));
    }
    /* Initialize the adjacency matrix with all zeroes */
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            newGraph->adjMatrix[i][j] = 0;
        }
    }
    return newGraph;
}
//--------------------------------------------------------------
void addDirEdgeM(struct GraphM *graph, int src, int dest)
{
    /* Add an edge from src -> dest */
    graph->adjMatrix[src][dest] = 1;
}
//--------------------------------------------------------------
void addUndirEdgeM(struct GraphM *graph, int src, int dest)
{
    /* Add an edge from src -> dest and dest -> src */
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}
//--------------------------------------------------------------------------
struct GraphM *transpose_M(struct GraphM *graph)
{
    struct GraphM *graphT = createGraphM(graph->V);
    for (int i = 0; i < graph->V; i++)
    {
        for (int j = 0; j < graph->V; j++)
        {
            graphT->adjMatrix[j][i] = graph->adjMatrix[i][j];
        }
    }
    return graphT;
}
//------------------------------------------------------------------------
bool isUniversalSink_M(struct GraphM *graph, int i)
{
    for (int j = 0; j < graph->V; j++)
    {
        if (graph->adjMatrix[i][j] == 1)
            return false;

        if (i != j && graph->adjMatrix[j][i] == 0)
            return false;
    }
    return true;
}
//----------------------------------------------------------------------
//-----------------------------------------------------------------------
void freeGraph_M(struct GraphM *graph)
{
    for (int i = 0; i < graph->V; i++)
    {
    }
}
//------------------------------------------------------------------------
void printAdjMatrix(struct GraphM *graph)
{
    printf("Adjacency matrix representation of the graph: \n");
    printf("\t");
    for (int i = 0; i < graph->V; i++)
    {
        printf("%d\t", i);
    }
    printf("\n");
    for (int i = 0; i < graph->V; i++)
    {
        printf("%d\t", i);
        for (int j = 0; j < graph->V; j++)
        {
            printf("%d\t", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}
