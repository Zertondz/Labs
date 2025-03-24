#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matr_de.h"
#include "tools.h"
void output_table(const Table* table)
{
    Node* data = NULL;
    if (table->csize == 0)
    {
        printf("The table is empty!!\n");
    }
    for (unsigned int i = 0; i < table->msize;i++)
    {
        if (table->ks[i].busy == 1)
        {
            printf("%d|[%s]: ",i,table->ks[i].key);
            data = table->ks[i].node;
            if (table->ks[i].node->release != 0)
            {
                while(data != NULL)
                {
                    printf("%s.%d | ",data->info,data->release);
                    data = data->next;
                }
                printf("\n");
                continue;
            }
            else
            {
                printf("%s.%d",data->info,data->release);
            }
            printf("\n");
        }
    }
}

int input_in_table(char* key,char * value, Table ** table)
{
    int ind = 0, error = 0;
    Node * element = (Node*)calloc(1,sizeof(Node));
    ind = search_hash(key,(*table),&error);
    element->info = value;
    if (error != -1)
    {
        if (error == -2)
        {
            (*table) = expend_table((*table));
            ind = search_hash(key,(*table),&error);
        }
        (*table)->ks[ind].key = key;
        (*table)->ks[ind].node = element;
        (*table)->ks[ind].busy = 1;
        (*table)->csize++;
    }
    else
    {
        element->release = (*table)->ks[ind].node->release + 1;
        element->next = (*table)->ks[ind].node;
        (*table)->ks[ind].node = element;
        free(key);
    }
    return 0;
}

unsigned int search_hash(char *key,Table * table,int *error)
{
    unsigned int ind = 0,i = 0;
    while(i != table->msize)
    {
        ind = double_hash(key,i,table->msize);
        if (table->ks[ind].busy == 0)
        {
            (*error) = 0;
            return ind;
        }
        else
        {
            if(strcmp(table->ks[ind].key,key) == 0)
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

Table* search_key_elem(char * key, Table * table)
{
    int ind = 0, error = 0;
    Node*data = NULL, * element = NULL,*data_copy = NULL;
    ind = search_hash(key,table,&error);
    if (error == -1)
    {
        Table *copy_table = initialization_table(1);
        copy_table->csize = 1;
        copy_table->ks->key = key;
        copy_table->ks->busy = 1;
        data = table->ks[ind].node;
        data_copy = copy_table->ks->node;
        while (data != NULL)
        {
            element = (Node*)calloc(1,sizeof(Node));
            char * value = (char *)malloc(sizeof(char)*(strlen(data->info) + 1));
            value = strcpy(value, data->info);
            element->release = data->release;
            element->info = value;
            element->next = NULL;
            if(copy_table->ks->node == NULL)
            {
                copy_table->ks->node = element;
                data_copy = copy_table->ks->node;
            }
            else
            {
                data_copy->next = element;
                data_copy = data_copy->next;
            }
            data = data->next;
        }
        return copy_table;
    }
    else
    {
        free(key);
        return NULL;
    }
}

Table* search_key_elem_rel(char * key,const unsigned int release, Table * table)
{
    int ind = 0, error = 0;
    Node*data = NULL, * element = NULL;
    ind = search_hash(key, table, &error);
    if (error == -1)
    {
        Table *copy_table = initialization_table(1);
        copy_table->csize = 1;
        copy_table->ks->key = key;
        copy_table->ks->busy = 1;
        data = table->ks[ind].node;
        while (data != NULL)
        {
            if(data->release == release)
            {
                element = (Node*)calloc(1,sizeof(Node));
                char * value = (char *)malloc(sizeof(char)*(strlen(data->info) + 1));
                value = strcpy(value, data->info);
                element->release = data->release;
                element->info = value;
                element->next = NULL;
                copy_table->ks->node = element;
                return copy_table;
            }
            else
            {
                data = data->next;
            }
        }
        free(key);
        copy_table->ks->busy = 0;
        delete_all(copy_table);
        return NULL;
    }
    else
    {
        free(key);
        return NULL;
    }
}
