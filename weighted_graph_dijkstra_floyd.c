#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000

struct HeapNode
{
    int dest;
    int weight;
};

struct minHeap
{
    int n;
    struct HeapNode *arr;
};

struct minHeap *initMinHeap(int n)
{
    struct minHeap *minHeap = (struct minHeap *)malloc(sizeof(struct minHeap));
    minHeap->arr = (struct HeapNode *)malloc(sizeof(struct HeapNode) * n);
    minHeap->n = 0;

    return minHeap;
}

void swap(struct HeapNode *a, struct HeapNode *b)
{
    struct HeapNode aux = *a;
    *a = *b;
    *b = aux;
}

void heapifyUp(struct minHeap *minHeap, int current)
{
    int parent = (current - 1) / 2;

    if (parent >= 0)
    {
        if (minHeap->arr[parent].weight > minHeap->arr[current].weight)
        {
            swap(&minHeap->arr[parent], &minHeap->arr[current]);
            heapifyUp(minHeap, parent);
        }
    }
}

void heapifyDown(struct minHeap *minHeap, int current)
{
    int left = current * 2 + 1;
    int right = current * 2 + 2;

    int smallest = current;

    if (left < minHeap->n && minHeap->arr[smallest].weight > minHeap->arr[left].weight)
        smallest = left;

    if (right < minHeap->n && minHeap->arr[smallest].weight > minHeap->arr[right].weight)
        smallest = right;

    if (smallest != current)
    {
        swap(&minHeap->arr[current], &minHeap->arr[smallest]);
        heapifyDown(minHeap, smallest);
    }
}

void insertElement(struct minHeap *minHeap, int dest, int weight)
{
    minHeap->arr[minHeap->n].dest = dest;
    minHeap->arr[minHeap->n].weight = weight;
    minHeap->n++;

    heapifyUp(minHeap, minHeap->n - 1);
}

struct HeapNode extractMin(struct minHeap *minHeap)
{
    struct HeapNode min = minHeap->arr[0];
    swap(&minHeap->arr[0], &minHeap->arr[minHeap->n - 1]);
    minHeap->n--;
    heapifyDown(minHeap, 0);

    return min;
}

void freeminHeap(struct minHeap *minHeap)
{
    free(minHeap->arr);
}

int isEmpty(struct minHeap *minHeap)
{
    return (minHeap->n == 0);
}

struct AdjNode
{
    int dest;
    int weight;
    struct AdjNode *next;
};

struct Graph
{
    int n;
    struct AdjNode **adjList;
};

struct AdjNode *createNode(int dest, int weight)
{
    struct AdjNode *newNode = (struct AdjNode *)malloc(sizeof(struct AdjNode));
    newNode->dest = dest;
    newNode->weight = weight;
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

void addEdge(struct Graph *graph, int ii, int jj, int weight)
{
    // check to see if the edge doesn't already exist
    int edgeExists = 0, i;
    struct AdjNode *temp = graph->adjList[ii];
    while (temp)
    {
        if (temp->dest == jj && temp->weight == weight)
            edgeExists = 1;
        temp = temp->next;
    }

    // if not add it at the beginning of the list
    if (!edgeExists)
    {
        struct AdjNode *newNode = createNode(jj, weight);
        newNode->next = graph->adjList[ii];
        graph->adjList[ii] = newNode;
    }
}

void readGraph(struct Graph *graph)
{
    int i, n, m, ii, jj, weight;
    printf("Number of nodes: ");
    scanf("%d", &n);

    initGraph(graph, n);

    printf("Number of edges: ");
    scanf("%d", &m);

    for (i = 0; i < m; i++)
    {
        printf("Edge number %d: ", i);
        scanf("%d%d%d", &ii, &jj, &weight);
        addEdge(graph, ii, jj, weight);
        addEdge(graph, jj, ii, weight);
    }
}

void freeGraph(struct Graph *graph)
{
    int i;
    for (i = 0; i < graph->n; i++)
        free(graph->adjList[i]);
}

void dijkstra(struct Graph *graph, int start)
{
    struct minHeap *priorityQueue = initMinHeap(graph->n * graph->n);

    int *distance = (int *)malloc(sizeof(int) * graph->n);
    int i;
    for (i = 0; i < graph->n; i++)
        distance[i] = INF;

    distance[start] = 0;
    insertElement(priorityQueue, start, 0);

    while (!isEmpty(priorityQueue))
    {
        struct HeapNode current = extractMin(priorityQueue);
        int dest = current.dest;
        int weight = current.weight;

        struct AdjNode *temp = graph->adjList[dest];
        while (temp)
        {
            int newDest = temp->dest;
            int newWeight = temp->weight;

            if (distance[newDest] > weight + newWeight)
            {
                distance[newDest] = weight + newWeight;
                insertElement(priorityQueue, newDest, distance[newDest]);
            }

            temp = temp->next;
        }
    }

    for (i = 0; i < graph->n; i++)
        printf("%d ", distance[i]);
    printf("\n");
}

int main()
{
    struct Graph graph;
    readGraph(&graph);
    dijkstra(&graph, 3);
    freeGraph(&graph);
}