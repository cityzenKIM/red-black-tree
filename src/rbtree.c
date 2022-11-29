#include "rbtree.h"

#include <stdlib.h>
#include <stdio.h>
#define SENTINEL
rbtree *new_rbtree(void)
{
    // TODO: initialize struct if needed
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    node_t *nilNode = (node_t *)calloc(1, sizeof(node_t));
    if (!p || !nilNode)
    {
        printf("error");
        return 0;
    }
    nilNode->color = RBTREE_BLACK;
    nilNode->key = 0;
    nilNode->parent = NULL;
    nilNode->left = NULL;
    nilNode->right = NULL;
    p->nil = nilNode;
    p->root = p->nil;
    return p;
}
node_t *new_node(key_t value)
{
    node_t *node = (node_t *)calloc(1, sizeof(node_t));
    node->color = RBTREE_RED;
    node->key = value;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}
void delete_by_postorder(rbtree *t, node_t *root)
{
    if (root == t->nil)
        return;
    delete_by_postorder(t, root->left);
    delete_by_postorder(t, root->right);
    free(root);
}

void delete_rbtree(rbtree *t)
{
    // TODO: reclaim the tree nodes's memory
    if (!t)
        return;
    delete_by_postorder(t, t->root);
    free(t->nil);
    free(t);
}

