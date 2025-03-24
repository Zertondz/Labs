#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matr_de.h"
#include "tools.h"

void delete_all(Table* table)
{
    Node* data = NULL, * data_mem = NULL;
    for (Iterator it = begin(table); (it.ptr - begin(table).ptr) < table->csize;it = next(it))
    {
        data = it.ptr->node;
        if (it.ptr->node->release != 0)
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
Iterator delete_key_elem(const Iterator ind, Table* table)
{
    Node* data = NULL, * data_mem = NULL;
    data = ind.ptr->node;
    if (ind.ptr->node->release != 0)
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
    memmove(ind.ptr, next(ind).ptr,(table->csize - (ind.ptr - begin(table).ptr) - 1)*sizeof(KeySpace));
    table->csize--;
    return ind;
}
Iterator delete_key_elem_rel(const Iterator ind,const unsigned int release, Table* table)
{
    Node* data = NULL, * data_mem = NULL;
    data = ind.ptr->node;
    if (data->next != NULL)
    {
        if (data->release == release)
        {
            ind.ptr->node = ind.ptr->node->next;
            free(data->info);
            free(data);
            return ind;
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
                return ind;
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
            return id_er();
        }
    }
    else
    {
        if (release == data->release)
        {
            free(data->info);
            free(data);
            memmove(ind.ptr, next(ind).ptr,(table->csize - (ind.ptr - begin(table).ptr) - 1)*sizeof(KeySpace));
            table->csize--;
        }
        else
        {
            return id_er();
        }
    }
    return ind;
}
