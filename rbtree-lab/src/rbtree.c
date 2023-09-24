#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void)
{
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    // TODO: initialize struct if needed
    node_t *t = (node_t *)calloc(1, sizeof(node_t));
    p->nil = t;
    p->root = t;
    t->color = RBTREE_BLACK;
    t->left = t->right = t->parent = NULL;
    return p;
}

void delete_node(node_t *p, node_t *nil)
{
    if (p != nil)
    {
        delete_node(p->left, nil);
        delete_node(p->right, nil);
        free(p);
    }
}

void delete_rbtree(rbtree *t)
{
    // TODO: reclaim the tree nodes's memory
    delete_node(t->root, t->nil);
    free(t->nil);
    free(t);
}

void leftRotation(rbtree *t, node_t *x)
{
    node_t *y = x->right;
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

void rightRotation(rbtree *t, node_t *y)
{
    node_t *x = y->left;
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

void transplant(rbtree *t, node_t *u, node_t *v)
{
    if (u->parent == t->nil)
        t->root = v;
    else if (u->parent->left == u)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

node_t *find_succ(rbtree *t, node_t *p)
{
    node_t *c = p;
    while (c->left != t->nil)
        c = c->left;
    return c;
}

void insert_fixup(rbtree *t, node_t *z)
{
    while (z->parent->color == RBTREE_RED)
    {
        node_t *gp = z->parent->parent;
        node_t *uc = (gp->left == z->parent ? gp->right : gp->left);
        if (gp->left == z->parent)
        {
            if (uc->color == RBTREE_RED)
            {
                gp->color = RBTREE_RED;
                uc->color = RBTREE_BLACK;
                z->parent->color = RBTREE_BLACK;
                z = gp;
            }
            else
            {
                if (z->parent->right == z) // case 2: z 가 오른쪽 자식일 때
                {
                    z = z->parent;
                    leftRotation(t, z);
                }
                z->parent->color = RBTREE_BLACK;
                gp->color = RBTREE_RED;
                rightRotation(t, gp);
            }
        }
        else
        {
            if (uc->color == RBTREE_RED)
            {

                gp->color = RBTREE_RED;
                uc->color = RBTREE_BLACK;
                z->parent->color = RBTREE_BLACK;
                z = gp;
            }
            else
            {
                if (z->parent->left == z) // case 2: z 가 오른쪽 자식일 때
                {
                    z = z->parent;
                    rightRotation(t, z);
                }
                z->parent->color = RBTREE_BLACK;
                gp->color = RBTREE_RED;
                leftRotation(t, gp);
            }
        }
    }
    t->root->color = RBTREE_BLACK;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
    // TODO: implement insert
    node_t *y = t->nil;
    node_t *x = t->root;
    node_t *e = (node_t *)calloc(1, sizeof(node_t));
    e->key = key;
    e->color = RBTREE_RED;
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
    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
    // TODO: implement find
    node_t *z = t->root;
    while (z != t->nil && z->key != key)
    {
        if (key < z->key)
            z = z->left;
        else
            z = z->right;
    }
    return z != t->nil ? z : NULL;
}

node_t *rbtree_min(const rbtree *t)
{
    node_t *p;
    for (p = t->root; p->left != t->nil; p = p->left)
        ;
    return p;
}

node_t *rbtree_max(const rbtree *t)
{
    node_t *p;
    for (p = t->root; p->right != t->nil; p = p->right)
        ;
    return p;
}

void erase_fixup(rbtree *t, node_t *x)
{
    while (x != t->root && x->color == RBTREE_BLACK)
    {
        node_t *w = x == x->parent->left ? x->parent->right : x->parent->left;
        if (x == x->parent->left)
        {
            if (w->color == RBTREE_RED)
            {
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                leftRotation(t, x->parent);
                w = x->parent->right;
            }
            if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
            {
                w->color = RBTREE_RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == RBTREE_BLACK)
                {
                    w->left->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    rightRotation(t, w);
                    w = x->parent->right;
                }
                w->color = w->parent->color;
                w->parent->color = RBTREE_BLACK;
                w->right->color = RBTREE_BLACK;
                leftRotation(t, x->parent);
                x = t->root; // 탈출
            }
        }
        else
        {
            if (w->color == RBTREE_RED)
            {
                w->color = RBTREE_BLACK;
                x->parent->color = RBTREE_RED;
                rightRotation(t, x->parent);
                w = x->parent->left;
            }
            if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
            {
                w->color = RBTREE_RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == RBTREE_BLACK)
                {
                    w->right->color = RBTREE_BLACK;
                    w->color = RBTREE_RED;
                    leftRotation(t, w);
                    w = x->parent->left;
                }
                w->color = w->parent->color;
                w->parent->color = RBTREE_BLACK;
                w->left->color = RBTREE_BLACK;
                rightRotation(t, x->parent);
                x = t->root; // 탈출
            }
        }
    }
    x->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p)
{
    // TODO: implement erase
    if (p == NULL)
        return 0;
    node_t *y = p, *x = NULL;
    color_t y_org_color = y->color;
    if (p->left == t->nil)
    {
        x = p->right;
        transplant(t, p, p->right);
    }
    else if (p->right == t->nil)
    {
        x = p->left;
        transplant(t, p, p->left);
    }
    else
    {
        y = find_succ(t, p->right);
        y_org_color = y->color;
        x = y->right;
        if (y->parent == p)
            x->parent = y;
        else
        {
            transplant(t, y, y->right);
            y->right = p->right;
            y->right->parent = y;
        }
        transplant(t, p, y);
        y->left = p->left;
        y->left->parent = y;
        y->color = p->color;
    }
    free(p);
    if (y_org_color == RBTREE_BLACK)
        erase_fixup(t, x);

    return 0;
}

void indorder_to_array(const rbtree *t, node_t *root, int *pidx, key_t *arr)
{
    if (root != t->nil)
    {
        indorder_to_array(t, root->left, pidx, arr);
        arr[(*pidx)++] = root->key;
        indorder_to_array(t, root->right, pidx, arr);
    }
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    int idx = 0;
    int *pidx = &idx;
    indorder_to_array(t, t->root, pidx, arr);
    return 0;
}
