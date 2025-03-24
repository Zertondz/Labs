#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "tools.h"
#include "dialoc.h"
#include "add.h"
int main()
{
    unsigned int mode = 0;
    Graph * graph = NULL;
    while(str_chint(&mode,1) != -1)
    {
        switch (mode)
        {
        case 1:
            if(graph == NULL)
            {
                graph = initialization_table(1);
            }
            if(dia_add_ver(&graph) == -1)
            {
                delete_all(graph);
                free(graph);
                return -1;
            }
            output(graph);
            break;
        case 2:
            if (dia_add_edge(graph) == -1)
            {
                delete_all(graph);
                free(graph);
                return -1;
            }
            break;
        case 3:
            if (dia_del_ver(graph) == -1)
            {
                delete_all(graph);
                free(graph);
                return -1;
            }
            break;
        case 4:
            if (dia_del_edge(graph) == -1)
            {
                delete_all(graph);
                free(graph);
                return -1;
            }
            break;
        case 5:
            if(dia_traverlas(graph) == -1)
            {
                delete_all(graph);
                free(graph);
                return -1;
            }
            break;
        case 6:            
            if (dia_change_ver(graph) == -1)
            {
                delete_all(graph);
                free(graph);
                return -1;
            }
            break;
        case 7:
            graphvi(graph);
            break;
        case 8:
            output(graph);
            break;
        case 9:
            dial_path(graph);
            break;
        case 10:
            dia_mod(graph);
            break;
        case 11:
            if(graph != NULL)
            {
                delete_all(graph);
                free(graph);
            }
            graph = read_f();
            break;
        case 12:
            generator();
            break;
        case 13:
            dial_path_add(graph);
            break;
        default:
            break;
        }
    }
    if (graph != NULL)
    {
        delete_all(graph);
        free(graph);
    }
    return 0;
}