#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct node
{
    int key;
    int height;
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

// 유일한 키를 가지는 avl_tree !!!
typedef struct avl_tree
{
    node *root;
} avl_tree;

void init_tree(avl_tree *t)
{
    t->root = NULL;
}

node *create_node(int key)
{
    node *p = (node *)malloc(sizeof(struct node));
    p->key = key;
    p->height = 0;
    p->left = NULL;
    p->right = NULL;
    p->parent = NULL;
    return p;
}

int height(node *n)
{
    if (n == NULL)
        return 0;
    int ld = height(n->left);
    int rd = height(n->right);
    return MAX(ld, rd) + 1;
}

void updateHeight(node *n)
{
    int lh = height(n->left);
    int rh = height(n->right);
    n->height = 1 + MAX(lh, rh);
}

int getBalance(node *n)
{
    return (n == NULL) ? 0 : height(n->right) - height(n->left);
}

node *rotateRight(node *y)
{
    node *x = y->left;
    node *z = x->right;
    x->right = y;
    y->left = z;
    x->parent = y->parent;
    y->parent = x;
    if (z != NULL)
        z->parent = y;
    updateHeight(y);
    updateHeight(x);
    // printf("x y , xl %d %d %d\n", x->key, y->key, x->left->key);
    return x;
}

node *rotateLeft(node *y)
{
    node *x = y->right;
    node *z = x->left;
    x->left = y;
    y->right = z;
    x->parent = y->parent;
    y->parent = x;
    if (z != NULL)
        z->parent = y;
    updateHeight(y);
    updateHeight(x);
    return x;
}

node *rebalance(node *z)
{
    updateHeight(z);
    int balance = getBalance(z);
    if (balance > 1)
    {
        if (height(z->right->right) > height(z->right->left))
            z = rotateLeft(z);
        else
        {
            z->right = rotateRight(z->right);
            z = rotateLeft(z);
        }
    }
    else if (balance < -1)
    {
        if (height(z->left->left) > height(z->left->right))
            z = rotateRight(z);
        else
        {
            z->left = rotateLeft(z->left);
            z = rotateRight(z);
        }
    }
    // printf("z key? %d\n", z->key);
    return z;
}

void rebalancing(avl_tree *t, node *prev)
{
    for (node *cur = prev; cur != NULL; cur = cur->parent)
    {
        node *cp = cur->parent;
        if (cp != NULL)
        {
            if (cur->key < cp->key)
                cp->left = rebalance(cur);
            else
                cp->right = rebalance(cur);
        }
        if (cur->parent == NULL)
            t->root = cur;
    }
}

void insert(avl_tree *t, int key)
{
    node *p = t->root;
    node *prev;
    if (p == NULL)
    {
        t->root = create_node(key);
        return;
    }
    while (p != NULL && p->key != key)
    {
        prev = p;
        if (key < p->key)
            p = p->left;
        else
            p = p->right;
    }
    if (p != NULL && p->key == key)
    {
        printf("같은 key는 추가할 수 없습니다.\n");
        return;
    }
    node *newnode = create_node(key);
    if (key < prev->key)
        prev->left = newnode;
    else
        prev->right = newnode;
    newnode->parent = prev;

    rebalancing(t, prev);
}

node *most_left_child(node *p)
{
    while (p->left != NULL)
    {
        p = p->left;
    }
    return p;
}

void erase(avl_tree *t, int key)
{
    node *p = t->root;
    node *prev, *succ, *child;
    if (p == NULL)
    {
        printf("avl_tree is empty!\n");
        return;
    }
    while (p != NULL && p->key != key)
    {
        prev = p;
        if (key < p->key)
            p = p->left;
        else
            p = p->right;
    }
    if (p == NULL)
    {
        printf("key 에 해당하는 원소가 없습니다.\n");
        return;
    }

    if (p->left == NULL || p->right == NULL)
    {
        child = (p->left == NULL) ? p->right : p->left;
        if (prev == NULL)
            t->root = child;
        else
        {
            if (prev->left == p)
                prev->left = child;
            else
                prev->right = child;
        }
    }
    else
    {
        node *succ = most_left_child(p->right);

        if (succ->parent->left == succ)
            succ->parent->left = succ->left;
        else
            succ->parent->right = succ->left;

        p->key = succ->key;
        p = succ;
    }

    free(p);

    // rebalancing
    rebalancing(t, prev);
}

void print_by_inorder(node *cur)
{
    if (cur == NULL)
        return;
    node *p = cur;
    printf("%d ", p->key);
    print_by_inorder(p->left);
    print_by_inorder(p->right);
}

int main()
{
    avl_tree t;
    init_tree(&t);

    insert(&t, 9);
    insert(&t, 8);
    insert(&t, 7);
    insert(&t, 6);
    insert(&t, 5);
    insert(&t, 4);
    insert(&t, 3);
    insert(&t, 2);
    insert(&t, 1);
    printf("==============================\n");
    print_by_inorder(t.root);
    printf("\n");
    printf("==============================\n");

    erase(&t, 1);
    erase(&t, 3);
    erase(&t, 5);
    erase(&t, 7);
    printf("==============================\n");
    print_by_inorder(t.root);
    printf("\n");
    printf("==============================\n");

    return 0;
}