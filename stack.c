#include <stdio.h>
#include <stdlib.h>

struct stackNode
{
    struct stackNode *prev;
    int nr;
};

struct stack
{
    struct stackNode *top;
};

struct stack *initStack()
{
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    stack->top = NULL;

    return stack;
}

struct stackNode *createNode(int nr)
{
    struct stackNode *newNode = (struct stackNode *)malloc(sizeof(struct stackNode));

    newNode->prev = NULL;
    newNode->nr = nr;

    return newNode;
}

int isEmpty(struct stack *stack)
{
    return (stack->top == NULL);
}

void push(struct stack *stack, int nr)
{
    struct stackNode *newNode = createNode(nr);

    if (isEmpty(stack))
    {
        stack->top = newNode;
        return;
    }

    newNode->prev = stack->top;
    stack->top = newNode;
}

int pop(struct stack *stack)
{
    if (isEmpty(stack))
        return -1;

    int extractedNr = stack->top->nr;
    struct stackNode *temp = stack->top;
    stack->top = stack->top->prev;
    free(temp);

    return extractedNr;
}

void freeStack(struct stack *stack)
{
    while (!isEmpty(stack))
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
    while (temp->prev)
    {
        printf("%d ", temp->nr);
        temp = temp->prev;
    }
    printf("%d ", temp->nr);
    printf("\n");
}

int main()
{
    struct stack *stack = initStack();
    readStack(stack);
    printStack(stack);
    freeStack(stack);
    return 0;
}
