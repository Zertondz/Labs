#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "tools.h"
#include "dialog.h"
int free_elem(Node * elem, unsigned int rel)
{
    Info *mem = NULL,*par = NULL;
    mem = elem->info;
    for(int i = 1;mem != NULL;i++)
    {
        if(i == rel)
        {
            if(par == NULL)
            {
                elem->info = mem->next;
            }
            else if (mem->next == NULL)
            {
                par->next = NULL;
            }
            else
            {
                par->next = mem->next;
            }
            free(mem->value);
            free(mem);
            break;
        }
        else if(i > rel)
        {
            return -1;
        }
        else
        {
            par = mem;
            mem = mem->next;
        }
    }
    if(elem->info == NULL)
    {
        free(elem);
        return 1;
    }
    return 0;
}
Node * create_elem(unsigned int key,char * value)
{
    Node *elem = (Node*)calloc(1,sizeof(Node));
    elem->info = (Info*)calloc(1,sizeof(Info));
    elem->key = key;
    elem->info->value = value;
    elem->height = 1;
    return elem;
}
Node * recur_balanced(Node * node,unsigned int key)
{
    if (node == NULL)
    {
        return NULL;
    }
    if(node->key > key)
    {
        node->left = recur_balanced(node->left, key);
    }
    else
    {
        node->right = recur_balanced(node->right, key);
    }
    return balance(node);
}
void recur_fix(Node * mem,Node * par, Tree * tree, unsigned int rel)
{
    Node * mem_left = NULL;
    Node * mem_right = NULL;
    if(mem->left != NULL)
    {
        recur_fix(mem->left,mem,tree,rel);
        if (mem->left != NULL)
        {
            mem->left = balance(mem->left);
        }
    }
    else
    {
        mem_left = tree->root->left;
        mem_right = tree->root->right;
        free_elem(tree->root,rel);
        if(par != NULL)
        {
            par->left = mem->right;
            mem->right = mem_right;
            mem->left = mem_left;
            tree->root = mem;
        }
        else
        {
            tree->root = mem;
            tree->root->left = mem_left;
        }
    }
}
Node *add_elem(Node *node, Node *elem)
{
    Info * mem = NULL;
    if (node == NULL)
    {
        return elem;
    }
    else if(node->key == elem->key)
    {
        mem = node->info;
        while(mem->next != NULL)
        {
            mem = mem->next;
        }
        mem->next = elem->info;
        free(elem);
        return node;
    }
    if(node->key > elem->key)
    {
        node->left = add_elem(node->left, elem);
    }
    else
    {
        node->right = add_elem(node->right, elem);
    }
    return balance(node);
}
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
void output_tree_s(Node * root,char * prefix,int is_left)
{
    Info *mem = NULL;
    if (root != NULL)
    {
        if (is_left == 1)
        {
            printf("%s└──%d:",prefix,root->key);
            mem = root->info;
            while(mem != NULL)
            {
                printf(" %s",mem->value);
                mem = mem->next;
            }
            printf("\n");
        }
        else
        {
            printf("%s├──%d:",prefix,root->key);
            mem = root->info;
            while(mem != NULL)
            {
                printf(" %s",mem->value);
                mem = mem->next;
            }
            printf("\n");
        }
        if(is_left == 0)
        {
            prefix = concat(prefix,"│   ");
        }
        else
        {
            prefix = concat(prefix,"    ");
        }
        output_tree_s(root->right,prefix,0);
        output_tree_s(root->left,prefix,1);
        free(prefix);
    }
}
int travel(Node *root,unsigned int key)
{   
    Info * mem = NULL;
    if (root->right != NULL)
    {
        travel(root->right,key);
    }
    if (((root->key>= key) && (root->key < (key*10)))||(key == 0))
    {
        mem = root->info;
        while(mem != NULL)
        {
            //printf("%d:%s ",root->key,mem->value);
            mem = mem->next;
        }
    }
    if (root->left != NULL)
    {
        travel(root->left,key);
    }
    return 0;
}
int travel_min_elem(Node *root,unsigned int * key,unsigned int * amount)
{
    if (root->left != NULL)
    {
        travel_min_elem(root->left, key, amount);
    }
    if((*amount == 0)&&(root->key > *key))
    {
        (*key) = root->key;
        (*amount)++;
    }
    if (root->right != NULL)
    {
        travel_min_elem(root->right, key, amount);
    }
    return 0;
}
Node *search(Node *root, unsigned int key)
{
    Node *mem = NULL;
    mem = root;
    while(mem != NULL)
    {
        if(mem->key > key)
        {
            mem = mem->left;
            if (mem == NULL)
            {
                return NULL;
            }
        }
        else
        {
            
            if(mem->key == key)
            {
                return mem;
            }
            mem = mem->right;
            if (mem == NULL)
            {
                return NULL;
            }
        }
    }
    return NULL;
}
Node *search_min(Node *root, unsigned int * key_it)
{
    unsigned int amount = 0;
    Node *ind = NULL;
    travel_min_elem(root,key_it,&amount);
    ind = search(root,*key_it);
    return ind;
}
Tree * read_f_file(int * error)
{
    FILE * file = NULL;
    Tree * tree = NULL;
    Node * elem = NULL;
    unsigned int len = 0,key = 0;
    char * name = readline12("Enter the file name: "),*value = NULL;
    if (name != NULL)
    {
        file = fopen(name,"r");
    }
    else
    {
        (*error) = -1;
        return NULL;
    }
    free(name);
    if (file == NULL)
    {
        return NULL;
    }
    fscanf(file,"%d",&len);
    if (len != 0)
    {
        tree = (Tree *)calloc(1,sizeof(Tree));
    }
    else
    {
        printf("File if empty\n");
        fclose(file);
        return NULL;
    }
    for (int i = 0;i < len;i++)
    {
        if (fscanf(file,"%d",&key) != 1)
        {
            printf("ERROR!!!\n");
            fclose(file);
            return tree;
        }
        value = freadline12(file);
        printf("%d -- %s\n",key,value);
        if (value == NULL)
        {
            printf("ERROR!!!\n");
            fclose(file);
            return tree;
        }
        elem = create_elem(key,value);
        tree->root = add_elem(tree->root, elem);
    }
    fclose(file);
    return tree;
}
int criteria_del(Node *node)
{
    return node->info->next == NULL;
}
int criteria_exist(Node *elem, unsigned int rel)
{
    Info *mem = NULL;
    mem = elem->info;
    for(int i = 1; mem != NULL; i++)
    {
        if(i == rel)
        {
            return 1;
        }
        else if(i > rel)
        {
            return -1;
        }
        else
        {
            mem = mem->next;
        }
    }
    return -1;
}
int del_elem(Tree * tree, unsigned int key, unsigned int rel)
{
    int flag = 0;
    Node *mem = NULL,*par = NULL,*mem_right = NULL,*mem_left = NULL,*par_mem = NULL;
    unsigned int key_rec = 0;
    mem = tree->root;
    while(mem != NULL)
    {
        if(mem->key > key)
        {
            par = mem;
            mem = mem->left;
            flag = 1;
            if (mem == NULL)
            {
                return -1;
            }
        }
        else
        {
            if(mem->key == key)
            {
                break;
            }
            par = mem;
            mem = mem->right;
            flag = 0;
            if (mem == NULL)
            {
                return -1;
            }
        }
    }        
    if (criteria_exist(mem,rel) == -1)
    {
        return -1;
    }
    if(par == NULL)
    {

        if((mem->left == NULL)&&(mem->right != NULL))
        {
            if (criteria_del(mem))
            {
                tree->root = mem->right;
            }
            free_elem(mem,rel);
        }
        else if((mem->right == NULL)&&(mem->left != NULL))
        {
            if (criteria_del(mem))
            {
                tree->root = mem->left;
            }
            free_elem(mem,rel);
        }
        else if((mem->right == NULL)&&(mem->left == NULL))
        {
            if (criteria_del(mem))
            {
                tree->root = NULL;
            }
            free_elem(mem,rel);
        }
        else
        {
            if (criteria_del(mem))
            {
                mem = mem->right;
                recur_fix(mem,NULL,tree,rel);
                tree->root = balance(tree->root);
            }
            else
            {
                free_elem(mem,rel);
            }
        }
    }
    else
    {
        key_rec = mem->key;
        if((mem->left == NULL)&&(mem->right != NULL))
        {
            if(criteria_del(mem))
            {
                if (flag == 1)
                {
                    par->left = mem->right;
                }
                else
                {
                    par->right = mem->right;
                }
            }
            free_elem(mem,rel);
        }
        else if((mem->right == NULL)&&(mem->left != NULL))
        {
            if(criteria_del(mem))
            {
                if (flag == 1)
                {
                    par->left = mem->left;
                }
                else
                {
                    par->right = mem->left;
                }
            }
            free_elem(mem,rel);
        }
        else if((mem->right == NULL)&&(mem->left == NULL))
        {
            if(criteria_del(mem))
            {
                if (flag == 1)
                {
                    par->left = NULL;
                }
                else
                {
                    par->right = NULL;
                }
            }
            free_elem(mem,rel);
        }
        else
        {   
            if(criteria_del(mem))
            {   
                par_mem = par;      
                mem_left = mem->left;
                mem_right = mem->right;            
                free_elem(mem,rel);
                mem = mem_right;
                while(mem->left != NULL)
                {
                    par_mem = mem;
                    mem = mem->left;
                }
                key_rec = mem->key;
                if (par == par_mem)
                {
                    mem->left = mem_left;
                    if (flag == 1)
                    {
                        par_mem->left = mem;
                    }
                    else
                    {
                        par_mem->right = mem;
                    }
                }
                else
                {
                    par_mem->left = mem->right;
                    mem->right = mem_right;
                    mem->left = mem_left;
                    if (flag == 1)
                    {
                        par->left = mem;
                    }
                    else
                    {
                        par->right = mem;
                    }
                    par = mem;
                }
            }
            else
            {
                free_elem(mem,rel);
            }
        }
        tree->root = recur_balanced(tree->root,key_rec);
    }
    return 0;
}
