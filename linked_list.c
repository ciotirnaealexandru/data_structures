#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int nr;
    struct Node *next;
};

struct Node *createNode(int nr)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->nr = nr;
    newNode->next = NULL;

    return newNode;
}

void insertNode(int nr, struct Node **head)
{
    struct Node *newNode = createNode(nr);

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    struct Node *temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = newNode;
}

void readList(struct Node **head)
{
    int n, nr, i;
    printf("Numar de noduri: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Nodul numarul %d: ", i);
        scanf("%d", &nr);
        insertNode(nr, head);
    }
}

void printList(struct Node *head)
{
    struct Node *current = head;
    while (current)
    {
        printf("%d --> ", current->nr);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(struct Node **head)
{
    struct Node *temp = *head;
    while (temp)
    {
        struct Node *current = temp;
        temp = temp->next;
        free(current);
    }
    *head = NULL;
}

void insertAtBeginning(struct Node **head, int nr)
{
    struct Node *newNode = createNode(nr);

    if ((*head) == NULL)
    {
        *head = newNode;
        return;
    }

    newNode->next = *head;
    (*head) = newNode;
}

void deleteLastNode(struct Node **head)
{
    struct Node *temp = *head;
    while (temp->next->next)
        temp = temp->next;

    struct Node *temp2 = temp;
    temp = temp->next;
    temp2->next = NULL;

    free(temp);
}

int main()
{
    struct Node *head = NULL;
    readList(&head);
    insertAtBeginning(&head, 5);
    deleteLastNode(&head);
    printList(head);
    freeList(&head);
    return 0;
}
