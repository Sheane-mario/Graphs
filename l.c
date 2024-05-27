#include "graph_list.h"
#include <stdio.h>

int main()
{
    int V = 5;
    struct GraphL *graph = createGraphL(V);

    addDirEdgeL(graph, 0, 1);
    addDirEdgeL(graph, 0, 4);
    addDirEdgeL(graph, 1, 2);
    addDirEdgeL(graph, 1, 3);
    addDirEdgeL(graph, 1, 4);
    addDirEdgeL(graph, 2, 3);
    addDirEdgeL(graph, 3, 4);

    printAdjList(graph);

    // BFS_L(graph, 0);
    printf("\n");

    struct GraphL *graphT = transpose_L(graph);
    printAdjList(graphT);

    return 0;
}