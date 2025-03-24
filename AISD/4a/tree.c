#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "tools.h"
#include "dialog.h"
int add_elem(Tree* tree, unsigned int key, char * value)
{
    Node * elem = (Node *)calloc(1,sizeof(Node)),*mem = NULL,*par = NULL;
    elem->info = value;
    elem->key = key;
    if (tree->root== NULL)
    {
        tree->root = elem;
    }
    else
    {
        mem = tree->root;
        while(mem != NULL)
        {
            par = mem;
            if(mem->key > key)
            {
                mem = mem->left;
                if (mem == NULL)
                {
                    par->left = elem;
                }
            }
            else
            {
                mem = mem->right;
                if (mem == NULL)
                {
                    par->right = elem;
                }
            }
        }
    }
    return 0;
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
    if (root != NULL)
    {
        if (is_left == 1)
        {
            printf("%s└──%d:%s\n",prefix,root->key,root->info);
        }
        else
        {
            printf("%s├──%d:%s\n",prefix,root->key,root->info);
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
    if (root->left != NULL)
    {
        travel(root->left,key);
    }
    if ((root->key<= key)||(key == 0))
    {
        printf("%d:%s ",root->key,root->info);
    }
    else
    {
        return 0;
    }
    if (root->right != NULL)
    {
        travel(root->right,key);
    }
    return 0;
}
int travel_count(Node *root,unsigned int * amount)
{
    if (root->left != NULL)
    {
        travel_count(root->left,amount);
    }
    (*amount)++;
    if (root->right != NULL)
    {
        travel_count(root->right,amount);
    }
    return 0;
}
Node ** search(Node *root, unsigned int key,unsigned int * len)
{
    Node *mem = NULL;
    Node ** ind = (Node **)calloc(1,sizeof(Node *));
    unsigned int j = 0;
    mem = root;
    while(mem != NULL)
    {
        if(mem->key > key)
        {
            mem = mem->left;
            if (mem == NULL)
            {
                if(j == 0)
                {
                    free(ind);
                    return NULL;
                }
                else
                {
                    ind = realloc(ind,sizeof(Node*)*j);
                    (*len) = j;
                    return ind;
                }
            }
        }
        else
        {
            
            if(mem->key == key)
            {
                ind[j] = mem;
                j++;
                ind = realloc(ind,sizeof(Node*)*(j + 1));
            }
            mem = mem->right;
            if (mem == NULL)
            {
                if(j == 0)
                {
                    free(ind);
                    return NULL;
                }
                else
                {
                    (*len) = j;
                    ind = realloc(ind,sizeof(Node*)*j);
                    return ind;
                }
            }
        }
    }
    (*len) = j;
    return ind;
}
Node ** search_min(Node *root, unsigned int * len)
{
    Node *mem = NULL;
    Node ** ind = NULL;
    unsigned int key = 0;
    mem = root;
    while(mem != NULL)
    {
        if(mem->left == 0)
        {
            key = mem->key;
        }
        mem = mem->left;
    }
    ind = search(root,key,len);
    return ind;
}
Tree * read_f_file(int * error)
{
    FILE * file = NULL;
    Tree * tree = NULL;
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
        add_elem(tree,key,value);
    }
    fclose(file);
    return tree;
}
int del_elem(Tree * tree, unsigned int key)
{
    int flag = 0;
    Node *mem = NULL,*par = NULL,*mem_right = NULL,*mem_left = NULL,*par_mem = NULL;
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
    if(par == NULL)
    {
        if((mem->left == NULL)&&(mem->right != NULL))
        {
            tree->root = mem->right;
            free(mem->info);
            free(mem);
        }
        else if((mem->right == NULL)&&(mem->left != NULL))
        {
            tree->root = mem->left;
            free(mem->info);
            free(mem);
        }
        else if((mem->right == NULL)&&(mem->left == NULL))
        {
            tree->root = NULL;
            free(mem->info);
            free(mem);
        }
        else
        {
            mem = mem->right;
            while(mem->left != NULL)
            {
                par = mem;
                mem = mem->left;
            }
            mem_left = tree->root->left;
            mem_right = tree->root->right;
            free(tree->root->info);
            free(tree->root);
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
    else
    {
        if((mem->left == NULL)&&(mem->right != NULL))
        {
            if (flag == 1)
            {
                par->left = mem->right;
            }
            else
            {
                par->right = mem->right;
            }
            free(mem->info);
            free(mem);
        }
        else if((mem->right == NULL)&&(mem->left != NULL))
        {
            if (flag == 1)
            {
                par->left = mem->left;
            }
            else
            {
                par->right = mem->left;
            }
            free(mem->info);
            free(mem);
        }
        else if((mem->right == NULL)&&(mem->left == NULL))
        {
            if (flag == 1)
            {
                par->left = NULL;
            }
            else
            {
                par->right = NULL;
            }
            free(mem->info);
            free(mem);
        }
        else
        {      
            par_mem = par;      
            mem_left = mem->left;
            mem_right = mem->right;            
            free(mem->info);
            free(mem);
            mem = mem_right;
            while(mem->left != NULL)
            {
                par_mem = mem;
                mem = mem->left;
            }
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
    }
    return 0;
}