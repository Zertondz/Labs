#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "tools.h"
#include "dialoc.h"
int add_ver(Graph ** graph,Vertex *vertex)
{
    unsigned int ind = 0;
    int error = 0;
    if ((*graph)->csize == (*graph)->msize)
    {
        (*graph) = expend_table((*graph));
    }
    ind = search_hash(vertex->x, vertex->y, (*graph), &error);
    if (error == 0)
    {
        (*graph)->vertex_table[ind] = vertex;
        (*graph)->csize++;
    }
    else
    {
        free(vertex->edges);
        free(vertex);
        return -1;
    }
    return 0;
}
int add_edge(Graph * graph,unsigned int from_x,unsigned int from_y,Edge *edge)
{
    unsigned int ind_f = 0, ind_to = 0;
    int error_f = 0,error_to = 0, j = 0;
    Edge * mem = NULL,*par = NULL;
    ind_f = search_hash_del(from_x, from_y, graph, &error_f);
    if (error_f != -1)
    {
        free(edge);
        return -1;
    }
    if(graph->vertex_table[ind_f]->type == 2)
    {
        free(edge);
        return -4;
    }
    ind_to = search_hash_del(edge->to_x, edge->to_y, graph, &error_to);
    if (error_to != -1)
    {
        free(edge);
        return -1;
    }
    if(graph->vertex_table[ind_to]->type == 1)
    {
        free(edge);
        return -4;
    }
    mem = graph->vertex_table[ind_f]->edges;
    par = mem;
    while (par != NULL)
    {
        j++;
        if(j == 4)
        {
            free(edge);
            return -2;
        }
        par = par->next;
    }
    par = NULL;
    while(mem != NULL)
    {
        par = mem;
        if((mem->to_x == edge->to_x)&&(mem->to_y == edge->to_y))
        {
            free(edge);
            return -3;
        }
        mem = mem->next;
    }
    if (par == NULL)
    {
        graph->vertex_table[ind_f]->edges = edge;
    }
    else
    {
        par->next = edge;
    }
    return 0;
}
int del_ver(unsigned int x,unsigned int y,Graph *graph)
{
    int error = 0;
    unsigned int ind = 0;
    Edge *par = NULL, * par_m = NULL;
    Vertex * mem = NULL;
    ind = search_hash_del(x, y, graph,&error);
    if(error != -1)
    {
        return -1;
    }
    del_ed_corr(x,y,graph);
    mem = graph->vertex_table[ind];
    par = mem->edges;
    while(par != NULL)
    {
        par_m = par->next;
        free(par);
        par = par_m;
    }
    free(mem);
    graph->vertex_table[ind] = NULL;
    graph->csize--;
    return 0;
}
int del_edge(Graph * graph,unsigned int from_x,unsigned int from_y,Edge *edge)
{
    unsigned int ind_f = 0;
    int error_f = 0,error_to = 0;
    Edge * mem = NULL,*par = NULL;
    ind_f = search_hash_del(from_x, from_y, graph, &error_f);
    if (error_f != -1)
    {
        free(edge);
        return -1;
    }    
    if (graph->vertex_table[ind_f]->edges == NULL)
    {
        free(edge);
        return -2;
    }
    search_hash_del(edge->to_x, edge->to_y, graph, &error_to);
    if (error_to != -1)
    {
        free(edge);
        return -1;
    }
    mem = graph->vertex_table[ind_f]->edges;
    while(mem != NULL)
    {
        if((mem->to_x == edge->to_x)&&(mem->to_y == edge->to_y))
        {
            if (par == NULL)
            {
                graph->vertex_table[ind_f]->edges = graph->vertex_table[ind_f]->edges->next;
            }
            else
            {
                par->next = mem->next;
            }
            free(mem);
            free(edge);
            return 0;
        }
        par = mem;
        mem = mem->next;
    }   
    return -2;
}
void change_ver(Graph *graph,unsigned int ind,unsigned int x,unsigned int y,unsigned int type)
{
    Edge *par = NULL, * par_m = NULL;
    Vertex * mem = NULL;
    int error = 0;
    mem = graph->vertex_table[ind];
    if ((mem->x != x)||(mem->y != y))
    {
        del_ed_corr(mem->x, mem->y, graph);        
        par = mem->edges;
        while(par != NULL)
        {
            par_m = par->next;
            free(par);
            par = par_m;
        }
        free(mem);
        graph->csize--;
        graph->vertex_table[ind] = NULL;
        mem = create_ver(x,y,type);
        graph->vertex_table[search_hash(x,y,graph,&error)] = mem;
        graph->csize++;
    }
    else
    {
        par = mem->edges;
        while(par != NULL)
        {
            par_m = par->next;
            free(par);
            par = par_m;
        }
        mem->edges = NULL;
        mem->x = x;
        mem->y = y;
        mem->type = type;
    }
}
int *sh_path(Graph *graph, unsigned int x_f, unsigned int y_f, unsigned int x_to, unsigned int y_to, int * error)
{
    int *dist = NULL, *from = NULL;
    int error_v = 0;
    unsigned int ind_f = 0, a = 0, b = 0, ind_to = 0;
    Edge *par = NULL;   
    Vertex * mem = NULL;
    ind_f = search_hash_del(x_f,y_f,graph,error);
    printf("++%d\n",*error);
    if((*error) != -1)
    {
        (*error) = -1;
        return NULL;
    }
    if(graph->vertex_table[ind_f]->type != 1)
    {
        (*error) = -1;
        return NULL;
    }
    ind_to = search_hash_del(x_to,y_to,graph,error);
    printf("++%d\n",*error);
    if((*error) != -1)
    {
        (*error) = -1;
        return NULL;
    }
    if(graph->vertex_table[ind_to]->type != 2)
    {
        (*error) = -1;
        return NULL;
    }
    printf("plfd\n");
    dist = (int*)malloc(graph->msize*sizeof(int));
    from = (int*)malloc(graph->msize*sizeof(int));
    for (int i = 0; i < graph->msize;i++)
    {
        dist[i] = 1e9;
        from[i] = -1;
    }
    dist[ind_f] = 0;
    for(int i = 0; i < graph->msize - 1; i++)
    {
        for(int j = 0; j < graph->msize; j++)
        {
            mem = graph->vertex_table[j];
            if(mem != NULL)
            {
                par = mem->edges;
                while(par != NULL)
                {
                    a = search_hash_del(mem->x,mem->y,graph,&error_v);
                    b = search_hash_del(par->to_x,par->to_y,graph,&error_v);
                    if((dist[a] != 1e9)&&(dist[b] > (dist[a] + 1)))
                    {
                        dist[b] = dist[a] + 1;
                        from[b] = a;
                    }
                    par = par->next;
                }
            }
        }
    }
    free(dist);
    return from;
}
void output(Graph * graph)
{
    Edge * mem = NULL;
    for(int i = 0;i < graph->msize;i++)
    {
        if (graph->vertex_table[i] != NULL)
        {
            printf("%d)[%d, %d]^%d:",i,graph->vertex_table[i]->x,graph->vertex_table[i]->y,graph->vertex_table[i]->type);
            mem = graph->vertex_table[i]->edges;
            while(mem != NULL)
            {
                printf("{%d, %d}->{%d, %d}",graph->vertex_table[i]->x,graph->vertex_table[i]->y,mem->to_x,mem->to_y);
                mem = mem->next;
            }
            printf("\n");
        }
    }
}
void recur_trav(Vertex * ver, Graph *graph)
{
    unsigned int ind = 0;
    int error = 0;
    Edge * mem = NULL;
    mem = ver->edges;
    ver->service = 1;
    while(mem != NULL)
    {
        ind = search_hash_del(mem->to_x,mem->to_y,graph, &error);
        if(graph->vertex_table[ind]->service == 0)
        {
            recur_trav(graph->vertex_table[ind],graph);
        }
        mem = mem->next;
    }
    ver->service = 2;
    if ((ver->type == 2)&&(ver->service == 2))
    {
        printf("{%d, %d} ",ver->x, ver->y);
    }
}
void travelsal(Graph *graph,unsigned int x, unsigned int y)
{
    for (int i = 0; i < graph->msize; i++)
    {
        if(graph->vertex_table[i] != NULL)
        {
            if((graph->vertex_table[i]->x == x)&&(graph->vertex_table[i]->y == y))
            {
                recur_trav(graph->vertex_table[i], graph);
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
void check_cycle(Graph * graph,Vertex * ver, int * path, int size)
{
    int error = 0;
    unsigned int ind = 0, flag = 0;
    int *path_c = calloc(size + 1, sizeof(int));
    Edge *mem = ver->edges;
    for(int i = 0;i < size; i++)
    {
        path_c[i] = path[i];
    }
    while(mem != NULL)
    {
        ind = search_hash_del(mem->to_x, mem->to_y, graph, &error);
        for(int i = 0; i < size; i++)
        {
            if(ind == path_c[i])
            {
                printf("{%d,%d},{%d,%d}\n",ver->x,ver->y,graph->vertex_table[ind]->x,graph->vertex_table[ind]->y);
                del_edge(graph, ver->x, ver->y, create_edge(graph->vertex_table[ind]->x, graph->vertex_table[ind]->y));
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            break;
        }
        path_c[size] = ind;
        check_cycle(graph, graph->vertex_table[ind], path_c, size + 1);
        mem = mem->next;
    }
    free(path_c);
}
void recur_mod(Graph *graph, Vertex * ver)
{
    int error = 0;
    int * path = 0;
    unsigned int ind = 0;
    Edge *mem = ver->edges;
    while(mem != NULL)
    {
        path = calloc(1,sizeof(int));
        ind = search_hash_del(mem->to_x, mem->to_y, graph, &error);
        ver->service = 1;
        path[0] = search_hash_del(ver->x,ver->y,graph,&error);
        check_cycle(graph, ver,path,1);
        free(path);
        if(graph->vertex_table[ind]->service == 1)
        {
            printf("{%d,%d},{%d,%d}\n",ver->x,ver->y,graph->vertex_table[ind]->x,graph->vertex_table[ind]->y);
            del_edge(graph, ver->x, ver->y, create_edge(graph->vertex_table[ind]->x, graph->vertex_table[ind]->y));
            break;
        }
        recur_mod(graph, graph->vertex_table[ind]);
        mem = mem->next;
    }
    ver->service = 1;
}
void mod_gr(Graph *graph,int * error)
{
    for (int i = 0; i < graph->msize; i++)
    {
        if(graph->vertex_table[i] != NULL)
        {
            graph->vertex_table[i]->service = 0;
        }
    }
    for(int i = 0; i < graph->msize; i++)
    {
        if(graph->vertex_table[i] != NULL)
        {
            if(graph->vertex_table[i]->type != 2)
            {
                recur_mod(graph,graph->vertex_table[i]);
                for (int i = 0; i < graph->msize; i++)
                {
                    if(graph->vertex_table[i] != NULL)
                    {
                        graph->vertex_table[i]->service = 0;
                    }
                }
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
