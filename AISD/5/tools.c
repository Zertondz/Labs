#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <graphviz/pathplan.h>
#include <graphviz/cgraph.h>
#include "graph.h"
#include "tools.h"
unsigned int search_hash(unsigned int x,unsigned int y,Graph * table,int *error);
unsigned long hash_prime(unsigned int msize);
unsigned int hash(unsigned int x,unsigned int msize);
unsigned int double_hash(unsigned int key,const unsigned int i,const unsigned msize);
unsigned int near_simp(unsigned int amount);
Graph* expend_table(Graph* table);
Graph *initialization_table(unsigned int msize);
int NOD(int a,int b);
int str_chint(unsigned int* n1,int mode)
{
    int ke = 1,n2,f;
    char c;
    switch(mode)
    {
    case 1:
        printf("(1) Add a vertex\n"
           "(2) Add an edge\n"
           "(3) Delete a given vertex\n"
           "(4) Delete a given edge\n"
           "(5) Graph traversal\n"
           "(6) Edit vertex data\n"
           "(7) Graphical tree output\n"
           "(8) Graph output in the form of adjacency lists\n"
           "(9) Find the shortest path between two vertices of the Graph\n"
           "(10) Modify the maze\n"
           "(11) Reading from a file\n"
           "(12) Generate a file\n"
           "(13) Display the path in the picture\n"
           "option:  ");
           break;
    case 2:
        printf("Enter the vertex type: (0 - cell, 1 - input, 2 - output)");
        break;
    case 3:
        printf("Enter the x: ");
        break;
    case 4:
        printf("Enter the y: ");
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
Vertex *create_ver(unsigned int x, unsigned int y, int type)
{
    Vertex *ver = (Vertex*)calloc(1,sizeof(Vertex));
    ver->x = x;
    ver->y = y;
    ver->type = type;
    return ver;
}
Edge *create_edge(unsigned int x_to, unsigned int y_to)
{
    Edge *edge = (Edge*)calloc(1,sizeof(Edge));
    edge->to_x = x_to;
    edge->to_y = y_to;
    return edge;
}
int check_coordinates(unsigned int x_f,unsigned int y_f,unsigned int x_to,unsigned int y_to)
{ 
    if((abs(x_f - x_to) == 1)&&(abs(y_f - y_to) == 1))
    {
        return 0;
    }
    if((abs(x_f - x_to) == 1)&&(abs(y_f - y_to) == 0))
    {
        return 1;
    }
    if((abs(x_f - x_to) == 0)&&(abs(y_f - y_to) == 1))
    {
        return 1;
    }
    return 0;
}
void delete_all(Graph * graph)
{
    Vertex * mem = NULL;
    Edge *par = NULL,*par_m = NULL;
    for (int i = 0; i < graph->msize; i++)
    {
        mem = graph->vertex_table[i];
        if(mem != NULL)
        {
            par = mem->edges;
            while(par != NULL)
            {
                par_m = par->next;
                free(par);
                par = par_m;
            }
            free(mem);
        }
    }
    free(graph->vertex_table);
}
unsigned int search_hash(unsigned int x,unsigned int y,Graph * table,int *error)
{
    unsigned int ind = 0,i = 0;
    while(i != table->msize)
    {
        ind = double_hash(x * y,i,table->msize);
        if (table->vertex_table[ind] == NULL)
        {
            (*error) = 0;
            return ind;
        }
        else
        {
            if((table->vertex_table[ind]->x == x)&&(table->vertex_table[ind]->y == y))
            {
                (*error) = -1;
                return ind;
            }
        }
        i++;
    }
    (*error) = -2;
    return 0;
}
int del_ed_corr(unsigned int x, unsigned int y, Graph * graph)
{
    int error = 0;
    unsigned int ind = 0;
    ind = search_hash_del(x - 1,y,graph,&error);
    if (error == -1)
    {
        del_edge(graph,graph->vertex_table[ind]->x,graph->vertex_table[ind]->y,create_edge(x,y));
    }
    ind = search_hash_del(x + 1,y,graph,&error);
    if (error == -1)
    {
        del_edge(graph,graph->vertex_table[ind]->x,graph->vertex_table[ind]->y,create_edge(x,y));
    }
    ind = search_hash_del(x,y - 1,graph,&error);
    if (error == -1)
    {
        del_edge(graph,graph->vertex_table[ind]->x,graph->vertex_table[ind]->y,create_edge(x,y));
    }
    ind = search_hash_del(x,y + 1,graph,&error);
    if (error == -1)
    {
        del_edge(graph,graph->vertex_table[ind]->x,graph->vertex_table[ind]->y,create_edge(x,y));
    }
    return 0;
}
unsigned int search_hash_del(unsigned int x,unsigned int y,Graph * table,int *error)
{
    unsigned int ind = 0,i = 0;
    while(i != table->msize)
    {
        ind = double_hash(x * y,i,table->msize);
        if (table->vertex_table[ind] != NULL)
        {
            if((table->vertex_table[ind]->x == x)&&(table->vertex_table[ind]->y == y))
            {
                (*error) = -1;
                return ind;
            }
        }
        i++;
    }
    (*error) = -2;
    return 0;
}
unsigned long hash_prime(unsigned int msize)
{
    long long p = msize;
    while (NOD(msize,p) != 1)
    {
        p++;
    }
    return p%msize;
}
unsigned int hash(unsigned int x,unsigned int msize) 
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % msize;
}
unsigned int double_hash(unsigned int key,const unsigned int i,const unsigned msize)
{
    unsigned int ind = (hash(key,msize) + i * hash_prime(msize)) % msize;
    return ind;
}
unsigned int near_simp(unsigned int amount)
{
    unsigned int flag = 1;
    amount++;
    while(flag == 1)
    {
        flag = 0;
        for (unsigned int i = 2;i < ((unsigned int)sqrt(amount) + 1);i++)
        {
            if((amount % i) == 0)
            {
                amount++;
                flag = 1;
                break;
            }
        }
    }
    return amount;
}
Graph *initialization_table(unsigned int msize)
{
    Graph * table = (Graph *)calloc(1,sizeof(Graph));
    table->msize = msize;
    table->vertex_table = (Vertex **)calloc(msize,sizeof(Vertex*));
    return table;
}
Graph* expend_table(Graph* table)
{
    int error = 0;
    unsigned int ind = 0,x = 0, y = 0;
    Graph * copy_table = initialization_table(near_simp(table->msize));
    copy_table->csize = table->csize;
    for (unsigned int i = 0; i < table->msize; i++)
    {
        if(table->vertex_table[i] != NULL)
        {
            x = table->vertex_table[i]->x;
            y = table->vertex_table[i]->y;
            ind = search_hash(x,y,copy_table,&error);
            copy_table->vertex_table[ind] = table->vertex_table[i];
        }
    }
    free(table->vertex_table);
    free(table);
    return copy_table;
}
int NOD(int a,int b)
{
    while((a != 0)&&(b != 0))
    {
        if (a > b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }
    }
    return (a + b);
}
char *name_node(Vertex *ver)
{
    unsigned int nD_x = 1, nD_y = 1;
    if (ver->x != 0)
    {
        nD_x = floor(log10(abs(ver->x))) + 1;
    }
    if (ver->y != 0)
    {
        nD_y = floor(log10(abs(ver->y))) + 1;
    }
    char *itog = (char *)calloc(5 + nD_x + nD_y,sizeof(char));
    snprintf(itog,5 + nD_x + nD_y,"[%d, %d]",ver->x, ver->y);
    return itog;
}
void recur(Agraph_t *g,Vertex * ver,Agnode_t *n2, Graph *graph)
{
    unsigned int ind = 0;
    int error = 0;
    Agnode_t *n1;
    char * name = name_node(ver);
    Edge * mem = NULL;
    n1 = agnode(g, name, 1);
    agsafeset(n1, "shape", "square", "");
    if(ver->type == 1)
    {
        agsafeset(n1, "color", "red", "");
    }
    else if(ver->type)
    {
        agsafeset(n1, "color", "blue", "");
    }
    mem = ver->edges;
    if (n2 != NULL)
    {
        agedge(g, n2, n1, 0, 1);
    }
    if(ver->service == 0)
    {
        ver->service = 1;  
        while(mem != NULL)
        {
            ind = search_hash_del(mem->to_x,mem->to_y,graph, &error);
            recur(g,graph->vertex_table[ind], n1, graph);
            mem = mem->next;
        }
    }     
    free(name);
}
void serv(Agraph_t *g,Graph *graph)
{
    for (int i = 0; i < graph->msize; i++)
    {
        if(graph->vertex_table[i] != NULL)
        {
            if(graph->vertex_table[i]->service == 0)
            {
                recur(g,graph->vertex_table[i],NULL,graph);
            }
        }
    }
    for (int i = 0; i < graph->msize; i++)
    {
        if(graph->vertex_table[i] != NULL)
        {
            graph->vertex_table[i]->service = 0;
        }
    }
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
int graphvi(Graph *graph) 
{
    if (graph == NULL)
    {
        printf("The tree is empty\n");
        return 1;
    }
    if (graph->csize == 0)
    {
        printf("The tree is empty\n");
        return 1;
    }
    Agraph_t *g;
    GVC_t *gvc;
    gvc = gvContext();
    g = agopen("g",  Agdirected, 0);
    serv(g, graph);
    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "svg", "output.svg");
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
    return 0;
}