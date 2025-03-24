#include "matr.h"
#include <stdio.h>
#include <stdlib.h>
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

int str_chint(int* n1)
{
    int ke = 1,n2,f;
    char c;
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
            if (c == 10)
            {
                (*n1) = n2;
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

int round_up(const int a,const int b)
{
    int c = a / b;
    if (a != c * b)
    {
        c++;
    }
    return c;
}
