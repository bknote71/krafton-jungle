#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *ptr = (char *)malloc(sizeof(char));
    printf("ptr: %p\n", ptr);

    *ptr = 'c';

    free(ptr);
    // ptr = NULL;
    printf("ptr? %d %p, %c\n", ptr, ptr, *ptr);

    return 0;
}