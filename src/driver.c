#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>
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

int main(int argc, char *argv[])
{
    rbtree *t = new_rbtree();

    key_t a, b, c, d, e, f, g, h, i, j, k, l, m;

    a = 10;
    b = 20;
    c = 30;
    d = 100;
    e = 90;
    f = 40;
    g = 50;
    h = 60;
    i = 70;
    j = 80;
    k = 150;
    l = 110;
    m = 120;

    rbtree_insert(t, a);
    rbtree_insert(t, b);
    rbtree_insert(t, c);
    rbtree_insert(t, d);
    rbtree_insert(t, e);
    rbtree_insert(t, f);
    // rbtree_insert(t, g);
    // rbtree_insert(t, h);
    // rbtree_insert(t, i);
    // rbtree_insert(t, j);
    // rbtree_insert(t, k);
    // rbtree_insert(t, l);
    // rbtree_insert(t, m);
    node_t *root = t->root;
    print_tree(t, root, 0);
}