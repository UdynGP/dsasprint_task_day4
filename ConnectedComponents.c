/*
Given a directed graph, write an algorithm to find the strongly connected components of the graph.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1000

int indices[MAX_NODES];
int lowlink[MAX_NODES];
int onStack[MAX_NODES];
int stack[MAX_NODES];
int stackSize = 0;
int index = 0;

// Structure for Adjacency List Node
typedef struct AdjListNode
{
    int dest;
    struct AdjListNode *next;
} AdjListNode;

// Structure for Adjacency List
typedef struct AdjList
{
    struct AdjListNode *head;
} AdjList;

// Structure for Graph
typedef struct Graph
{
    int V;
    struct AdjList *array;
} Graph;

// Function to create a new adjacency list node
AdjListNode *newAdjListNode(int dest)
{
    AdjListNode *newNode = (AdjListNode *)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph of V vertices
Graph *createGraph(int V)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (AdjList *)malloc(V * sizeof(AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

// Adds an edge to an undirected graph
void addEdge(Graph *graph, int src, int dest)
{
    AdjListNode *newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Function to print the connected components
void printSCC(int node)
{
    while (stackSize > 0)
    {
        int v = stack[--stackSize];
        onStack[v] = 0;
        printf("%d ", v);
        if (node == v)
            break;
    }
    printf("\n");
}

// A recursive function to find strongly connected components
void SCCUtil(Graph *graph, int u)
{
    indices[u] = lowlink[u] = index++;
    stack[stackSize++] = u;
    onStack[u] = 1;

    // Go through all vertices adjacent to this
    AdjListNode *node;
    for (node = graph->array[u].head; node != NULL; node = node->next)
    {
        int v = node->dest;
        if (indices[v] == -1)
        {
            SCCUtil(graph, v);
            lowlink[u] = (lowlink[u] < lowlink[v]) ? lowlink[u] : lowlink[v];
        }
        else if (onStack[v])
        {
            lowlink[u] = (lowlink[u] < indices[v]) ? lowlink[u] : indices[v];
        }
    }

    // Check if the current vertex is a root node
    if (lowlink[u] == indices[u])
    {
        printSCC(u);
    }
}

// Function to find SCCs
void SCC(Graph *graph)
{
    for (int i = 0; i < graph->V; i++)
    {
        indices[i] = -1;
        lowlink[i] = -1;
        onStack[i] = 0;
    }

    for (int i = 0; i < graph->V; i++)
    {
        if (indices[i] == -1)
        {
            SCCUtil(graph, i);
        }
    }
}

// Driver program to test above functions
int main()
{
    printf("Enter number of vertices in graph\n");
    int V;
    scanf("%d", &V);

    Graph *graph = createGraph(V);

    printf("Enter number of edges\n");
    int E;
    scanf("%d", &E);

    for (int i = 0; i < E; i++)
    {
        int src, dest;
        printf("Enter source and destination of edge %d\n", i + 1);
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Strongly connected components in the given graph:\n");
    SCC(graph);

    return 0;
}
