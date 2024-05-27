#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "graph_list.h"

struct GraphNode *createNode(int val)
{
    struct GraphNode *newNode = (struct GraphNode *)malloc(sizeof(struct GraphNode));
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}
//---------------------------------------------------------------
struct GraphL *createGraphL(int V)
{
    struct GraphL *newGraph = (struct GraphL *)malloc(sizeof(struct GraphL));
    newGraph->V = V;

    newGraph->adjList = (struct GraphNode **)malloc(V * sizeof(struct GraphNode *));

    for (int i = 0; i < V; i++)
    {
        newGraph->adjList[i] = NULL;
    }

    return newGraph;
}
//-------------------------------------------------------------
void addDirEdgeL(struct GraphL *graph, int src, int dest)
{
    /* Add an edge from source to dest */
    struct GraphNode *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}
//--------------------------------------------------------------
void addUndirEdgeL(struct GraphL *graph, int src, int dest)
{
    /* Add an edge from source to dest */
    struct GraphNode *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    /* In an undirected graph, add an edge from dest to source as well */
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}
//--------------------------------------------------------------
void BFS_L(struct GraphL *graph, int startVertex)
{
    /* Dynamically allocate memory for queue to keep the frontier nodes */
    int *queue = (int *)malloc(graph->V * sizeof(int));
    int front = 0;
    int rear = 0;

    /* Enqueue startVertex to the queue */
    queue[rear++] = startVertex;

    /* Setting the configs for the startVertex, distance from the source = 0, parent is null, color is grey, since it's already processed */
    graph->adjList[startVertex]->distance = 0;  /* Distance from the startVertex to itself is 0 */
    graph->adjList[startVertex]->parent = NULL; /* Parent of startVertex is null */
    graph->adjList[startVertex]->color = 'G';   /* since the startvertex is processed at the beginning mark it as GREY */

    for (int i = 0; i < graph->V; i++)
    {
        if (i == startVertex)
            continue;
        graph->adjList[i]->distance = INT_MAX; /* At the beginning set the distance from the source to the every other node as infinity */
        graph->adjList[i]->parent = NULL;      /* At the beginning parent is not set for the nodes */
        graph->adjList[i]->color = 'W';        /* Mark every node as WHITE, since it is discovered now */
    }

    while (front < rear)
    {
        int u = queue[front++]; /* dequeue from the front of the queue */
        printf("%d\t", u);

        struct GraphNode *temp = graph->adjList[u];
        while (temp != NULL)
        {
            int v = temp->data;
            if (graph->adjList[v]->color == 'W')
            {
                graph->adjList[v]->color = 'G';                                /* Mark v as grey since it is processing now */
                graph->adjList[v]->distance = graph->adjList[u]->distance + 1; /* set the distance of v as v.d = u.d + 1 */
                graph->adjList[v]->parent = graph->adjList[u];
                queue[rear++] = v;
            }
            temp = temp->next;
        }
        graph->adjList[u]->color = 'B'; /* Mark u as black since u is now visited */
    }
    free(queue); /* Free dynamically allocated memory for the queue */
}
//-------------------------------------------------------------------------
struct GraphL *transpose_L(struct GraphL *graph)
{

    struct GraphL *graphT = createGraphL(graph->V);
    for (int i = 0; i < graph->V; i++)
    {
        struct GraphNode *u = graph->adjList[i];

        while (u != NULL)
        {
            addDirEdgeL(graphT, u->data, i);
            u = u->next;
        }
    }
    return graphT;
}
//------------------------------------------------------------------------
bool isUniversalSink_L(struct GraphL *graph, int vertex)
{
    struct GraphNode *current = graph->adjList[vertex];
    /* if the vertex has out-degree then it is not a universal sink */
    if (current != NULL)
        return false;

    /* Check if every other vertex has an edge towards this vertex */
    for (int i = 0; i < graph->V; i++)
    {
        if (i != vertex)
        {
            current = graph->adjList[i];
            while (current != NULL)
            {
                if (current->data == vertex)
                {
                    /* current vertex has an edge to the given vertex */
                    break;
                }
                current = current->next;
            }
            /* When the current vertex does not have an edge to the checking vertex it cannot be a universal sink */
            if (current == NULL)
                return false;
        }
    }
    /* When program comes here every other vertex has an edge to this given vertex, hence return true */
    return true;
}
//-----------------------------------------------------------------------
int degreeCount_L(struct GraphL *graph, int vertex)
{
    int count = 0;
    struct GraphNode *temp = graph->adjList[vertex];
    while (temp != NULL)
    {
        count += 1;
        temp = temp->next;
    }
    return count;
}
//-----------------------------------------------------------------------
bool isRegularGraph_L(struct GraphL *graph)
{
    int *degCount = (int *)malloc(graph->V * sizeof(int));

    for (int i = 0; i < graph->V; i++)
    {
        degCount[i] = degreeCount_L(graph, i);
    }
    bool isRegular = true;
    for (int i = 0; i < graph->V - 1; i++)
    {
        if (degCount[i] != degCount[i + 1])
        {
            isRegular = false;
            break;
        }
    }
    return isRegular;
}
//-----------------------------------------------------------------------
bool isCompleteGraph_L(struct GraphL *graph)
{
    for (int i = 0; i < graph->V; i++)
    {
        /* Array to keep track of the visited vertices */
        int *visited = (int *)malloc(graph->V * sizeof(int));
        for (int k = 0; k < graph->V; k++)
        {
            visited[k] = 0;
        }
        struct GraphNode *currVertex = graph->adjList[i];

        while (currVertex != NULL)
        {
            /* Mark the vertex as visited */
            visited[currVertex->data] = 1;
            currVertex = currVertex->next;
        }
        /* Check if all the vertices are visited */
        for (int j = 0; j < graph->V; j++)
        {
            if (i != j && visited[j] == 0)
            {
                /* There is no edge between i and j, so cannot be a complete graph */
                return false;
            }
        }
    }
    return true;
}
//-----------------------------------------------------------------------
int outDegree_L(struct GraphL *graph, int vertex)
{
    int outDeg = 0;
    struct GraphNode *temp = graph->adjList[vertex];
    while (temp != NULL)
    {
        outDeg += 1;
        temp = temp->next;
    }
    return outDeg;
}
//-----------------------------------------------------------------------
int inDegree_L(struct GraphL *graph, int vertex)
{
    int inDeg = 0;
    for (int i = 0; i < graph->V; i++)
    {
        struct GraphNode *curr = graph->adjList[i];
        while (curr != NULL)
        {
            if (curr->data == vertex)
            {
                inDeg += 1;
                break;
            }
            curr = curr->next;
        }
    }
}
//-------------------------------------------------------------------------
void freeGraph_L(struct GraphL *graph)
{
    for (int i = 0; i < graph->V; i++)
    {
        struct GraphNode *current = graph->adjList[i];
        while (current != NULL)
        {
            struct GraphNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjList);
    free(graph);
}
//-------------------------------------------------------------------------
void printAdjList(struct GraphL *graph)
{
    for (int i = 0; i < graph->V; i++)
    {
        printf("Adjacency list of vertex %d:", i);
        struct GraphNode *temp = graph->adjList[i];
        while (temp != NULL)
        {
            printf(" -> %d", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}
//---------------------------------------------------------------
