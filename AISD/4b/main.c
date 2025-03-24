#include <stdlib.h>
#include <stdio.h>
#include <graphviz/gvc.h>
#include <graphviz/cdt.h>
#include <graphviz/pathplan.h>
#include <graphviz/cgraph.h>
#include "tree.h"
#include "tools.h"
#include "dialog.h"
int main()
{
    unsigned int mode = 0;
    int error = 0;
    Tree * tree = NULL;
    while (str_chint(&mode,1) != -1)
    {
        switch (mode)
        {
        case 1:
            if (tree == NULL)
            {
                tree = (Tree*)calloc(1,sizeof(Tree));
            }
            if (dial_add_el(tree)== -1)
            {
                return -1;
            }
            dial_output(tree);
            break;
        case 2:
            if (dial_del_elem(tree) == -1)
            {
                return -1;
            }
            break;
        case 3:
            if (dial_travel(tree) == -1)
            {
                return -1;
            }
            break;
        case 4:
            if (dial_search(tree) == -1)
            {
                return -1;
            }
            break;
        case 5:
            if (dial_search_min(tree) == -1)
            {
                return -1;
            }
            break;
        case 6:
            dial_output(tree);
            break;
        case 7:
            graph(tree);
            break;
        case 8:
            tree = read_f_file(&error);
            if (error == -1)
            {
                return -1;
            }
            break;
        case 9:
            test_time();
            break;
        case 10:
            tree = dial_add_task(tree);
            if (tree == NULL)
            {
                return -1;
            }
        default:
            break;
        }
    }
    if (tree != NULL)
    {
        if (tree->root != NULL)
        {
            delet_all(tree->root);
            
        }
        free(tree);
    }
    return 0;
}