#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int INIT_CAPACITY = 0;

typedef struct node
{
    int key;
    int value;
    int hash;
    struct node *next;
} node;

typedef struct hashtable
{
    node **table; // 원래는 0으로 초기화 <<
    float load_factor;
    int size;
    int capacity; // length == capacity
    int threshold;
} hashtable;

int hashing(int key)
{
    return key;
}

void init_hashtable(hashtable *h)
{
    h->table = NULL;
    h->load_factor = 0.75f;
    h->threshold = 0;
    h->size = 0;
    h->capacity = 0;
}

node *create_node(int key, int value, int hash, node *next)
{
    node *p = (node *)malloc(sizeof(struct node));
    p->key = key;
    p->value = value;
    p->hash = hash;
    p->next = next;
    return p;
}

void resize(hashtable *h)
{
    // size ?
    printf("resize\n");
    int old_capacity = h->table == NULL ? 0 : h->capacity;
    int new_capacity = old_capacity > 0 ? old_capacity << 1 : 1;
    printf("old and new %d %d\n", old_capacity, new_capacity);
    // 포인터의 배열 동적 할당받기
    node **new_table = (node **)malloc(sizeof(node *) * new_capacity);
    if (h->table != NULL)
    {
        for (int i = 0; i < old_capacity; ++i)
        {
            node *p;
            if ((p = h->table[i]) != NULL)
            {
                printf("i table key %d\n", h->table[i]->key);
                h->table[i] = NULL;
                if (p->next == NULL)
                {
                    new_table[p->hash & (new_capacity - 1)] = p;
                }
                else
                {
                    node *loh, *lot;
                    node *hih, *hit;
                    node *q;
                    loh = lot = hih = hit = q = NULL;
                    do
                    {
                        q = p->next;
                        if ((p->hash & old_capacity) == 0) // 기존과 변경 없음
                        {
                            if (lot == NULL)
                                loh = p;
                            else
                                lot->next = p;
                            lot = p;
                        }
                        else // 기존 인덱스 + old_capacity
                        {
                            if (hit == NULL)
                            {
                                hih = p;
                            }
                            else
                                hit->next = p;
                            hit = p;
                        }
                    } while ((p = q) != NULL);
                    if (lot != NULL)
                    {
                        lot->next = NULL;
                        new_table[i] = loh;
                    }
                    if (hit != NULL)
                    {
                        hit->next = NULL;
                        new_table[i + old_capacity] = hih;
                    }
                }
            }
        }
    }
    free(h->table);
    h->table = new_table;
    h->capacity = new_capacity;
    h->threshold = (int)(h->load_factor * new_capacity);
    printf("complete resize!\n");
}

void put_value(hashtable *h, int key, int value)
{
    node *p, *prev;
    int i, n;
    int hash = hashing(key);
    if (h->table == NULL || (n = h->capacity) == 0)
    {
        printf("h cap? %d\n", h->capacity);
        resize(h);
    }
    if ((p = h->table[i = (hash & (n - 1))]) == NULL)
        h->table[i] = create_node(key, value, hash, NULL);
    else
    {
        while (p != NULL && p->key != key)
        {
            prev = p;
            p = p->next;
        }
        if (p == NULL)
            prev->next = create_node(key, value, hash, NULL);
        else
        {
            p->value = value;
            return;
        }
    }
    if (++h->size > h->threshold)
    {
        printf("h size and threshold %d %d\n", h->size, h->threshold);
        resize(h);
    }
}

void remove_node(hashtable *h, int key)
{
    node *p, *q, *node = NULL;
    int i, n;
    int hash = hashing(key);
    if ((n = h->capacity) == 0 || (p = h->table[i = (hash & (n - 1))]) == NULL)
        return;
    if (p->key == key)
    {
        node = p;
        h->table[i] = node->next;
    }
    else
    {
        while ((q = p->next) != NULL)
        {
            if (q->key == key)
            {
                node = q;
                break;
            }
            p = q;
        }
        if (node != NULL)
            p->next = node->next;
    }
    free(node);
    --h->size;
}

int find_value(hashtable *h, int key)
{
    node *p, *q;
    int i, n;
    int hash = hashing(key);
    if ((n = h->capacity) == 0 || (p = h->table[i = (hash & (n - 1))]) == NULL)
        return -1;
    if (p->key == key)
        return p->value;
    while ((q = p->next) != NULL)
    {
        if (q->key == key)
            return q->value;
        p = q;
    }
    return -1;
}

void printHashTable(hashtable *h)
{
    for (int i = 0; i < h->capacity; ++i)
    {
        node *p = h->table[i];
        while (p != NULL)
        {
            printf("%d index, %d key %d value\n", i, p->key, p->value);
            p = p->next;
        }
    }
}

int main()
{
    hashtable h;
    init_hashtable(&h);

    put_value(&h, 1, 1);
    put_value(&h, 2, 2);
    put_value(&h, 5, 5);
    put_value(&h, 21, 21);
    put_value(&h, 31, 31);
    put_value(&h, 49, 49);

    printHashTable(&h);

    remove_node(&h, 1);
    remove_node(&h, 21);
    remove_node(&h, 49);

    printf("after remove some nodes\n");
    printHashTable(&h);

    printf("%d\n", find_value(&h, 1));
    printf("%d\n", find_value(&h, 22));
    printf("%d\n", find_value(&h, 5));

    return 0;
}