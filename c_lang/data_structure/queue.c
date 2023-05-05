#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct queue
{
    Node *head, *tail;
} queue;

Node *createNode(int data)
{
    Node *p = (Node *)malloc(sizeof(struct Node));
    p->data = data;
    p->next = NULL;
    return p;
}

void offer(queue *q, int data)
{
    Node *p = createNode(data);
    q->tail->next = p;
    q->tail = p;
}

int poll(queue *q)
{
    if (q->head == q->tail)
    {
        printf("queue is empty\n");
        return -1;
    }
    // 보초 노드는 반드시 존재한다. 따라서 head와 tail은 항상 NULL 이 아니다.
    Node *p = q->head;
    Node *np = p->next;
    int result = np->data;
    q->head = np;
    free(p);
    return result;
}

void printQueue(queue *q)
{
    Node *p = q->head->next;
    printf("in queue: ");
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    queue q;
    q.head = q.tail = createNode(-1);

    offer(&q, 1);
    offer(&q, 2);
    offer(&q, 3);
    offer(&q, 4);

    printQueue(&q);
    printf("====================\n");

    printf("pop %d\n", poll(&q));
    printf("pop %d\n", poll(&q));
    printf("pop %d\n", poll(&q));
    printf("pop %d\n", poll(&q));
    printf("pop %d\n", poll(&q));

    return 0;
}
