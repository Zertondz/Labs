#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matr_de.h"
#include "tools.h"
int round_up(int a,int b)
{
    if (0 == a % b)
    {
        return a / b;
    }
    else
    {
        return a / b + 1;
    }
}

void output_table(const Table* table)
{
    Node* data = NULL;
    if (table->csize == 0)
    {
        printf("The table is empty!!\n");
    }
    for (unsigned int i = 0; i < table->csize;i++)
    {
        printf("[%d]: ",table->ks[i].key);
        data = table->ks[i].node;
        if (table->ks[i].node->release != 0)
        {
            while(data != NULL)
            {
                printf("%d.%d | ",*data->info,data->release);
                data = data->next;
            }
            printf("\n");
            continue;
        }
        else
        {
            printf("%d.%d",*data->info,data->release);
        }
        printf("\n");
    }
}
void output_table_i(const Iterator ind)
{
    Node* data = NULL;
    printf("[%d]: ",ind.ptr->key);
    data = ind.ptr->node;
    if (ind.ptr->node->release != 0)
    {
        while(data != NULL)
        {
            printf("%d.%d | ",*data->info,data->release);
            data = data->next;
        }
    }
    else
    {
        printf("%d.%d",*data->info,data->release);
    }
    printf("\n");
}
Iterator input_in_table(const unsigned int key,const unsigned value_in, Table * table)
{
    int error = 0;
    Iterator ind;
    Node * element = (Node*)calloc(1,sizeof(Node));
    unsigned int * value = (unsigned int *)calloc(1,sizeof(unsigned int));
    (*value) = value_in;
    ind = search_bin_2_0_I(key,table,&error);
    //printf("%d --- %d\n", ind.ptr - begin(table).ptr,ind.ptr);
    element->info = value;
    if (error == -1)
    {
        if (table->csize ==table->msize)
        {
            free(value), free(element);
            return id_er();
        }
        if (table->csize != 0)
        {
            if ((table->csize - (ind.ptr - begin(table).ptr)) != 0)
            {
                memmove(next(ind).ptr, ind.ptr,(table->csize - (ind.ptr - begin(table).ptr))*sizeof(KeySpace));
            }
        }
        ind.ptr->key = key;
        ind.ptr->node = element;
        table->csize++;
    }
    else
    {
        element->release = ind.ptr->node->release + 1;
        element->next = ind.ptr->node;
        ind.ptr->node = element;
    }
    return ind;
}

Iterator search_bin_2_0_I(const unsigned int key,const Table * table, int * error)
{
    Iterator dow = begin(table), upe = create_it(table,table->csize-1),ind = begin(table);
    if (table->csize == 0)
    {
        (*error) = -1;
        return begin(table);
    }
    while(1)
    {
        if (next_id(ind, round_up((upe.ptr - dow.ptr),2)).ptr->key == key)
        {
            return next_id(ind, round_up((upe.ptr - dow.ptr),2));
        }
        else if (next_id(ind, round_up((upe.ptr - dow.ptr),2)).ptr->key < key)
        {
            if (upe.ptr == dow.ptr)
            {
                break;
            }
            dow = next_id(dow,round_up((upe.ptr - dow.ptr),2));
            ind = dow;
        }
        else if (next_id(ind, round_up((upe.ptr - dow.ptr),2)).ptr->key > key)
        {
            if (upe.ptr == dow.ptr)
            {
                break;
            }
            upe = next_id(ind, ((upe.ptr - dow.ptr) / 2));
        }
    }
    if (key < begin(table).ptr->key)
    {
        (*error) = -1;
        return begin(table);
    }
    (*error) = -1;
    return next(dow);
}

Table* search_key_elem_rel(const unsigned int key,const unsigned int release, const Table * table)
{
    Node*data = NULL, * element = NULL;
    int error = 0;
    Iterator ind = search_bin_2_0_I(key,table,&error);
    if (error == -1)
    {
        return NULL;
    }
    Table *copy_table = initialization_table(1);
    copy_table->ks->key = ind.ptr->key;
    data = ind.ptr->node;
    while (data != NULL)
    {
        if(data->release == release)
        {
            element = (Node*)calloc(1,sizeof(Node));
            unsigned int * value = (unsigned int *)malloc(sizeof(unsigned int));
            (*value) = *(data->info);
            element->release = data->release;
            element->info = value;
            element->next = NULL;
            copy_table->ks->node = element;
            copy_table->csize = 1;
            return copy_table;
        }
        else
        {
            data = data->next;
        }
    }
    delete_all(copy_table);
    return NULL;
}
