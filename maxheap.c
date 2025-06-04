#include <stdio.h>
#include <stdlib.h>

struct MaxHeap
{
    int n;
    int *arr;
};

void initMaxHeap(struct MaxHeap *maxHeap, int n)
{
    maxHeap->arr = (int *)malloc(sizeof(int) * n);
    maxHeap->n = 0;
}

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void heapifyUp(struct MaxHeap *maxHeap, int current)
{
    int parent = (current - 1) / 2;

    if (parent >= 0)
    {
        if (maxHeap->arr[parent] < maxHeap->arr[current])
        {
            swap(&maxHeap->arr[parent], &maxHeap->arr[current]);
            heapifyUp(maxHeap, parent);
        }
    }
}

void heapifyDown(struct MaxHeap *maxHeap, int current)
{
    int left = current * 2 + 1;
    int right = current * 2 + 2;

    int largest = current;

    if (left < maxHeap->n && maxHeap->arr[largest] < maxHeap->arr[left])
        largest = left;

    if (right < maxHeap->n && maxHeap->arr[largest] < maxHeap->arr[right])
        largest = right;

    if (largest != current)
    {
        swap(&maxHeap->arr[current], &maxHeap->arr[largest]);
        heapifyDown(maxHeap, largest);
    }
}

void insertElement(struct MaxHeap *maxHeap, int nr)
{
    maxHeap->arr[maxHeap->n] = nr;
    maxHeap->n++;

    heapifyUp(maxHeap, maxHeap->n - 1);
}

int extractMax(struct MaxHeap *maxHeap)
{
    if (maxHeap->n == 0)
        return -1;

    int max = maxHeap->arr[0];
    swap(&maxHeap->arr[0], &maxHeap->arr[maxHeap->n - 1]);
    maxHeap->n--;
    heapifyDown(maxHeap, 0);

    return max;
}

void readMaxHeap(struct MaxHeap *maxHeap)
{
    int i, nr, n;
    printf("Insert MaxHeap size: ");
    scanf("%d", &n);
    initMaxHeap(maxHeap, n);

    for (i = 0; i < n; i++)
    {
        printf("Insert element number %d: ", i);
        scanf("%d", &nr);
        insertElement(maxHeap, nr);
    }
}

void printMaxHeap(struct MaxHeap *maxHeap)
{
    int i;
    for (i = 0; i < maxHeap->n; i++)
        printf("%d ", maxHeap->arr[i]);
    printf("\n");
}

void freeMaxHeap(struct MaxHeap *maxHeap)
{
    free(maxHeap->arr);
}

void heapSort(int array[], int n)
{
    struct MaxHeap maxHeap;
    initMaxHeap(&maxHeap, n);

    int i;
    for (i = 0; i < n; i++)
        insertElement(&maxHeap, array[i]);
    for (i = 0; i < n; i++)
        array[n - i - 1] = extractMax(&maxHeap);

    freeMaxHeap(&maxHeap);
}

int main()
{
    // struct MaxHeap maxHeap;
    // readMaxHeap(&maxHeap);
    // printMaxHeap(&maxHeap);
    // printf("%d\n", extractMax(&maxHeap));
    // printMaxHeap(&maxHeap);

    // heapsort
    int array[] = {6, 4, 3, 2, 4, 3};
    heapSort(array, 6);
    for (int i = 0; i < 6; i++)
        printf("%d ", array[i]);
    printf("\n");

    // freeMaxHeap(&maxHeap);
    return 0;
}