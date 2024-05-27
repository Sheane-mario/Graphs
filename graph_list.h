#include <stdbool.h>
#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

/* Rrepresentation of a graph node */
struct GraphNode
{
    int data;
    char color;
    int distance;
    struct GraphNode *parent;
    struct GraphNode *next;
};
/* Representation of a graph using an adjacency list */
struct GraphL
{
    int V;
    struct GraphNode **adjList; /* adjList is a pointer to array of pointers, where each array member pointing to the adjacency list of each vertex */
};

/////////////////////////////////////////////////////////////////
struct GraphNode *createNode(int dest);                      /* Function to create a graph node */
struct GraphL *createGraphL(int V);                          /* Function to create a graph using an adjacency list representaion  */
void addDirEdgeL(struct GraphL *graph, int src, int dest);   /* Function to add a directed edge to the graph represented using an adjacency list */
void addUndirEdgeL(struct GraphL *graph, int src, int dest); /* Function to add an undirected edge to the graph represented using an adjacency list */
void printAdjList(struct GraphL *graph);                     /* Function to print the adjacency list of the graph */
void BFS_L(struct GraphL *graph, int startVertex);           /* Breadth first traversal of the graph represented using an adjacency list */
void printPath_L(struct GraphL *graph, int s, int v);        /* print path procedure print out the vertices on the shortest path from s to v */
struct GraphL *transpose_L(struct GraphL *graph);            /* Get the transpose of a graph represented using an adjacency list */
bool isUniversalSink_L(struct GraphL *graph, int vertex);    /* Function to check whether the given vertex is a universal sink */
int degreeCount_L(struct GraphL *graph, int vertex);         /* count the degree of the given vertex */
bool isRegularGraph_L(struct GraphL *graph);                 /* Return true if the graph is regular and false otherwise */
bool isCompleteGraph_L(struct GraphL *graph);                /* Returns true is the graph is a complete graph and false otherwise */
int outDegree_L(struct GraphL *graph, int vertex);           /* Calculates the out-degree of a given vertex */
int inDegree_L(struct GraphL *graph, int vertex);            /* Calculates the in-degree of a given vertex */
void freeGraph_L(struct GraphL *graph);                      /* Deallocate memory allocated to the graph */

#endif