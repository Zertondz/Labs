#include <stdio.h>
#include <stdlib.h>
#include "matr_de.h"
#include "tools.h"
void output_table_files(char *fname,const Table* table)
{
    if (table->csize == 0)
    {
        printf("The table is empty!!\n");
    }
    Node* data = NULL;
    FILE *file = fopen(fname,"w");
    fprintf(file,"%d %d\n",table->csize,table->msize);
    for (unsigned int i = 0; i < table->csize;i++)
    {
        fprintf(file,"[%d]: ",table->ks[i].key);
        data = table->ks[i].node;
        if (table->ks[i].node->release != 0)
        {
            while(data != NULL)
            {
                fprintf(file," %d.%d",*data->info,data->release);
                data = data->next;
            }
            fprintf(file,"\n");
            continue;
        }
        else
        {
            fprintf(file,"%d.%d",*data->info,data->release);
        }
        fprintf(file,"\n");
    }
    fclose(file);
}
Table* input_from_file(char * fname)
{
    char c = '\0';
    Node* element = NULL,*data = NULL;
    FILE *file = fopen(fname,"r");
    unsigned int csize = 0, msize = 0,*value = 0;
    if (file == NULL)
    {
        return NULL;
    }
    fscanf(file,"%d%d",&csize,&msize);
    fscanf(file,"%*c");
    Table* table = initialization_table(msize);
    table->csize = csize;
    for(unsigned int i = 0; i < csize; i++)
    {
        fscanf(file,"%*c%d%*c%*c",&(table->ks[i].key));
        element = (Node*)calloc(1,sizeof(Node));
        value = (unsigned int *)malloc(sizeof(unsigned int));
        fscanf(file,"%d",value);
        element->info = value;
        fscanf(file,"%*c%d",&(element->release));
        table->ks[i].node = element;
        data = table->ks[i].node;
        while(1)
        {
            fscanf(file,"%c",&c);
            if(c == '\n')
            {
                break;
            }
            element = (Node*)calloc(1,sizeof(Node));
            value = (unsigned int *)malloc(sizeof(unsigned int));
            fscanf(file,"%d",value);
            element->info = value;
            fscanf(file,"%*c%d",&(element->release));
            data->next = element;
            data = data->next;
        }
    }
    fclose(file);
    return table;
}
int check_arr_rel(unsigned int * arr, unsigned int len)
{
    for (unsigned int i = 0;i < len - 1;i++)
    {
        for (unsigned int j = i + 1;j < len;j++)
        {
            if(arr[i] == arr[j])
            {
                return -1;
            }
        }
        if(arr[i] < arr[i+1])
        {
            return -1;
        }
    }
    return 0;
}
int check_arr_key(unsigned int * arr, unsigned int len)
{
    for (unsigned int i = 0;i < len - 1;i++)
    {
        for (unsigned int j = i + 1;j < len;j++)
        {
            if(arr[i] == arr[j])
            {
                return -1;
            }
        }
        if(arr[i] > arr[i+1])
        {
            return -1;
        }
    }
    return 0;
}
int check_file(char * fname)
{
    char c = '\0';
    FILE *file = fopen(fname,"r");
    unsigned int csize = 0, msize = 0,*rel = NULL,*key = NULL, j = 1;
    if (file == NULL)
    {
        return -1;
    }
    fscanf(file,"%d%d",&csize,&msize);
    if (csize > msize)
    {
        return -1;
    }
    fscanf(file,"%*c");
    key = (unsigned int *)malloc(csize * sizeof(unsigned int));
    for(unsigned int i = 0; i < csize; i++)
    {
        j = 1;
        fscanf(file,"%*c%d%*c%*c",&(key[i]));
        rel = (unsigned int *)malloc(sizeof(unsigned int));
        fscanf(file,"%*d");
        fscanf(file,"%*c%d",&(rel[0]));
        while(1)
        {
            fscanf(file,"%c",&c);
            if(c == '\n')
            {
                break;
            }
            fscanf(file,"%*d");
            rel = (unsigned int *)realloc(rel,(j + 1) * sizeof(unsigned int));
            fscanf(file,"%*c%d",&(rel[j]));
            j++;
        }
        if (check_arr_rel(rel,j) == -1)
        {
            free(key), free(rel);
            fclose(file);
            return -1;
        }
        free(rel);
    }
    if (check_arr_key(key,csize) == -1)
    {
        free(key);
        fclose(file);
        return -1;
    }
    free(key);
    fclose(file);
    return 0;
}
