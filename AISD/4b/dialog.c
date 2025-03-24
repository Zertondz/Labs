#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include "tree.h"
#include "tools.h"
#include "dialog.h"
int dial_add_el(Tree * tree)
{
    unsigned int key = 0;
    char * value = NULL;
    if (str_chint(&key,2) == -1)
    {
        delet_all(tree->root);
        free(tree);
        return -1;
    }
    value = readline12(("Enter a value: "));
    if (value == NULL)
    {
        delet_all(tree->root);
        free(tree);
        return -1;
    }
    tree->root = add_elem(tree->root,create_elem(key,value));
    return 0;
}
int dial_travel(Tree * tree)
{
    unsigned int key_num = 0, key = 1;
    if (tree == NULL)
    {
        printf("The tree is empty\n");
        return 0;
    }
    if (tree->root == NULL)
    {
        printf("The tree is empty\n");
        return 0;
    }
    if (str_chint(&key_num,3) == -1)
    {
        delet_all(tree->root);
        free(tree);
        return -1;
    }
    if (key_num != 1)
    {
        key = pow(10,key_num - 1);
    }
    else if (key_num == 0)
    {
        key = 0;
    }
    travel(tree->root,key);
    printf("\n");
    return 0;
}
int dial_search(Tree * tree)
{
    unsigned int key = 0;
    Node *ind = NULL;
    if (tree == NULL)
    {
        printf("The tree is empty\n");
        return 0;
    }
    if (tree->root == NULL)
    {
        printf("The tree is empty\n");
        return 0;
    }
    if (str_chint(&key,2) == -1)
    {
        delet_all(tree->root);
        free(tree);
        return -1;
    }
    ind = search(tree->root, key);
    if (ind != NULL)
    {
        output_ind(ind->info, key);
    }
    else
    {
        printf("The element was not found!!!\n");
    }
    return 0;
}
int dial_search_min(Tree * tree)
{
    unsigned int key = 0, key_it = 0;
    Node * ind = NULL;
    if (tree == NULL)
    {
        printf("The tree is empty\n");
        return 0;
    }
    if (tree->root == NULL)
    {
        printf("The tree is empty\n");
        return 0;
    }
    if (str_chint(&key,2) == -1)
    {
        delet_all(tree->root);
        free(tree);
        return -1;
    }
    key_it = key;
    ind = search_min(tree->root, &key_it);
    if (ind != NULL)
    {
        output_ind(ind->info, key_it);
    }
    else
    {
        printf("The element was not found!!!\n");
    }
    return 0;
}
int dial_del_elem(Tree * tree)
{
    int error = 0;
    unsigned int key = 0,rel = 0;
    if (tree == NULL)
    {
        printf("The tree is empty\n");
        return 0;
    }
    if (tree->root == NULL)
    {
        printf("The tree is empty\n");
        return 0;
    }
    if (str_chint(&key,2) == -1)
    {
        delet_all(tree->root);
        free(tree);
        return -1;
    }
    if (str_chint(&rel,6) == -1)
    {
        delet_all(tree->root);
        free(tree);
        return -1;
    }
    error = del_elem(tree, key, rel);
    if (error == -1)
    {
        printf("The element was not found!!!\n");
    }
    return 0;
}
int dial_output(Tree * tree)
{
    if (tree == NULL)
    {
        printf("The tree is empty\n");
        return 1;
    }
    if (tree->root == NULL)
    {
        printf("The tree is empty\n");
        return 1;
    }
    output_tree_s(tree->root,"",0);
    return 0;
}
Tree * dial_add_task(Tree * tree)
{
    int error = 0;
    if (tree == NULL)
    {
        tree = (Tree *)calloc(1,sizeof(Tree));
    }
    read_f_file_d(tree,&error);
    if (error == -1)
    {
        delet_all(tree->root);
        free(tree);
        return NULL;
    }
    output_tree_s(tree->root,"",0);
    return tree;
}