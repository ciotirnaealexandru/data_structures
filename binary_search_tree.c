#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int nr;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int nr)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->nr = nr;

    return newNode;
}

struct Node *insertNode(struct Node *current, int nr)
{
    if (current == NULL)
        return createNode(nr);

    if (current->nr == nr)
        return current;

    if (current->nr < nr)
        current->right = insertNode(current->right, nr);

    if (current->nr > nr)
        current->left = insertNode(current->left, nr);

    return current;
}

struct Node *searchNode(struct Node *current, int nr)
{
    if (current == NULL)
        return NULL;

    if (current->nr == nr)
        return current;

    if (current->nr < nr)
        return searchNode(current->right, nr);

    if (current->nr > nr)
        return searchNode(current->left, nr);
}

void readBinarySearchTree(struct Node **head)
{
    int n, nr, i;
    printf("Numar de noduri: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Nodul numarul %d: ", i);
        scanf("%d", &nr);
        *head = insertNode(*head, nr);
    }
}

void freeBinarySearchTreee(struct Node *current)
{
    if (current != NULL)
    {
        freeBinarySearchTreee(current->left);
        freeBinarySearchTreee(current->right);
        free(current);
    }
}

void printInorder(struct Node *current)
{
    if (current != NULL)
    {
        printInorder(current->left);
        printf("%d ", current->nr);
        printInorder(current->right);
    }
}

int main()
{
    struct Node *head = NULL;
    readBinarySearchTree(&head);
    printInorder(head);
    freeBinarySearchTreee(head);
    return 0;
}