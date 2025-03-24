#include <stdlib.h>
#include <stdio.h>
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <graphviz/pathplan.h>
#include <graphviz/cgraph.h>
#include <time.h>
#include "dialoc.h"
#include "graph.h"
#include "tools.h"
Agraph_t * graphvi_pr(Graph *graph) 
{
    if (graph == NULL)
    {
        printf("The tree is empty\n");
        return NULL;
    }
    if (graph->csize == 0)
    {
        printf("The tree is empty\n");
        return NULL;
    }
    Agraph_t *g;
    g = agopen("g",  Agdirected, 0);
    serv(g, graph);
    return g;
}
Graph * read_f()
{
    int count_ver = 0,count_edge = 0;
    unsigned int x = 0, y = 0,x_to = 0, y_to = 0, type = 0;
    char *name = readline12("Name file:");
    if(name == NULL)
    {
        return 0;
    }
    FILE *file  = fopen(name, "r");
    fscanf(file,"%d", &count_ver);
    fscanf(file,"%*c");
    fscanf(file,"%d", &count_edge);
    Graph* graph = initialization_table(1);
    printf("%d,%d\n",count_edge,count_ver);
    for(int i = 0; i < count_ver; i++)
    {
        fscanf(file, "%d", &x);
        fscanf(file,"%*c");
        fscanf(file, "%d", &y);
        fscanf(file,"%*c");
        fscanf(file, "%d", &type);
        add_ver(&graph, create_ver(x, y, type));
    }
    for(int i = 0; i < count_edge; i++)
    {
        fscanf(file, "%d", &x);
        fscanf(file,"%*c");
        fscanf(file, "%d", &y);
        fscanf(file,"%*c");
        fscanf(file, "%d", &x_to);
        fscanf(file,"%*c");
        fscanf(file, "%d", &y_to);
        add_edge(graph, x, y, create_edge(x_to,y_to));
    }
    free(name);
    fclose(file);
    return graph;
}
void generator()
{
    char *name = readline12("Name file:");
    unsigned int x_f = 0,y_f = 0, j = 0, type = 0, k = 1;
    FILE *file  = fopen(name, "w");
    srand(time(NULL));
    int size = 34, c_ed = 2000, size_q;
    size_q = size * size;
    fprintf(file,"%d %d\n",size_q,c_ed);
    Graph * graph = initialization_table(1);
    for(int x = 0; x < size;x++)
    {
        for(int y = 0; y < size; y++)
        {
            if(k % 10 == 0)
            {
                type = rand()%2 + 1;
            }
            add_ver(&graph,create_ver(x,y,type));
            fprintf(file,"%d,%d,%d\n",x,y,type);
            type = 0;
            k++;
        }
    }
    while(j < c_ed)
    {
        for(int i = 0;i < graph->msize;i++)
        {
            if(graph->vertex_table[i] != NULL)
            {
                x_f = graph->vertex_table[i]->x;
                y_f = graph->vertex_table[i]->y;
                if(rand()%5 >= 1)
                {
                    fprintf(file,"%d,%d>%d,%d\n",x_f,y_f,x_f + 1,y_f);
                    j++;
                }
                if(rand()%5 >= 1)
                {
                    fprintf(file,"%d,%d>%d,%d\n",x_f,y_f,x_f - 1,y_f);
                    j++;
                }
                if(rand()%5 >= 1)
                {
                    fprintf(file,"%d,%d>%d,%d\n",x_f,y_f,x_f,y_f + 1);
                    j++;
                }
                if(rand()%5 >= 1)
                {
                    fprintf(file,"%d,%d>%d,%d\n",x_f,y_f,x_f,y_f - 1);
                    j++;
                }
            }
        }
    }
    delete_all(graph);
    free(graph);
    fclose(file);
}
int dial_path_add(Graph *graph)
{
    unsigned int x_f = 0, y_f = 0, x_to = 0, y_to = 0, j = 0;
    int error = 0;
    int * from = NULL,*from_r = NULL;
    Agraph_t *g;
    GVC_t *gvc;
    Agnode_t *n1 = NULL,*n2 = NULL;
    Agedge_t *e;
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
        gvc = gvContext();
        g = graphvi_pr(graph);
        if(g == NULL)
        {
            return 0;
        }
        for(int i = j - 1; i >= 0; i--)
        {
            printf("{%d, %d}->",graph->vertex_table[from_r[i]]->x,graph->vertex_table[from_r[i]]->y);
            char * name = name_node(graph->vertex_table[from_r[i]]);
            n1 = agnode(g, name, 1);
            if (n2 != NULL)
            {
                e = agedge(g, n2, n1, 0, 1);
                agsafeset(e, "penwidth", "4", "");
                agsafeset(e, "color", "green", "");
            }
            n2 = n1;
            free(name);
        }            
        gvLayout(gvc, g, "dot");  
        gvRenderFilename(gvc, g, "svg", "output.svg");
        gvFreeLayout(gvc, g);
        agclose(g);
        gvFreeContext(gvc);
        printf("\n");
        free(from);
        free(from_r);
    }
    return 0;
}