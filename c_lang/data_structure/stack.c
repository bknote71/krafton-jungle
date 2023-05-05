#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct stack
{
    struct Node *top;
} stack;

// push and pop
// stack의 주소를 가리키고 있는 s 포인터
// 만약 이 프로시저 내부에서 s를 변경하면 주소에 직접 접근하여 변경하기 때문에 변경한 값이 반영이 된다.
void push(stack *s, int data)
{
    Node *p = (Node *)malloc(sizeof(struct Node));
    p->data = data;
    p->next = s->top;
    s->top = p;
}

int pop(stack *s)
{
    Node *p = s->top;
    if (p == NULL)
        return -1;
    // 없으면 NULL
    // 이중 포인터를 안 써도 된다. 왜냐하면 s가 가리키는 주소에 직접 접근해서 변경하기 때문이다.
    Node *q = p->next;
    int ret = p->data;
    s->top = q;

    free(p);
    return ret;
}

void printStack(stack *s)
{
    Node *p = s->top;
    printf("in stack: ");
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    stack s;
    s.top = NULL;

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    push(&s, 4);

    printStack(&s);
    printf("=====================\n");

    printf("pop %d\n", pop(&s));
    printf("pop %d\n", pop(&s));
    printf("pop %d\n", pop(&s));
    printf("pop %d\n", pop(&s));
    printf("pop %d\n", pop(&s));

    return 0;
}