#include <stdio.h>
#include <stdlib.h>

struct StackNode
{
    struct StackNode *prev;
    int nr;
};

struct Stack
{
    struct StackNode *top;
};

struct Stack *initStack()
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->top = NULL;

    return stack;
}

struct StackNode *createNode(int nr)
{
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));

    newNode->prev = NULL;
    newNode->nr = nr;

    return newNode;
}

int isEmpty(struct Stack *stack)
{
    return (stack->top == NULL);
}

void push(struct Stack *stack, int nr)
{
    struct StackNode *newNode = createNode(nr);

    if (isEmpty(stack))
    {
        stack->top = newNode;
        return;
    }

    newNode->prev = stack->top;
    stack->top = newNode;
}

int pop(struct Stack *stack)
{
    if (isEmpty(stack))
        return -1;

    int extractedNr = stack->top->nr;
    struct StackNode *temp = stack->top;
    stack->top = stack->top->prev;
    free(temp);

    return extractedNr;
}

void freeStack(struct Stack *stack)
{
    while (!isEmpty(stack))
        pop(stack);
    free(stack);
}

void readStack(struct Stack *stack)
{
    int n, nr, i;
    printf("Numar elemente: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Elementul numarul %d: ", i);
        scanf("%d", &nr);
        push(stack, nr);
    }
}

struct AdjNode
{
    int dest;
    struct AdjNode *next;
};

struct Graph
{
    int n;
    struct AdjNode **arr;
};

struct AdjNode *createAdjNode(int dest)
{
    struct AdjNode *newNode = (struct AdjNode *)malloc(sizeof(struct AdjNode));
    newNode->dest = dest;
    newNode->next = NULL;

    return newNode;
}

void initGraph(struct Graph *graph, int n)
{
    int i;
    graph->arr = (struct AdjNode **)malloc(sizeof(struct AdjNode *) * n);
    graph->n = n;
    for (i = 0; i < n; i++)
        graph->arr[i] = NULL;
}

void addEdge(struct Graph *graph, int ii, int jj)
{
    if (ii >= graph->n)
        return;

    int nodeExists = 0;
    struct AdjNode *temp = graph->arr[ii];
    while (temp)
    {
        if (temp->dest == jj)
            nodeExists = 1;
        temp = temp->next;
    }

    if (nodeExists)
        return;

    struct AdjNode *newNode = createAdjNode(jj);
    newNode->next = graph->arr[ii];
    graph->arr[ii] = newNode;
}

void freeGraph(struct Graph *graph)
{
    for (int i = 0; i < graph->n; i++)
    {
        struct AdjNode *current = graph->arr[i];
        while (current)
        {
            struct AdjNode *next = current->next;
            free(current);
            current = next;
        }
    }
    free(graph->arr);
}

void printGraph(struct Graph *graph)
{
    int i, j;
    for (i = 0; i < graph->n; i++)
    {
        printf("%d: ", i);

        struct AdjNode *current = graph->arr[i];
        while (current)
        {
            printf("%d ", current->dest);
            current = current->next;
        }

        printf("\n");
    }
}

void readGraph(struct Graph *graph, struct Graph *inverseGraph)
{
    int n, m, i, ii, jj;
    printf("Number of nodes: ");
    scanf("%d", &n);

    graph->n = n;
    inverseGraph->n = n;

    initGraph(graph, n);
    initGraph(inverseGraph, n);

    printf("Number of edges: ");
    scanf("%d", &m);

    for (i = 0; i < m; i++)
    {
        printf("Insert edge number %d: ", i);
        scanf("%d%d", &ii, &jj);

        addEdge(graph, ii, jj);
        addEdge(inverseGraph, jj, ii);
    }
}

void resetArray(int *array, int n)
{
    int i;
    for (i = 0; i < n; i++)
        array[i] = 0;
}

void dfs1(struct Graph *graph, int current, int *exists, struct Stack *stack)
{
    exists[current] = 1;
    struct AdjNode *temp = graph->arr[current];
    while (temp)
    {
        if (!exists[temp->dest])
            dfs1(graph, temp->dest, exists, stack);
        temp = temp->next;
    }
    push(stack, current);
}

void dfs2(struct Graph *inverseGraph, int current, int *exists)
{
    exists[current] = 1;
    printf("%d ", current);
    struct AdjNode *temp = inverseGraph->arr[current];
    while (temp)
    {
        if (!exists[temp->dest])
            dfs2(inverseGraph, temp->dest, exists);
        temp = temp->next;
    }
}

void kosaraju()
{
    struct Stack *stack = initStack();

    struct Graph graph, inverseGraph;
    readGraph(&graph, &inverseGraph);

    int *exists = (int *)malloc(sizeof(int) * graph.n);
    resetArray(exists, graph.n);

    int i;
    for (i = 0; i < graph.n; i++)
        if (!exists[i])
            dfs1(&graph, i, exists, stack);

    resetArray(exists, graph.n);
    while (!isEmpty(stack))
    {
        int current = pop(stack);
        if (!exists[current])
        {
            dfs2(&inverseGraph, current, exists);
            printf("\n");
        }
    }

    freeGraph(&graph);
    freeGraph(&inverseGraph);

    freeStack(stack);
}

int main()
{
    kosaraju();
    return 0;
}