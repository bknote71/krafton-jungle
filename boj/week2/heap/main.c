#include "./int_max_heap.h"
#include <stdio.h>

//  gcc -Wall -g int_max_heap.c  main.c -o main
// or
// gcc -c int_max_heap.c
// gcc  int_main_heap.o main.c -o main

int main()
{
    heap h;
    h.size = 0;

    insertHeap(&h, 17);
    insertHeap(&h, 5);
    insertHeap(&h, 30);
    insertHeap(&h, 92);
    insertHeap(&h, 27);
    insertHeap(&h, 64);
    insertHeap(&h, 44);

    printHeap(&h);

    return 0;
}