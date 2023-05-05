// max heap
#include <stdio.h>
#include <stdlib.h>

const int MAX = 1000;
typedef struct heap
{
    int size;
    int arr[MAX];
} heap;

void push(heap *h, int data)
{
    int index = ++h->size;
    while (index > 1 && h->arr[index / 2] < data)
    {
        h->arr[index] = h->arr[index / 2];
        index /= 2;
    }
    h->arr[index] = data;
    printf("push %d data at %d index\n", data, index);
}

int pop(heap *h)
{
    int index = 1;
    int result = h->arr[1];
    int k = h->arr[h->size--];

    int child;
    while ((child = index * 2) <= h->size)
    {
        if ((child + 1 <= h->size) && h->arr[child] < h->arr[child + 1])
            ++child;
        if (h->arr[child] <= k)
            break;
        h->arr[index] = h->arr[child];
        index = child;
    }
    h->arr[index] = k;
    return result;
}

void printHeap(heap *h)
{
    printf("my heap: ");
    for (int i = 1; i < h->size + 1; ++i)
    {
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}

int main()
{
    heap h;
    h.size = 0;

    push(&h, 1);
    push(&h, 2);
    push(&h, 3);
    push(&h, 4);
    push(&h, 5);

    printHeap(&h);
    printf("=============================\n");

    printf("pop %d\n", pop(&h));
    printf("pop %d\n", pop(&h));
    printf("pop %d\n", pop(&h));
    printf("pop %d\n", pop(&h));
    printf("pop %d\n", pop(&h));

    return 0;
}