void left_rotate(rbtree *t, node_t *x)
{
    // set y
    node_t *y;
    y = x->right;

    // y의 왼쪽 서브트리를 x의 오른쪽 서브트리로 전환
    x->right = y->left;
    if (y->left != t->nil)
        y->left->parent = x;
    // x의 부모 노드를 y의 부모 노드로 바꿔준다
    y->parent = x->parent;
    if (x->parent == t->nil)
        t->root = y;

    // x가 x의 부모의 왼쪽이면
    else if (x == x->parent->left)
        x->parent->left = y;
    // x가 x의 부모의 오른쪽이면
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void right_rotate(rbtree *t, node_t *y)
{
    // set y
    node_t *x;
    x = y->left;

    // x의 오른쪽 서브트리를 y의 왼쪽 서브트리로 전환
    y->left = x->right;
    if (x->right != t->nil)
        x->right->parent = y;
    // x의 부모를 y의 부모로 바꿔준다
    x->parent = y->parent;
    if (y->parent == t->nil)
        t->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

void insert_fix_up(rbtree *t, node_t *z)
{
    node_t *uncle;
    node_t *parent;
    node_t *grandpa;
    // if (z->parent)
    //     parent = z->parent;
    // if (z->parent->parent)
    //     grandpa = z->parent->parent;
    while (z->parent->color == RBTREE_RED)
    {
        parent = z->parent;
        grandpa = z->parent->parent;
        // 부모 노드가 할아버지 노드의 왼쪽 노드일 경우
        if (parent == grandpa->left)
        {
            uncle = grandpa->right;
            // 삼촌 노드가 블랙일 경우
            if (uncle->color == RBTREE_RED)
            {
                uncle->color = RBTREE_BLACK;
                parent->color = RBTREE_BLACK;
                grandpa->color = RBTREE_RED;
                z = grandpa;
            }
            // 꺽인 상태
            else
            {
                if (z == parent->right)
                {
                    z = parent;
                    left_rotate(t, z);
                }
                z->parent->parent->color = RBTREE_RED;
                z->parent->color = RBTREE_BLACK;
                right_rotate(t, z->parent->parent);
            }
        }
        else
        {
            uncle = grandpa->left;
            if (uncle->color == RBTREE_RED)
            {
                uncle->color = RBTREE_BLACK;
                parent->color = RBTREE_BLACK;
                grandpa->color = RBTREE_RED;
                z = grandpa;
            }
            else
            {
                if (z == parent->left)
                {
                    z = parent;
                    right_rotate(t, z);
                }
                z->parent->parent->color = RBTREE_RED;
                z->parent->color = RBTREE_BLACK;
                left_rotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK;
};
node_t *rbtree_insert(rbtree *t, const key_t key)
{
    // TODO: implement insert
    node_t *y = t->nil;
    node_t *x = t->root;
    node_t *z = new_node(key);

    while (x != t->nil)
    {
        y = x;
        // if (key == x->key)
        //     return;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == t->nil)
        t->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left = t->nil;
    z->right = t->nil;
    z->color = RBTREE_RED;
    insert_fix_up(t, z);
    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
    // TODO: implement find
    node_t *temp = t->root;
    while (temp != t->nil)
    {
        if (key > temp->key)
            temp = temp->right;
        else if (key < temp->key)
            temp = temp->left;
        else
            return temp;
    }
    return NULL;
}

node_t *rbtree_min(const rbtree *t)
{
    // TODO: implement find
    node_t *node = t->root;
    while (node->left != t->nil)
        node = node->left;
    return node;
}

node_t *rbtree_max(const rbtree *t)
{
    // TODO: implement find
    node_t *node = t->root;
    while (node->right != t->nil)
        node = node->right;
    return node;
}
node_t *find_successor(rbtree *t, node_t *z)
{
    while (z->left != t->nil)
        z = z->left;
    return z;
}
void erase_fix_up(rbtree *t, node_t *x)
{

    node_t *w; // x의 형제 노드
    // x가 루트이거나 x가 레드이면 while문을 종료한다.
    while (x != t->root && x->color == RBTREE_BLACK)
    {
        if (x == x->parent->left)
        {
            w = x->parent->right;
            // 경우1. x의 형제 노드가 레드일 때
            if (w->color == RBTREE_RED)
            {
                x->parent->color = RBTREE_RED;
                w->color = RBTREE_BLACK;
                left_rotate(t, x->parent);
                w = x->parent->right;
            }
            // 경우2. x의 형제의 왼쪽 자식, 오른쪽 자식이 둘 다 블랙일 때
            if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
            {
                w->color = RBTREE_RED;
                x = x->parent;
            }

            else
            {
                // 경우3. w는 블랙, w의 왼쪽 자식이 레드일 때
                if (w->left->color == RBTREE_RED)
                {
                    w->color = RBTREE_RED;
                    w->left->color = RBTREE_BLACK;
                    right_rotate(t, w);
                    w = x->parent->right;
                }
                // 경우4. w는 블랙, w의 오른쪽 자식이 레드일 때
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->right->color = RBTREE_BLACK;
                left_rotate(t, x->parent);
                x = t->root;
            }
        }
        else
        {
            w = x->parent->left;
            // 경우1. x의 형제 노드가 레드일 때
            if (w->color == RBTREE_RED)
            {
                x->parent->color = RBTREE_RED;
                w->color = RBTREE_BLACK;
                right_rotate(t, x->parent);
                w = x->parent->left;
            }
            // 경우2. x의 형제의 왼쪽 자식, 오른쪽 자식이 둘 다 블랙일 때
            if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK)
            {
                w->color = RBTREE_RED;
                x = x->parent;
            }

            else
            {
                // 경우3. w는 블랙, w의 오른쪽 자식이 레드일 때
                if (w->right->color == RBTREE_RED)
                {
                    w->color = RBTREE_RED;
                    w->right->color = RBTREE_BLACK;
                    left_rotate(t, w);
                    w = x->parent->right;
                }
                // 경우4. w는 블랙, w의 왼쪽 자식이 레드일 때
                w->color = x->parent->color;
                x->parent->color = RBTREE_BLACK;
                w->left->color = RBTREE_BLACK;
                right_rotate(t, x->parent);
                x = t->root;
            }
        }
    }
    x->color = RBTREE_BLACK;
}
int rbtree_erase(rbtree *t, node_t *z)
{
    // TODO: implement erase
    node_t *y; // 실제 삭제할 노드를 가르키는 포인터
    node_t *x;

    // 삭제할 노드 선택
    // 1. 삭제 노드의 자식 노드가 하나 또는 없는 경우일 때
    if (z->left == t->nil || z->right == t->nil)
        y = z;
    // 2. 삭제 노드의 자식 노드가 둘일 경우
    else
        y = find_successor(t, z->right);

    // 삭제할 노드의 자식노드 x는 nil 노드를 가르킬 수도 있음
    if (y->left != t->nil)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;

    // 삭제할 노드가 루트인 경우
    if (y->parent == t->nil)
        t->root = x;
    // 삭제할 노드가 부모의 왼쪽 자식인 경우
    else if (y->parent->left == y)
        y->parent->left = x;
    // 삭제할 노드가 부모의 오른쪽 자식인 경우
    else
        y->parent->right = x;

    // 실제로 삭제할 노드가 삭제 노드와 다른 경우
    if (y != z)
    {
        z->key = y->key;
        z->color = y->color;
    }
    // 삭제한 노드가 레드이면 RB트리 조건을 위반하지 않는다
    if (y->color == RBTREE_BLACK)
        erase_fix_up(t, x);
    free(y);
    return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
    // TODO: implement to_array
    return 0;
}

void print_tree(rbtree *t, node_t *node, int level)
{
    if (node == t->nil)
        return;
    print_tree(t, node->right, level + 1);
    for (int i = 0; i < level; i++)
    {
        printf("    ");
    }
    printf("%d:%d\n", node->key, node->color);
    print_tree(t, node->left, level + 1);
}
