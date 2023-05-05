#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

typedef struct tree
{
    node *root;
} tree;

void init_tree(tree *t)
{
    t->root = NULL;
}

node *create_node(int data)
{
    node *p = (node *)malloc(sizeof(struct node));
    p->data = data;
    p->left = NULL;
    p->right = NULL;
    p->parent = NULL;
    return p;
}

// 현재 노드의 키보다 작거나 같은쪽 왼쪽, 아니면 오른쪽
// 만약 해당 방향의 자식이 없으면 자식으로 삽입
void insert(tree *t, int data)
{
    node *p = t->root;
    if (p == NULL)
    {
        t->root = create_node(data);
        return;
    }
    node *newnode = create_node(data);
    node *prev = NULL;
    while (p != NULL)
    {
        prev = p;
        if (data <= p->data)
            p = p->left;
        else
            p = p->right;
    }

    if (data <= prev->data)
    {
        prev->left = newnode;
    }
    else
    {
        prev->right = newnode;
    }
    newnode->parent = prev;
}

void erase(tree *t, int data)
{
    node *p = t->root;
    node *prev = NULL, *succ = NULL, *psucc;
    node *child = NULL;
    if (p == NULL)
    {
        printf("tree is empty!\n");
        return;
    }
    while (p != NULL)
    {
        prev = p;
        if (data < p->data)
            p = p->left;
        else if (data > p->data)
            p = p->right;
        else
            break;
    }

    if (p == NULL)
    {
        printf("no item found\n");
        return;
    }

    // 삭제할 노드가 단말 노드인 경우
    if ((p->left == NULL) && (p->right == NULL))
    {
        if (prev != NULL)
        {
            if (prev->left == p)
                prev->left = NULL;
            else
                prev->right = NULL;
        }
        else
            t->root = NULL;
    }

    // 삭제할 노드가 자식 노드를 한 개 가진 경우
    else if ((p->left == NULL) || (p->right == NULL))
    {
        if (p->left != NULL)
            child = p->left;
        else
            child = p->right;

        if (prev != NULL)
        {
            if (prev->left == p)
                prev->left = child;
            else
                prev->right = child;
        }

        else
            t->root = child;
    }
    // 삭제할 노드가 자식 노드를 두 개 가진 경우
    else
    {
        succ = p->left;
        while (succ->right != NULL)
        {
            succ = succ->right;
        }
        if (succ->parent->left == succ)
        {
            succ->parent->left = succ->left;
        }
        else
        {
            succ->parent->right = succ->left;
        }
        if (succ->left != NULL)
            succ->left->parent = succ->parent;
        p->data = succ->data;
        p = succ;
    }
    free(p);
}

void print_by_inorder(node *cur)
{
    if (cur == NULL)
        return;
    node *p = cur;
    printf("%d ", p->data);
    print_by_inorder(p->left);
    print_by_inorder(p->right);
}

void print_by_preorder(node *cur)
{
    if (cur == NULL)
        return;
    node *p = cur;
    print_by_preorder(p->left);
    printf("%d ", p->data);
    print_by_preorder(p->right);
}

void print_by_postorder(node *cur)
{
    if (cur == NULL)
        return;
    node *p = cur;
    print_by_postorder(p->left);
    print_by_postorder(p->right);
    printf("%d ", p->data);
}

int main()
{
    tree t;
    init_tree(&t);

    insert(&t, 5);
    insert(&t, 2);
    insert(&t, 1);
    insert(&t, 4);
    insert(&t, 3);
    insert(&t, 8);
    insert(&t, 6);
    insert(&t, 7);
    insert(&t, 9);

    print_by_inorder(t.root);
    printf("\n");
    print_by_preorder(t.root);
    printf("\n");
    print_by_postorder(t.root);
    printf("\n");

    erase(&t, 5);
    print_by_inorder(t.root);
    printf("\n");
    erase(&t, 2);
    print_by_inorder(t.root);
    printf("\n");
    erase(&t, 4);
    print_by_inorder(t.root);
    printf("\n");

    return 0;
}