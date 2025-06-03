#include <stdio.h>
#include <stdlib.h>

struct queueNode
{
    struct queueNode *next;
    int nr;
};

struct queue
{
    struct queueNode *head;
    struct queueNode *tail;
};

struct queue *initQueue()
{
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

struct queueNode *createNode(int nr)
{
    struct queueNode *newNode = (struct queueNode *)malloc(sizeof(struct queueNode));

    newNode->next = NULL;
    newNode->nr = nr;

    return newNode;
}

int isEmpty(struct queue *queue)
{
    return (queue->tail == NULL);
}

void enqueue(struct queue *queue, int nr)
{
    struct queueNode *newNode = createNode(nr);

    if (isEmpty(queue))
    {
        queue->head = newNode;
        queue->tail = newNode;
        return;
    }

    queue->tail->next = newNode;
    queue->tail = newNode;
}

int dequeue(struct queue *queue)
{
    if (isEmpty(queue))
        return -1;

    int extractedNr = queue->head->nr;

    struct queueNode *temp = queue->head;
    queue->head = queue->head->next;

    if (queue->head == NULL)
        queue->tail = NULL;

    free(temp);

    return extractedNr;
}

void freeQueue(struct queue *queue)
{
    while (!isEmpty(queue))
        dequeue(queue);
    free(queue);
}

void readQueue(struct queue *queue)
{
    int n, nr, i;
    printf("Numar elemente: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Elementul numarul %d: ", i);
        scanf("%d", &nr);
        enqueue(queue, nr);
    }
}

void printQueue(struct queue *queue)
{
    struct queueNode *temp = queue->head;
    while (temp)
    {
        printf("%d ", temp->nr);
        temp = temp->next;
    }
    printf("\n");
}

int main()
{
    struct queue *queue = initQueue();
    readQueue(queue);
    printQueue(queue);
    freeQueue(queue);
    return 0;
}
