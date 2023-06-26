#include <stdio.h>

int *KERN_BASE = (int *)0x8004000000;

int return_nullptr()
{
    return *(int *)NULL;
}

int kern_pointer()
{
    return *KERN_BASE;
}

int main()
{
    // case 0: NULL 이 가리키는 곳에 값 넣기. (segmentation fault)
    // *(int *)NULL = 42;

    // case 1: NULL pouinter가 가리키는 곳? segmentation fault
    // return_nullptr();

    // *(NULL)
    // - NULL 포인터가 가리키는 곳에 접근
    // - 잘못됨

    // case 2, 3, 4: kern base 접근 : user 모드에서 접근할 수 없다.
    // invalid 한 메모리 접근이다!
    // kern_pointer();
    // *KERN_BASE = 42;

    // default: NOT_REACHED();

    printf("pass!\n");
    return 0;
}