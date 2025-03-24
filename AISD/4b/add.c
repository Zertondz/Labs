#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "tools.h"
#include "dialog.h"
char * create_value(unsigned int line_num, unsigned int dij_num, char* name_f)
{
    unsigned int nD_line = 1, nD_dij = 1;
    char * value = NULL;
    if (line_num != 0)
    {
        nD_line = floor(log10(abs(line_num))) + 1;
    }
    if (line_num != 0)
    {
        nD_dij = floor(log10(abs(dij_num))) + 1;
    }
    value = (char*)calloc(nD_dij + nD_line + strlen(name_f) + 3,sizeof(char));
    strcat(value,name_f);
    strcat(value,",");
    snprintf(value + strlen(name_f) + 1,nD_line + 2,"%d,",line_num);
    snprintf(value + strlen(name_f) + 2 + nD_line,nD_dij + 1,"%d",dij_num);
    return value;
}
Tree * read_f_file_d(Tree * tree,int * error)
{
    FILE * file = NULL;
    unsigned int key = 0;
    char * name = readline12("Enter the file name: "),*line = NULL,*num = NULL;
    if (name != NULL)
    {
        file = fopen(name,"r");
    }
    else
    {
        (*error) = -1;
        return tree;
    }
    if (file == NULL)
    {
        free(name);
        return tree;
    }
    line = freadline12(file);
    for(int num_line = 1;line;num_line++)
    {
        num = strtok(line,",");
        for(int num_dij = 1;num != NULL;num_dij++)
        {
            key = strtol(num, NULL, 10);
            tree->root = add_elem(tree->root,create_elem(key,create_value(num_line, num_dij, name)));
            num = strtok(NULL,",");
        }
        free(line);
        line = freadline12(file);
    }
    fclose(file);
    free(name);
    return tree;
}
