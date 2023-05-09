#include <stdio.h>
#include <stdlib.h>

typedef enum color
{
    black,
    red
} color;

typedef struct node
{
    int key;
    color color; // black: 0 red: 1
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

typedef struct rbtree
{
    struct node *root;
    struct node *nil;
} rbtree;

void init_tree(rbtree *t)
{
    node *p = (node *)malloc(sizeof(struct node));
    p->color = black;
    p->left = NULL;
    p->right = NULL;
    p->parent = NULL;
    t->nil = p;
    t->root = p;
}

void leftRotation(rbtree *t, node *x)
{
    node *y = x->right;
    x->right = y->left;
    if (y->left != t->nil)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == t->nil)
        t->root = y;
    else if (x->parent->left == x)
        x->parent->left = y;
    else
        x->parent->right = y;
    x->parent = y;
    y->left = x;
}

void rightRotation(rbtree *t, node *y)
{
    node *x = y->left;
    y->left = x->right;
    if (x->right != t->nil)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == t->nil)
        t->root = x;
    else if (y->parent->left == y)
        y->parent->left = x;
    else
        y->parent->right = x;
    y->parent = x;
    x->right = y;
}

void insert_fixup(rbtree *t, node *z)
{
    while (z->parent->color == red)
    {
        node *gp = z->parent->parent;
        node *uc = (gp->left == z->parent ? gp->right : gp->left);
        if (gp->left == z->parent)
        {
            if (uc->color == red)
            {
                gp->color = red;
                uc->color = black;
                z->parent->color = black;
                z = gp;
            }
            else
            {
                if (z->parent->right == z) // case 2: z 가 오른쪽 자식일 때
                {
                    z = z->parent;
                    leftRotation(t, z);
                }
                z->parent->color = black;
                gp->color = red;
                rightRotation(t, gp);
            }
        }
        else
        {
            if (uc->color == red)
            {

                gp->color = red;
                uc->color = black;
                z->parent->color = black;
                z = gp;
            }
            else
            {
                if (z->parent->left == z) // case 2: z 가 오른쪽 자식일 때
                {
                    z = z->parent;
                    rightRotation(t, z);
                }
                z->parent->color = black;
                gp->color = red;
                leftRotation(t, gp);
            }
        }
    }
    t->root->color = black;
}

void insert(rbtree *t, int key)
{
    node *y = t->nil;
    node *x = t->root;
    node *e = (node *)malloc(sizeof(struct node));
    e->key = key;
    e->color = red;
    e->left = e->right = t->nil;
    while (x != t->nil)
    {
        y = x;
        if (e->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    e->parent = y;
    if (y == t->nil)
        t->root = e;
    else if (e->key < y->key)
        y->left = e;
    else
        y->right = e;
    insert_fixup(t, e);
}

node *find_succ(rbtree *t, node *p)
{
    node *c = p;
    while (c->left != t->nil)
        c = c->left;
    return c;
}

void erase_fixup(rbtree *t, node *x)
{
    while (x != t->root && x->color == black)
    {
        node *w = x == x->parent->left ? x->parent->right : x->parent->left;
        if (x == x->parent->left)
        {
            if (w->color == red)
            {
                w->color = black;
                x->parent->color = red;
                leftRotation(t, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == black && w->right->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else
            {
                if (w->right->color == black)
                {
                    w->left->color = black;
                    w->color = red;
                    rightRotation(t, w);
                    w = x->parent->right;
                }
                w->color = w->parent->color;
                w->parent->color = black;
                w->right->color = black;
                leftRotation(t, x->parent);
                x = t->root; // 탈출
            }
        }
        else
        {
            if (w->color == red)
            {
                w->color = black;
                x->parent->color = red;
                rightRotation(t, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == black && w->right->color == black)
            {
                w->color = red;
                x = x->parent;
            }
            else
            {
                if (w->left->color == black)
                {
                    w->right->color = black;
                    w->color = red;
                    leftRotation(t, w);
                    w = x->parent->left;
                }
                w->color = w->parent->color;
                w->parent->color = black;
                w->left->color = black;
                rightRotation(t, x->parent);
                x = t->root; // 탈출
            }
        }
    }
    x->color = black;
}

void transplant(rbtree *t, node *u, node *v)
{
    if (u->parent == t->nil)
        t->root = v;
    else if (u->parent->left == u)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

void erase(rbtree *t, int key)
{
    node *x, *y;
    x = y = t->nil;
    node *z = t->root;
    while (z != t->nil && z->key != key)
    {
        if (key < z->key)
            z = z->left;
        else
            z = z->right;
    }
    if (z == t->nil)
    {
        printf("삭제할 수 있는 노드가 없습니다\n");
        return;
    }
    y = z;
    color y_org_color = y->color;
    if (z->left == t->nil)
    {
        x = z->right;
        transplant(t, z, z->right);
    }
    else if (z->right == t->nil)
    {
        x = z->left;
        transplant(t, z, z->left);
    }
    else
    {
        y = find_succ(t, z->right);
        printf("%d is replaced key: %d, color? %d\n", z->key, y->key, y->color);
        y_org_color = y->color;
        x = y->right;
        if (y->parent == z)
            x->parent = y;
        else
        {
            transplant(t, y, y->right);
            y->right = z->right;
            printf("%d\n", y->right->key);
            y->right->parent = y;
        }
        transplant(t, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    printf("root key? %d and z, y key %d %d\n", t->root->key, z->key, y->key);
    free(z);
    printf("root key? %d\n", t->root->key);
    if (y_org_color == black)
        erase_fixup(t, x);
}

void print_tree(rbtree *t, node *p)
{
    if (p == t->nil)
        return;
    printf("in tree: %d\n", p->key);
    print_tree(t, p->left);
    print_tree(t, p->right);
}

int main()
{
    rbtree t;
    init_tree(&t);

    insert(&t, 1);
    insert(&t, 2);
    insert(&t, 3);
    insert(&t, 4);
    insert(&t, 5);
    insert(&t, 6);
    insert(&t, 7);
    insert(&t, 8);
    insert(&t, 9);

    printf("print tree\n");
    print_tree(&t, t.root);

    erase(&t, 4);

    printf("print tree\n");
    print_tree(&t, t.root);

    return 0;
}