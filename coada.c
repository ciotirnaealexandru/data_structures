#include <stdio.h>
#include <stdlib.h>

struct queueNode
{
    struct stackNode *next;
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

struct queueNode *createNode(int nr) {
    struct queueNode *newNode = (struct queueNode *)malloc(sizeof(struct queueNode));
    
    newNode->next = NULL;
    newNode->nr = nr;
}

int isEmpty(struct stack *stack)
{
    return (stack->top == NULL);
}

void push(struct stack *stack, int nr) {
    struct stackNode *newNode = createNode(nr);
    
    if(isEmpty(stack))
    {
        stack->top = newNode;
        return;
    }

    newNode->prev = stack->top;
    stack->top = newNode;
}

int pop(struct stack *stack)
{
    if(isEmpty(stack))
        return -1;

    int extractedNr = stack->top->nr;
    struct stackNode *temp = stack->top;
    stack->top = stack->top->prev;
    free(temp);
    
    return extractedNr;
}

void freeStack(struct stack *stack)
{
    while(isEmpty(stack))
        pop(stack);
    free(stack);
}

void readStack(struct stack *stack)
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

void printStack(struct stack *stack)
{
    struct stackNode *temp = stack->top;
    while(temp->prev)
    {
        printf("%d ", temp->nr);
        temp = temp->prev;
    }
    printf("\n");
}

int main() {
    struct stack *stack = initStack();
    readStack(stack);
    printStack(stack);
    pop(stack);
    freeStack(stack);
    return 0;
}
