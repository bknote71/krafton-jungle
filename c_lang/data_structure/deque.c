#include <stdio.h>
#include <stdlib.h>

// deque 는 센티넬 노드로는 지금은 사용 못하겠다.
// 자바의 경우에는 item == NULL 인 센티넬 노드를 만들 수 있는데
// 지금은 int 형만 하니까...
typedef struct Node
{
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct deque
{
    Node *head, *tail;
} deque;

Node *createNode(int data)
{
    Node *p = (Node *)malloc(sizeof(struct Node));
    p->data = data;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void init_deque(deque *dq)
{
    dq->head = NULL;
    dq->tail = NULL;
}

void offerFirst(deque *dq, int data)
{
    Node *p = createNode(data);
    if (dq->head == NULL)
    {
        dq->head = p;
        dq->tail = p;
        return;
    }
    dq->head->prev = p;
    p->next = dq->head;
    dq->head = p;
}
void offerLast(deque *dq, int data)
{
    Node *p = createNode(data);
    if (dq->tail == NULL)
    {
        dq->head = p;
        dq->tail = p;
        return;
    }
    dq->tail->next = p;
    p->prev = dq->tail;
    dq->tail = p;
}

int pollFirst(deque *dq)
{
    if (dq->head == NULL)
    {
        printf("deque is empty\n");
        return -1;
    }
    Node *p = dq->head;
    Node *q = p->next;
    int result = p->data;
    if (q != NULL) // q 가 NULL 일 때 next 접근하면 segmentation fault 발생!!
        q->prev = NULL;
    dq->head = q;
    free(p);
    return result;
}

int pollLast(deque *dq)
{
    if (dq->tail == NULL)
    {
        printf("deque is empty\n");
        return -1;
    }
    Node *p = dq->tail;
    Node *q = p->prev;
    int result = p->data;
    if (q != NULL)
        q->next = NULL;
    dq->tail = q;
    free(p);
    return result;
}

void printDeque(deque *dq)
{
    printf("in deque: ");
    Node *p = dq->head;
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    deque dq;
    init_deque(&dq);

    offerFirst(&dq, 1);
    offerFirst(&dq, 2);
    offerFirst(&dq, 3);
    offerFirst(&dq, 4);

    printDeque(&dq);

    printf("pop %d\n", pollFirst(&dq));
    printf("pop %d\n", pollFirst(&dq));
    printf("pop %d\n", pollFirst(&dq));
    printf("pop %d\n", pollFirst(&dq));
    printf("pop %d\n", pollFirst(&dq));

    offerFirst(&dq, 1);
    offerFirst(&dq, 2);
    offerFirst(&dq, 3);
    offerFirst(&dq, 4);

    printDeque(&dq);

    printf("pop %d\n", pollLast(&dq));
    printf("pop %d\n", pollLast(&dq));
    printf("pop %d\n", pollLast(&dq));
    printf("pop %d\n", pollLast(&dq));
    printf("pop %d\n", pollLast(&dq));

    return 0;
}