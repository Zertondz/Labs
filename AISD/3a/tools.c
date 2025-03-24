#include <stdio.h>
#include <stdlib.h>
#include "matr_de.h"
#include "tools.h"
#ifdef ITERATOR
Iterator begin(const Table * table)
{
    Iterator it = {table->ks};
    return it;
}
Iterator end(const Table * table)
{
    Iterator it = {table->ks + table->csize};
    return it;
}
Iterator next_id(const Iterator it,const unsigned int id)
{
    Iterator it_fu = {it.ptr + id};
    return it_fu;
}
Iterator id_er()
{
    Iterator it = {0};
    return it;
}
Iterator next(const Iterator it)
{
    Iterator it_fu = {it.ptr + 1};
    return it_fu;
}
int ifeq(const Iterator it_a, const Iterator it_b)
{
    if (it_a.ptr == it_b.ptr)
    {
        return 1;
    }
    return 0;
}
Iterator create_it(const Table * table, const int id)
{
    Iterator id_fu = {table->ks + id};
    return id_fu;
}
#endif
int str_chint(unsigned int* n1,int mode)
{
    int ke = 1,n2,f;
    char c;
    switch(mode)
    {
    case 1:
        printf("(1) Entering in a table\n"
           "(2) Displaying the table on the screen\n"
           "(3) Deleting all items by key\n"
           "(4) Deleting a version by key\n"
           "(5) Search by key\n"
           "(6) Search by key and release\n"
           "(7) Output to a file\n"
           "(8) Input from a file\n"
           "option:  ");
           break;
    case 2:
        printf("Enter the size of the table: ");
        break;
    case 3:
        printf("Enter the key: ");
        break;
    case 4:
        printf("Enter the values: ");
        break;
    case 5:
        printf("Enter the release: ");
        break;
    case 6:
        printf("(1) input from a keyboard\n"
               "(2) Input from a file\n"
               "option: ");
    }
    while (ke !=0)
    {
        ke = 0;
        f = scanf("%d",&n2);
        if (f == 0)
        {
            scanf("%*[^\n]");
            ke++;
            printf("Enter an integer: ");
        }
        else if (f == -1)
        {
            return -1;
        }
        else
        {
            scanf("%c",&c);
            if ((c == 10) && (n2 >= 0))
            {
                (*n1) = n2;
            }
            else if(n2 < 0)
            {
                printf("Enter a positive number!\n");
                ke++;
            }
            else
            {
                scanf("%*[^\n]");
                ke++;
                printf("Enter an integer: ");
            }
        }
    }
    return 1;
}
Table * initialization_table(int size)
{
    Table * table = (Table*)calloc(1,sizeof(Table));
    table->msize = size;
    table->ks = (KeySpace*)calloc(size,sizeof(KeySpace));
    return table;
}

char * readline12(char rasd[])
{
    int k = 0,countch = 1, f = 0, d = 0;
    printf("%s",rasd);
    char* itog = (char*)malloc(sizeof(char)*11);
    char masd[11];
    scanf("%*[\n]");
    while (f == 0)
    {
        for (int i = 0; i < 11; i++)
        {
            masd[i] = 0;
        }
        d = scanf("%11[^\n]",masd);
        if (d == -1)
        {
            free(itog);
            return NULL;
        }
        else if(d == 0)
        {
            f = 1;
            k++;
        }
        else if(d == 1)
        {
            for (int i = 0;i < 11;i++)
            {
                if (masd[i] == 0)
                {
                    break;
                }
                itog[k] = masd[i];
                k++;
            }
        }
        countch++;
        itog = realloc(itog,sizeof(char)*countch*11);
    }
    itog = realloc(itog,sizeof(char) * k);
    itog[k-1] = '\0';
    return itog;
}
