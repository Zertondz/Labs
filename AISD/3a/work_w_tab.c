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
int input_in_table(const unsigned int key,const unsigned value_in, Table * table)
{
    int ind = 0;
    Node * element = (Node*)calloc(1,sizeof(Node));
    unsigned int * value = (unsigned int *)calloc(1,sizeof(unsigned int));
    (*value) = value_in;
    ind = search_bin_2_0(key,table);
    element->info = value;
    if (ind <= -1)
    {
        if (table->csize ==table->msize)
        {
            free(value), free(element);
            return -2;
        }
        ind = (-1)*(ind + 1);
        if (table->csize != 0)
        {
            if ((table->csize - ind) != 0)
            {
                memmove(&table->ks[ind + 1], &table->ks[ind],(table->csize - ind)*sizeof(KeySpace));
            }
        }
        table->ks[ind].key = key;
        table->ks[ind].node = element;
        table->csize++;
    }
    else
    {
        element->release = table->ks[ind].node->release + 1;
        element->next = table->ks[ind].node;
        table->ks[ind].node = element;
    }
    return 0;
}


int search_bin_2_0(const unsigned int key,const Table * table)
{
    int dow = 0, upe = table->csize - 1,ind = 0;
    if (table->csize == 0)
    {
        return -1;
    }
    while(1)
    {
        if (table->ks[ind + round_up((upe - dow),2)].key == key)
        {
            return ind + round_up((upe - dow),2);
        }
        else if (table->ks[ind + round_up((upe - dow),2)].key < key)
        {
            if (upe == dow)
            {
                break;
            }
            dow += round_up((upe - dow),2);
            ind = dow;
        }
        else if (table->ks[ind + round_up((upe - dow),2)].key > key)
        {
            if (upe == dow)
            {
                break;
            }
            upe = ind + ((upe - dow) / 2);
        }
    }
    if (key < table->ks[0].key)
    {
        return -1;
    }
    return (-1) * (dow + 2);
}
Table* search_key_elem(const unsigned int key,const Table * table)
{
    Node*data = NULL, * element = NULL,*data_copy = NULL;
    int ind = search_bin_2_0(key,table);
    if (ind <= -1)
    {
        return NULL;
    }
    Table *copy_table = initialization_table(1);
    copy_table->csize = 1;
    copy_table->ks->key = table->ks[ind].key;
    data = table->ks[ind].node;
    data_copy = copy_table->ks->node;
    while (data != NULL)
    {
        element = (Node*)calloc(1,sizeof(Node));
        unsigned int * value = (unsigned int *)malloc(sizeof(unsigned int));
        (*value) = *(data->info);
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

Table* search_key_elem_rel(const unsigned int key,const unsigned int release, const Table * table)
{
    Node*data = NULL, * element = NULL;
    int ind = search_bin_2_0(key,table);
    if (ind <= -1)
    {
        return NULL;
    }
    Table *copy_table = initialization_table(1);
    copy_table->csize = 1;
    copy_table->ks->key = table->ks[ind].key;
    data = table->ks[ind].node;
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
