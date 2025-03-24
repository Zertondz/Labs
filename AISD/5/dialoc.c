#include <stdlib.h>
#include <stdio.h>
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <graphviz/pathplan.h>
#include <graphviz/cgraph.h>
#include "dialoc.h"
#include "graph.h"
#include "tools.h"
int dia_add_ver(Graph **graph)
{
    unsigned int x = 0, y = 0, type = 3;
    while(type > 2)
    {
        if(str_chint(&type,2) == -1)
        {
            return -1;
        }
    }
    if(str_chint(&x,3) == -1)
    {
        return -1;
    }
    if(str_chint(&y,4) == -1)
    {
        return -1;
    }
    if (add_ver(graph,create_ver(x,y,type)) == -1)
    {
        printf("Such a vertex already exists!!!\n");
    }
    return 0;
}
int dia_add_edge(Graph *graph)
{
    unsigned int x_f = 0, y_f = 0, x_to = 0, y_to = 0;
    int error = 0;
    printf("Enter the beginning of the edge:\n");
    if(str_chint(&x_f,3) == -1)
    {
        return -1;
    }
    if(str_chint(&y_f,4) == -1)
    {
        return -1;
    }
    printf("Enter the end of the edge:\n");
    if(str_chint(&x_to,3) == -1)
    {
        return -1;
    }
    if(str_chint(&y_to,4) == -1)
    {
        return -1;
    }
    if(check_coordinates(x_f,y_f,x_to,y_to) == 0)
    {
        printf("The cells are not adjacent!!!\n");
        return 0;
    }
    error = add_edge(graph,x_f,y_f, create_edge(x_to,y_to));
    if (error == -2)
    {
        printf("The maximum number of edges has already been reached!!!\n");
    }
    else if(error == -1)
    {
        printf("One or two vertices do not exist!!!\n");
    }
    else if(error == -3)
    {
        printf("Such an edge already exists!!!\n");
    }
    else if (error == -4)
    {
        printf("Unsuitable cell type!!!\n");
    }
    return 0;
}
int dia_del_ver(Graph *graph)
{
    unsigned int x = 0, y = 0;
    if(graph->csize == 0)
    {
        printf("Matrix is empty!!!\n");
        return 1;
    }
    if(str_chint(&x,3) == -1)
    {
        return -1;
    }
    if(str_chint(&y,4) == -1)
    {
        return -1;
    }
    if(del_ver(x, y, graph) == -1)
    {
        printf("The element was not found!!!\n");
    }
    return 0;
}
int dia_del_edge(Graph *graph)
{
    unsigned int x_f = 0, y_f = 0, x_to = 0, y_to = 0;
    int error = 0;
    printf("Enter the beginning of the edge:\n");
    if(str_chint(&x_f,3) == -1)
    {
        return -1;
    }
    if(str_chint(&y_f,4) == -1)
    {
        return -1;
    }
    printf("Enter the end of the edge:\n");
    if(str_chint(&x_to,3) == -1)
    {
        return -1;
    }
    if(str_chint(&y_to,4) == -1)
    {
        return -1;
    }
    if(check_coordinates(x_f,y_f,x_to,y_to) == 0)
    {
        printf("The cells are not adjacent!!!\n");
        return 0;
    }
    error = del_edge(graph,x_f,y_f, create_edge(x_to,y_to));
    if (error == -2)
    {
        printf("The minimum number of edges has already been reached!!!\n");
    }
    else if(error == -1)
    {
        printf("Edge does not exist!!!\n");
    }
    return 0;
}
int dia_change_ver(Graph *graph)
{
    unsigned int x = 0, y = 0, ind = 0, type = 3;
    int error = 0;
    if(str_chint(&x,3) == -1)
    {
        return -1;
    }
    if(str_chint(&y,4) == -1)
    {
        return -1;
    }
    ind = search_hash_del(x, y,graph,&error);
    if(error == -1)
    {
        printf("x = %d, y = %d, type = %d\n",graph->vertex_table[ind]->x,graph->vertex_table[ind]->y,graph->vertex_table[ind]->type);
        printf("Enter the new data!!!\n");
        while(type > 2)
        {
            if(str_chint(&type,2) == -1)
            {
                return -1;
            }
        }
        if(str_chint(&x,3) == -1)
        {
            return -1;
        }
        if(str_chint(&y,4) == -1)
        {
            return -1;
        }
        change_ver(graph, ind, x, y, type);
    }
    else
    {
        printf("The element was not found!!!\n");
    }
    return 0;
}
int dial_path(Graph *graph)
{
    unsigned int x_f = 0, y_f = 0, x_to = 0, y_to = 0, j = 0;
    int error = 0;
    int * from = NULL,*from_r = NULL;
    printf("Enter the coordinates of the entrance!!\n");
    if(str_chint(&x_f,3) == -1)
    {
        return -1;
    }
    if(str_chint(&y_f,4) == -1)
    {
        return -1;
    }
    printf("Enter the coordinates of the exit!!\n");
    if(str_chint(&x_to,3) == -1)
    {
        return -1;
    }
    if(str_chint(&y_to,4) == -1)
    {
        return -1;
    }
    from = sh_path(graph, x_f, y_f, x_to, y_to,&error);
    if (from == NULL)
    {
        printf("There is no way!!!\n");
    }
    else
    {
        from_r = (int *)calloc(graph->msize, sizeof(int));
        for(int i = search_hash_del(x_to, y_to, graph, &error); i != -1; i = from[i])
        {
            from_r[j] = i;
            j++;
        }            
        for(int i = j - 1; i >= 0; i--)
        {
            printf("{%d, %d}->",graph->vertex_table[from_r[i]]->x,graph->vertex_table[from_r[i]]->y);
        }            
    }
    return 0;
}
int dia_traverlas(Graph *graph)
{
    unsigned int x = 0, y = 0;
    if(str_chint(&x,3) == -1)
    {
        return -1;
    }
    if(str_chint(&y,4) == -1)
    {
        return -1;
    }
    printf("Exits: ");
    travelsal(graph, x, y);
    printf("\n");
    return 0;
}
int dia_mod(Graph *graph)
{
    int error = 0;
    mod_gr(graph, &error);
    if (error == -1)
    {
        printf("It won't work that way!!!\n");
    }
    return 0;
}