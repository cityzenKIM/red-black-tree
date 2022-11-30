#include "rbtree.h"
#include <stdio.h>

// void print_tree(rbtree* t, node_t* node, int level) {
//     if (node == t->nil)
//         return;
//     print_tree(t, node->right, level + 1);
//     for (int i = 0; i < level; i++) {
//         printf("    ");
//     }
//     printf("%d:%d\n", node->key, node->color);
//     print_tree(t, node->left, level + 1);
// }
// int main(int argc, char* argv[]) {
    // rbtree* t = new_rbtree();
    // t->root = rbtree_insert(t, 8);
    // t->root = rbtree_insert(t, 1);
    // t->root = rbtree_insert(t, 11);
    // t->root = rbtree_insert(t, 6);
    // t->root = rbtree_insert(t, 15);
    // t->root = rbtree_insert(t, 17);
    // t -> root = rbtree_insert(t, 25);
    // t -> root = rbtree_insert(t, 22);
    // t -> root = rbtree_insert(t, 27);
    // t -> root = rbtree_insert(t, 13);
    // // key_t a, b, c, d, e, f, g, h, i, j, k, l, m;

    // // a = 10;
    // // b = 20;
    // // c = 30;
    // // d = 100;
    // // e = 90;
    // // f = 40;
    // // g = 50;
    // // h = 60;
    // // i = 70;
    // // j = 80;
    // // k = 150;
    // // l = 110;
    // // m = 120;

    // // rbtree_insert(t, a);
    // // rbtree_insert(t, b);
    // // rbtree_insert(t, c);
    // // rbtree_insert(t, d);
    // // rbtree_insert(t, e);
    // // rbtree_insert(t, f);
    // // rbtree_insert(t, g);
    // // rbtree_insert(t, h);
    // // rbtree_insert(t, i);
    // // rbtree_insert(t, j);
    // // rbtree_insert(t, k);
    // // rbtree_insert(t, l);
    // // rbtree_insert(t, m);
    // print_tree(t, t->root, 0);
    // node_t *x= rbtree_min(t);
    // printf("%d ", x->key);
    // x = rbtree_max(t);
    // printf("%d ", x->key);
    // // x = rbtree_find(t, 19);
    // // printf("%d",x->key);
    // // printf("\n");
    // key_t arr[6] = {0};
    // rbtree_to_array(t, arr, 6);
    // for (int i = 0; i < 6;i++)
    // {
    //     printf("%d ", arr[i]);
    // }
    // // x -> key = 15;
    // // rbtree_erase(t, x);
    // // print_tree(t, t->root, 0);
    // return 0;
// }