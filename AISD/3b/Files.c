#include <stdio.h>
#include <stdlib.h>
#include "matr_de.h"
#include "tools.h"
#include "string.h"
void output_table_files(char *fname,const Table* table)
{
    unsigned int len = 0;
    char space = '\0', enter = '\n';
    if (table->csize == 0)
    {
        printf("The table is empty!!\n");
    }
    Node* data = NULL;
    FILE *file = fopen(fname,"wb");
    fwrite(&table->csize,sizeof(unsigned int),1,file);
    fwrite(&table->msize,sizeof(unsigned int),1,file);
    for (unsigned int i = 0; i < table->msize;i++)
    {
        fwrite(&table->ks[i].busy,sizeof(unsigned int),1,file);
        if (table->ks[i].busy == 1)
        {
            len = strlen(table->ks[i].key);
            fwrite(&len,sizeof(unsigned int),1,file);
            fwrite(table->ks[i].key,sizeof(char),len,file);
            data = table->ks[i].node;
            if (table->ks[i].node->release != 0)
            {
                while(data != NULL)
                {
                    fwrite(&space,sizeof(char),1,file);
                    len = strlen(data->info);
                    fwrite(&len,sizeof(unsigned int),1,file);
                    fwrite(data->info,sizeof(char),len,file);
                    fwrite(&data->release,sizeof(unsigned int),1,file);
                    data = data->next;
                }
            }
            else
            {
                fwrite(&space,sizeof(char),1,file);
                len = strlen(data->info);
                fwrite(&len,sizeof(unsigned int),1,file);
                fwrite(data->info,sizeof(char),len,file);
                fwrite(&data->release,sizeof(unsigned int),1,file);
            }
            fwrite(&enter,sizeof(char),1,file);
        }
        else
        {
            fwrite(&enter,sizeof(char),1,file);
        }
    }
    fclose(file);
}
Table* input_from_file(char * fname)
{
    char c = '\0',*value = NULL, * key = NULL;
    Node* element = NULL,*data = NULL;
    FILE *file = fopen(fname,"rb");
    unsigned int csize = 0, msize = 0,busy = 0,len = 0;
    if (file == NULL)
    {
        return NULL;
    }
    fread(&csize,sizeof(unsigned int),1,file);
    fread(&msize,sizeof(unsigned int),1,file);
    Table* table = initialization_table(msize);
    table->csize = csize;
    for(unsigned int i = 0; i < msize; i++)
    {
        fread(&busy,sizeof(unsigned int),1,file);
        table->ks[i].busy = busy;
        if(busy == 1)
        {
            fread(&len,sizeof(unsigned int),1,file);
            key = (char*)calloc(len + 1, sizeof(char));
            fread(key,sizeof(char),len,file);
            table->ks[i].key = key;
            fseek(file,1,SEEK_CUR);
            element = (Node*)calloc(1,sizeof(Node));
            fread(&len,sizeof(unsigned int),1,file);
            value = (char *)calloc(len + 1, sizeof(char));
            fread(value,sizeof(char),len,file);
            fread(&element->release,sizeof(unsigned int),1,file);
            element->info = value;
            table->ks[i].node = element;
            data = table->ks[i].node;
            while(1)
            {
                fread(&c,sizeof(char),1,file);
                if(c == '\n')
                {
                    break;
                }
                element = (Node*)calloc(1,sizeof(Node));
                fread(&len,sizeof(unsigned int),1,file);
                value = (char *)calloc(len + 1, sizeof(char));
                fread(value,sizeof(char),len,file);
                fread(&element->release,sizeof(unsigned int),1,file);
                element->info = value;
                data->next = element;
                data = data->next;
            }
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

int check_file(char * fname)
{
    char c = '\0';
    FILE *file = fopen(fname,"rb");
    unsigned int csize = 0, msize = 0,*rel = NULL, j = 1,busy = 0, len = 0;
    if (file == NULL)
    {
        return -1;
    }
    fread(&csize,sizeof(unsigned int),1,file);
    fread(&msize,sizeof(unsigned int),1,file);
    if (csize > msize)
    {
        fclose(file);
        return -1;
    }
    for(unsigned int i = 0; i < csize; i++)
    {
        fread(&busy,sizeof(unsigned int),1,file);
        if(busy == 1)
        {
            j = 1;
            rel = (unsigned int *)malloc(sizeof(unsigned int));
            fread(&len,sizeof(unsigned int),1,file);
            fseek(file,len * sizeof(char),SEEK_CUR);
            fseek(file,1,SEEK_CUR);
            fread(&len,sizeof(unsigned int),1,file);
            fseek(file,len * sizeof(char),SEEK_CUR);
            fread(&(rel[0]),sizeof(unsigned int),1,file);
            while(1)
            {
                fread(&c,sizeof(char),1,file);
                if(c == '\n')
                {
                    break;
                }
                fread(&len,sizeof(unsigned int),1,file);
                fseek(file,len * sizeof(char),SEEK_CUR);
                rel = (unsigned int *)realloc(rel,(j + 1) * sizeof(unsigned int));
                fread(&(rel[j]),sizeof(unsigned int),1,file);
                j++;
            }
            if (check_arr_rel(rel,j) == -1)
            {
                free(rel);
                fclose(file);
                return -1;
            }
            free(rel);
        }
    }
    fclose(file);
    return 0;
}
