#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matr_de.h"
#include "tools.h"
void delete_all(Table* table)
{
    Node* data = NULL, * data_mem = NULL;
    for (unsigned int i = 0; i < table->csize;i++)
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
            continue;
        }
        else
        {
            free(data->info);
            free(data);
        }
    }
    free(table->ks);
    free(table);
}
int delete_key_elem(const unsigned int key, Table* table)
{
    Node* data = NULL, * data_mem = NULL;
    if (table->csize == 0)
    {
        return -2;
    }
    int ind = search_bin_2_0(key, table);
    if (ind <= -1)
    {
        return -1;
    }
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
    memmove(&table->ks[ind], &table->ks[ind + 1],(table->csize - ind - 1)*sizeof(KeySpace));
    table->csize--;
    return 0;
}
int delete_key_elem_rel(const unsigned int key,const unsigned int release, Table* table)
{
    Node* data = NULL, * data_mem = NULL;
    if (table->csize == 0)
    {
        return -2;
    }
    int ind = search_bin_2_0(key, table);
    if (ind <= -1)
    {
        return -1;
    }
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
            memmove(&table->ks[ind], &table->ks[ind + 1],(table->csize - ind - 1)*sizeof(KeySpace));
            table->csize--;
        }
        else
        {
            return -1;
        }
    }
    return 0;
}
