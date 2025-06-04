#include <stdio.h>
#include <stdlib.h>

struct Node
{
    struct Node *left;
    struct Node *right;
    int height;
    int nr;
};

struct Node *createNode(int nr)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->nr = nr;
    newNode->height = 1;

    return newNode;
}

int height(struct Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    y->left = T2;
    x->right = y;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    x->right = T2;
    y->left = x;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

struct Node *insertNode(struct Node *current, int nr)
{
    // insert the node like in a binary search tree
    if (current == NULL)
        return createNode(nr);

    if (current->nr == nr)
        return current;

    if (current->nr < nr)
        current->right = insertNode(current->right, nr);

    if (current->nr > nr)
        current->left = insertNode(current->left, nr);

    current->height = max(height(current->left), height(current->right)) + 1;

    int balance = getBalance(current);

    // right right
    if (balance > 1 && nr < current->left->nr)
        return rightRotate(current);

    // left left
    if (balance < -1 && nr > current->right->nr)
        return leftRotate(current);

    // left right
    if (balance > 1 && nr > current->left->nr)
    {
        current->left = leftRotate(current->left);
        return rightRotate(current);
    }

    // right left
    if (balance < -1 && nr < current->right->nr)
    {
        current->right = rightRotate(current->right);
        return leftRotate(current);
    }

    return current;
}

void readAVLTree(struct Node **head)
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

void printInorder(struct Node *current)
{
    if (current != NULL)
    {
        printInorder(current->left);
        printf("%d ", current->nr);
        printInorder(current->right);
    }
}

void freeAVLTree(struct Node *current)
{
    if (current != NULL)
    {
        freeAVLTree(current->left);
        freeAVLTree(current->right);
        free(current);
    }
}

int main()
{
    struct Node *head = NULL;
    readAVLTree(&head);
    printInorder(head);
    freeAVLTree(head);
    return 0;
}