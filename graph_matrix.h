#include <stdbool.h>
#ifndef GRAPH_MATRIX_H
#define GRAPH_MATRIX_H

/* Representation of a graph using an adjacency matrix */
struct GraphM
{
    int V;
    int **adjMatrix; /* adjMatrix is a pointer to array of integer pointers */
};
/////////////////////////////////////////////////////////////////
struct GraphM *createGraphM(int V);                          /* Function to create a graph using an adjacency matrix representation */
void addDirEdgeM(struct GraphM *graph, int src, int dest);   /* Function to add a direced edge to the graph represented using an adjcency matrix */
void addUndirEdgeM(struct GraphM *graph, int src, int dest); /* Function to add an undireced edge to the graph represented using an adjcency matrix */
void printAdjMatrix(struct GraphM *graph);                   /* Function to print the adjacency matrix representation of the graph */
void BFS_M(struct GraphM *graph, int startVertex);           /* Breadth first traversal of the graph represented using an adjacency matrix */
struct GraphM *transpose_M(struct GraphM *graph);            /* Get the transpose of the graph represented using an adjacency matrix */
bool isUniversalSink_M(struct GraphM *graph, int i);         /* Determine whether the given vertex contains a universal sink */
void freeGraph_M(struct GraphM *graph);                      /* Deallocate memory allocated to the graph */

#endif