#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <graphviz/pathplan.h>
#include <graphviz/cgraph.h>
#include "tree.h"
#include "tools.h"
#include "dialog.h"
int str_chint(unsigned int* n1,int mode)
{
    int ke = 1,n2,f;
    char c;
    switch(mode)
    {
    case 1:
        printf("(1) Adding a new element\n"
           "(2) Deleting an element\n"
           "(3) Tree traversal\n"
           "(4) Searching for an item by key\n"
           "(5) Special element search\n"
           "(6) Formatted tree output \"in the form of a tree\"\n"
           "(7) Graphical tree output\n"
           "(8) Loading a tree from a text file\n"
           "(9) Test file\n"
           "(10) Additional task\n"
           "option:  ");
           break;
    case 2:
        printf("Enter the key: ");
        break;
    case 3:
        printf("Enter the key:(Enter 0 to output the entire tree) ");
        break;
    case 4:
        printf("Enter the len: ");
        break;
    case 5:
        printf("Enter the max element: ");
        break;
    }
    while (ke !=0)
    {
        ke = 0;
        f = scanf("%d",&n2);
        if (f == 0)
        {
            scanf("%*[^\n]");
            ke++;
            printf("Enter an integer: ");
        }
        else if (f == -1)
        {
            return -1;
        }
        else
        {
            scanf("%c",&c);
            if ((c == 10) && (n2 >= 0))
            {
                (*n1) = n2;
            }
            else if(n2 < 0)
            {
                printf("Enter a positive number!\n");
                ke++;
            }
            else
            {
                scanf("%*[^\n]");
                ke++;
                printf("Enter an integer: ");
            }
        }
    }
    return 1;
}
char * readline12(char rasd[])
{
    int k = 0,countch = 1, f = 0, d = 0;
    printf("%s",rasd);
    char* itog = (char*)malloc(sizeof(char)*11);
    char masd[11];
    scanf("%*[\n]");
    while (f == 0)
    {
        for (int i = 0; i < 11; i++)
        {
            masd[i] = 0;
        }
        d = scanf("%11[^\n]",masd);
        if (d == -1)
        {
            free(itog);
            return NULL;
        }
        else if(d == 0)
        {
            f = 1;
            k++;
        }
        else if(d == 1)
        {
            for (int i = 0;i < 11;i++)
            {
                if (masd[i] == 0)
                {
                    break;
                }
                itog[k] = masd[i];
                k++;
            }
        }
        countch++;
        itog = realloc(itog,sizeof(char)*countch*11);
    }
    itog = realloc(itog,sizeof(char) * k);
    itog[k-1] = '\0';
    return itog;
}
void delet_all(Node * root)
{
    if(root != NULL)
    {
        free(root->info);
        if (root->left != NULL)
        {
            delet_all(root->left);
        }
        if (root->right != NULL)
        {
            delet_all(root->right);
        }
        free(root);
    }
}
void output_ind(Node ** ind,unsigned int len)
{
    for (int i = 0;i < len;i++)
    {
        printf("%d:%s ",ind[i]->key,ind[i]->info);
    }
    printf("\n");
}
char *name_node(Node *elem)
{
    unsigned int len = strlen(elem->info),nD = 1;
    char *itog = (char *)calloc(len + 1,sizeof(char));
    strcpy(itog,elem->info);
    itog[len] = ':';
    if (elem->key != 0)
    {
        nD = floor(log10(abs(elem->key))) + 1;
    }
    itog = realloc(itog,sizeof(char)*(len + 2 + nD));
    snprintf(itog+(len + 1),nD + 1,"%d",elem->key);
    return itog;
}
void recur(Agraph_t *g,Node * elem,Agnode_t *n2)
{
    Agnode_t *n1;
    char * name = name_node(elem);
    n1 = agnode(g, name,1);
    if (n2 != NULL)
    {
        agedge(g, n2, n1, 0, 1);
    }
    if (elem->left != NULL)
    {
        recur(g,elem->left,n1);
    }
    if(elem->right != NULL)
    {
        recur(g,elem->right,n1);
    }
}
int graph(Tree * tree) 
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
    Agraph_t *g;
    GVC_t *gvc;
    gvc = gvContext();
    g = agopen("g",  Agdirected,0);
    recur(g,tree->root,NULL);
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "svg", "output.svg");
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
    return 0;
}
char * freadline12(FILE * file)
{
    int k = 0,countch = 1, f = 0, d = 0;
    char* itog = (char*)malloc(sizeof(char)*11);
    char masd[11];
    fscanf(file, "%*[\n]");
    while (f == 0)
    {
        for (int i = 0; i < 11; i++)
        {
            masd[i] = 0;
        }
        d = fscanf(file, "%11[^\n]",masd);
        if (d == -1)
        {
            free(itog);
            return NULL;
        }
        else if(d == 0)
        {
            f = 1;
            k++;
        }
        else if(d == 1)
        {
            for (int i = 0;i < 11;i++)
            {
                if (masd[i] == 0)
                {
                    break;
                }
                itog[k] = masd[i];
                k++;
            }
        }
        countch++;
        itog = realloc(itog,sizeof(char)*countch*11);
    }
    itog = realloc(itog,sizeof(char) * k);
    itog[k-1] = '\0';
    return itog;
}
Tree * generator(unsigned int len,unsigned int ** key)
{
    char * value = NULL;
    Tree* tree = (Tree *)calloc(1,sizeof(Tree));
    srand(time(NULL));
    unsigned len_i = 0,key_el = 0,j = 0;
    (*key) = (unsigned int*)calloc(len, sizeof(unsigned int));
    for(int i = 0;i < len;i++)
    {
        len_i = rand() % 10;
        value = (char*)calloc(len_i + 1,sizeof(char));
        for (int j = 0;j < len_i; j++)
        {
            value[j] = 65 + (rand() % 60);
        }
        key_el = rand() % UINT_MAX;
        if(j != len)
        {
            (*key)[j] = key_el;
        }
        add_elem(tree, key_el, value);
    }
    return tree;
}
void test_time()
{
    Tree * tree = NULL;
    char * value = NULL;
    FILE * file = fopen("test_5_1.txt","w");
    struct timespec start, end;
    unsigned int *key = 0,len_i = 0;
    double time = 0.0;
    for (int j = 0; j < 20; j++)
    {
        for (int p = 0;p < 10;p++)
        {
            tree = generator(50000 + 50000 * j,&key);
            for (int i = 0;i < 100;i++)
            {
                clock_gettime(CLOCK_REALTIME, &start);
                search_min(tree->root, &len_i);
                clock_gettime(CLOCK_REALTIME, &end);
                time += (1000000000*(end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec));
            }
            free(key);
            key = NULL;                
            delet_all(tree->root);
            free(tree);
        }
        time = time /10;
        printf("%f\n",time);
        fprintf(file,"%f\n",time);
        time = 0;
    }
    fclose(file);
}
void write_bin(FILE * file, unsigned int len)
{
    int elem = 0;
    unsigned int max_elem = 1;
    str_chint(&max_elem, 5);
    for (int i = 0;i < len;i++)
    {
        elem = rand() % max_elem;
        fwrite(&elem,sizeof(int),1,file);
    }
}
void add_task(FILE * file,Tree_add * tree)
{
    unsigned int len = 0, key = 0;
    fread(&len,sizeof(int),1,file);
    for (int i = 0;i < len;i++)
    {
        fread(&key,sizeof(int), 1, file);
        insert_elem(tree,key);
    }
}
void travel_f(Node_add *root,FILE * file)
{
    if (root->left != NULL)
    {
        travel_f(root->left,file);
    }
    fprintf(file,"%d:%d\n",root->key,root->amount);
    if (root->right != NULL)
    {
        travel_f(root->right,file);
    }
}
void insert_elem(Tree_add *tree,int key)
{
    Node_add * elem = (Node_add *)calloc(1,sizeof(Node_add)),*mem = NULL,*par = NULL;
    elem->amount = 1;
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
                if (mem->key == key)
                {
                    mem->amount++;
                    free(elem);
                    break;
                }
                mem = mem->right;
                if (mem == NULL)
                {
                    par->right = elem;
                }
            }
        }
    }
}
void delet_all_ad(Node_add * root)
{
    if(root != NULL)
    {
        if (root->left != NULL)
        {
            delet_all_ad(root->left);
        }
        if (root->right != NULL)
        {
            delet_all_ad(root->right);
        }
        free(root);
    }
}