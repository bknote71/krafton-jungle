#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 만약 파라미터가 싱글 포인터이면, 포인터가 가리키는 값을 변경할 수 있지만 포인터 자체는 변경할 수 없다.
void push(Node **top, int data)
{
    Node *p = (Node *)malloc(sizeof(struct Node));
    p->data = data;
    p->next = *top;
    *top = p;
}

int pop(Node **top)
{
    Node *p = *top;
    if (p == NULL)
    {
        printf("top is NULL\n");
        return -1;
    }
    int result = p->data;
    Node *q = p->next;
    *top = q;
    free(p);
    return result;
}

void printstack(Node *t)
{
    Node *p = t;
    printf("in stack ");
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    Node *top = NULL;
    push(&top, 1);
    push(&top, 2);
    push(&top, 3);
    push(&top, 4);

    printstack(top);
    printf("=======================\n");

    printf("pop %d\n", pop(&top));
    printf("pop %d\n", pop(&top));
    printf("pop %d\n", pop(&top));
    printf("pop %d\n", pop(&top));
    printf("pop %d\n", pop(&top));

    return 0;
}