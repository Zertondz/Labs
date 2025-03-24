#include "huepph.h"
#include <stdio.h>
int round_up(const int a,const int b)
{
    int c = a / b;
    if (a != c * b)
    {
        c++;
    }
    return c;
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
