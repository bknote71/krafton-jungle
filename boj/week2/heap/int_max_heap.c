#include "./int_max_heap.h"
#include <stdio.h>
#include <stdlib.h>

void insertHeap(heap *h, int item)
{
    if (h->size >= MAX - 1)
    {
        printf("Full!!\n");
        return;
    }
    // 제일 끝 노드에 추가
    // 부모 노드와 비교하면서 자신의 위치를 찾는 것 (자신의 부모보다 작고, 자식보다 크다! : max heap)
    int index = ++h->size;
    // 멈추는 조건
    // 1. 루트 노드 일 때 (루트: 1)
    // 2. 부모 노드의 값이 클 때 (부모: index/2)
    while ((index != 1) && (h->data[index / 2] < item))
    {
        h->data[index] = h->data[index / 2];
        index /= 2;
    }
    h->data[index] = item;
}

int deleteHeap(heap *h)
{
    if (h->size == 0)
    {
        printf("Empty!!\n");
        return -1;
    }
    int result = h->data[1], tmp;
    tmp = h->data[h->size--];

    int cur, child;

    cur = 1;
    while ((child = cur * 2) <= h->size)
    {
        if (child + 1 <= h->size &&
            (h->data[child] < h->data[child + 1]))
            ++child;
        if (h->data[child] <= tmp)
            break;
        h->data[cur] = h->data[child];
        cur = child;
    }
    h->data[cur] = tmp;
    return result;
}

void printHeap(heap *h)
{
    printf("My heap: ");
    for (int i = 1; i < h->size + 1; ++i)
    {
        printf("%d ", h->data[i]);
    }
    printf("\n");
}