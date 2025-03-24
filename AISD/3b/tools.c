#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matr_de.h"
#include "tools.h"
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
           "(9) Enlarge the table\n"
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
unsigned long polinom_hash(const char* s,unsigned int msize)
{
    long long p = 111111, m = 1e9 + 7;
    long long hash = 0;
    long long p_pow = 1;
    int len = strlen(s),j = 0;
    while (NOD(msize,hash) != 1)
    {
        for(int i = 0; i < len; i++) {
            hash = (hash + (s[i] + j) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        hash = hash % msize;
        j++;
    }
    return hash;
}
unsigned long djb2_hash(char *str,unsigned int msize)
 {
    unsigned long hash = 5381;
    int c = 0;
    while ((c = *(str++)))
    hash = ((hash << 5) + hash) + c;
    return hash%msize;
 }
unsigned int double_hash(char *str,const unsigned int i,const unsigned msize)
{
    unsigned int ind = (djb2_hash(str,msize) + i * polinom_hash(str,msize)) % msize;
    return ind;
}
unsigned int near_simp(unsigned int amount)
{
    unsigned int flag = 1;
    amount++;
    while(flag == 1)
    {
        flag = 0;
        for (unsigned int i = 2;i < ((unsigned int)sqrt(amount) + 1);i++)
        {
            if((amount % i) == 0)
            {
                amount++;
                flag = 1;
                break;
            }
        }
    }
    return amount;
}
Table *  expend_table(Table * table)
{
    int error = 0;
    unsigned int ind = 0;
    Table * copy_table = initialization_table(near_simp(table->msize));
    copy_table->csize = table->csize;
    for (unsigned int i = 0; i < table->msize; i++)
    {
        if(table->ks[i].busy == 1)
        {
            ind = search_hash(table->ks[i].key,copy_table,&error);
            copy_table->ks[ind].node = table->ks[i].node;
            copy_table->ks[ind].key = table->ks[i].key;
            copy_table->ks[ind].busy = 1;
        }
    }
    printf("The size has been increased: %d --> %d\n",table->msize,copy_table->msize);
    free(table->ks);
    free(table);
    return copy_table;
}
int NOD(int a,int b)
{
    while((a != 0)&&(b != 0))
    {
        if (a > b)
        {
            a = a % b;
        }
        else
        {
            b = b % a;
        }
    }
    return (a + b);
}
