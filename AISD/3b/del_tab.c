#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matr_de.h"
#include "tools.h"
void delete_all(Table* table)
{
    Node* data = NULL, * data_mem = NULL;
    for (unsigned int i = 0; i < table->msize;i++)
    {
        if (table->ks[i].busy == 1)
        {
            data = table->ks[i].node;
            if (table->ks[i].node->release != 0)
            {
                while(data != NULL)
                {
                    data_mem = data->next;
                    free(data->info);
                    free(data);
                    data = data_mem;
                }
            }
            else
            {
                free(data->info);
                free(data);
            }
            free(table->ks[i].key);
        }
    }
    free(table->ks);
    free(table);
}
int delete_key_elem(char * key, Table* table)
{
    int ind, error;
    Node* data = NULL, * data_mem = NULL;
    if (table->csize == 0)
    {
        return -2;
    }
    ind = search_hash(key,table,&error);
    if (error == 0)
    {
        return -1;
    }
    if (error == -1)
    {
        data = table->ks[ind].node;
        if (table->ks[ind].node->release != 0)
        {
            while(data != NULL)
            {
                data_mem = data->next;
                free(data->info);
                free(data);
                data = data_mem;
            }
        }
        else
        {
            free(data->info);
            free(data);
        }
        free(table->ks[ind].key);
        table->ks[ind].busy = 0;
    }
    table->csize--;
    return 0;
}
int delete_key_elem_rel(char * key,const unsigned int release, Table* table)
{
    int error = 0, ind = 0;
    Node* data = NULL, * data_mem = NULL;
    if (table->csize == 0)
    {
        return -2;
    }
    ind = search_hash(key,table,&error);
    if (error == 0)
    {
        return -1;
    }
    if (error == -1)
    {
        data = table->ks[ind].node;
        if (data->next != NULL)
        {
            if (data->release == release)
            {
                table->ks[ind].node = table->ks[ind].node->next;
                free(data->info);
                free(data);
                return 0;
            }
            while(data->next != NULL)
            {
                data_mem = data;
                data = data->next;
                if (data->release == release)
                {
                    data_mem->next = data->next;
                    free(data->info);
                    free(data);
                    return 0;
                }
            }
            if (data->release == release)
            {
                free(data->info);
                free(data);
                data_mem->next = NULL;
            }
            else
            {
                return -1;
            }
        }
        else
        {
            if (release == data->release)
            {
                free(data->info);
                free(data);
                free(table->ks[ind].key);
                table->ks[ind].busy = 0;
                table->csize--;
            }
            else
            {
                return -1;
            }
        }
    }
    return 0;
}
