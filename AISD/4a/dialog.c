#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
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
    add_elem(tree, key, value);
    return 0;
}
int dial_travel(Tree * tree)
{
    unsigned int key = 0;
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
    if (str_chint(&key,3) == -1)
    {
        delet_all(tree->root);
        free(tree);
        return -1;
    }
    travel(tree->root,key);
    printf("\n");
    return 0;
}
int dial_search(Tree * tree)
{
    unsigned int key = 0,len = 0;
    Node ** ind = NULL;
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
    ind = search(tree->root, key, &len);
    if (len != 0)
    {
        output_ind(ind, len);
        free(ind);
    }
    else
    {
        printf("The element was not found!!!\n");
    }
    return 0;
}
int dial_search_min(Tree * tree)
{
    unsigned int len = 0;
    Node ** ind = NULL;
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
    ind = search_min(tree->root, &len);
    output_ind(ind, len);
    free(ind);
    return 0;
}
int dial_del_elem(Tree * tree)
{
    int error = 0;
    unsigned int key = 0;
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
    error = del_elem(tree, key);
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
int dial_bin()
{
    srand(time(NULL));
    char * name = readline12("Enter file name:");
    Tree_add * tree = NULL;
    unsigned int amount = 0; 
    if (name == NULL)
    {
        return -1;
    }    
    str_chint(&amount,4);
    tree = (Tree_add*)calloc(1,sizeof(Tree_add));
    FILE * file = fopen(name,"wb"),*file_res = NULL;
    fwrite(&amount,sizeof(int),1,file);
    write_bin(file,amount);
    fclose(file);
    file = fopen(name,"rb");
    add_task(file,tree);
    free(name);
    name = readline12("Enter file name:");
    file_res = fopen(name,"w");
    travel_f(tree->root,file_res);
    fclose(file);
    fclose(file_res);
    delet_all_ad(tree->root);
    free(tree);;
    free(name);
    return 0;
}