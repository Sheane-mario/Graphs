#include "graph_matrix.h"

int main()
{
    int V = 6;
    struct GraphM *graph = createGraphM(V);

    addDirEdgeM(graph, 0, 5);
    addDirEdgeM(graph, 0, 4);
    addDirEdgeM(graph, 0, 1);
    addDirEdgeM(graph, 1, 5);
    addDirEdgeM(graph, 1, 3);
    addDirEdgeM(graph, 1, 2);
    addDirEdgeM(graph, 4, 2);
    addDirEdgeM(graph, 2, 3);
    addDirEdgeM(graph, 5, 3);

    printAdjMatrix(graph);

    struct GraphM *graphT = transpose_M(graph);

    printAdjMatrix(graphT);

    return 0;
}