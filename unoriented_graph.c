#include <stdio.h>
#include <stdlib.h>

struct AdjNode
{
    int dest;
    struct AdjNode *next;
};

struct Graph
{
    int n;
    struct AdjNode **adjList;
};

struct AdjNode *createNode(int dest)
{
    struct AdjNode *newNode = (struct AdjNode *)malloc(sizeof(struct AdjNode));
    newNode->dest = dest;
    newNode->next = NULL;

    return newNode;
};

void initGraph(struct Graph *graph, int n)
{
    graph->n = n;

    int i;
    graph->adjList = (struct AdjNode **)malloc(sizeof(struct AdjNode *) * n);
    for (i = 0; i < n; i++)
        graph->adjList[i] = NULL;
}

void addEdge(struct Graph *graph, int ii, int jj)
{
    // check to see if the edge doesn't already exist
    int edgeExists = 0, i;
    struct AdjNode *temp = graph->adjList[ii];
    while (temp)
    {
        if (temp->dest == jj)
            edgeExists = 1;
        temp = temp->next;
    }

    // if not add it at the beggining of the list
    if (!edgeExists)
    {
        struct AdjNode *newNode = createNode(jj);
        newNode->next = graph->adjList[ii];
        graph->adjList[ii] = newNode;
    }
}

void printGraph(struct Graph *graph)
{
    int i, j;
    for (i = 0; i < graph->n; i++)
    {
        printf("%d: ", i);

        struct AdjNode *temp = graph->adjList[i];
        while (temp)
        {
            printf("%d ", temp->dest);
            temp = temp->next;
        }

        printf("\n");
    }
}

void readGraph(struct Graph *graph)
{
    int i, n, m, ii, jj;
    printf("Number of nodes: ");
    scanf("%d", &n);

    initGraph(graph, n);

    printf("Number of edges: ");
    scanf("%d", &m);

    for (i = 0; i < m; i++)
    {
        printf("Edge number %d: ", i);
        scanf("%d%d", &ii, &jj);
        addEdge(graph, ii, jj);
        addEdge(graph, jj, ii);
    }
}

void freeGraph(struct Graph *graph)
{
    int i;
    for (i = 0; i < graph->n; i++)
        free(graph->adjList[i]);
}

void dfs(struct Graph *graph, int current, int *checked)
{
    if (checked[current] == 0)
    {
        checked[current] = 1;
        printf("%d ", current);

        struct AdjNode *node = graph->adjList[current];
        while (node)
        {
            dfs(graph, node->dest, checked);
            node = node->next;
        }
    }
}

void printConnectedComponents(struct Graph *graph)
{
    int *checked = (int *)malloc(sizeof(int) * graph->n);
    int i, componentCount = 0;
    for (i = 0; i < graph->n; i++)
        checked[i] = 0;

    for (i = 0; i < graph->n; i++)
    {
        if (checked[i] == 0)
        {
            componentCount++;
            printf("Component number %d: ", componentCount);
            dfs(graph, i, checked);
            printf("\n");
        }
    }
}

int main()
{
    struct Graph graph;
    readGraph(&graph);
    printConnectedComponents(&graph);
    freeGraph(&graph);
}