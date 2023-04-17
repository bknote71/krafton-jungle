#ifndef INT_MAX_HEAP_H
#define INT_MAX_HEAP_H

#define MAX 10000

typedef struct heap
{
    int data[MAX];
    int size; // MAX - 1이면 꽉 찬 것!
} heap;

void insertHeap(heap *h, int item);
int deleteHeap(heap *h);
void printHeap(heap *h);

#endif