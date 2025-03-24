#include "huepph.h"
#include <stdio.h>
#include <stdlib.h>
matrix* create_matrix()
{
    int count_line = 0,g = 0;
    printf("Inter count of lines(To exit, enter ctrl+d/z): ");
    g = str_chint(&count_line);
    if (g == -1)return (matrix*)-1;
    else if (count_line <= 0)return NULL;
    matrix * my_matr = (matrix*)malloc(sizeof(matrix));
    my_matr->lines = count_line;
    my_matr->matr = (line*)malloc(count_line*sizeof(line));
    for (int i = 0;i < count_line;i++)
    {
        int count_elem = 0;
        printf("Inter count of element: ");
        g = str_chint(&count_elem);
        if (g == -1){delete_matrix_i(my_matr,i);return (matrix*)-1;}
        else if(count_elem <= 0){delete_matrix_i(my_matr,i);return NULL;}
        (my_matr->matr)[i].n = count_elem;
        (my_matr->matr)[i].a = (int*)malloc(sizeof(int)*count_elem);
        for (int j = 0;j < count_elem;j++)
        {
            int b = 0;
            g = str_chint(&b);
            if (g == -1){delete_matrix_i(my_matr,i + 1);return NULL;}
            ((my_matr->matr)[i].a)[j] = b;
        }
    }
    return my_matr;
}
void print_matrix(const matrix* matr)
{
    int count_line = matr->lines;
    for(int i = 0;i < count_line;i++)
    {
        int count_elem = (matr->matr)[i].n;
        printf("%d: ",i);
        for (int j = 0;j< count_elem;j++)
        {
            printf("[%d] ",((matr->matr)[i].a)[j]);
        }
        printf("\n");
    }
}
void delete_matrix(matrix* matr_del)
{
    int count_line = matr_del->lines;
    for (int i = 0;i < count_line;i++)
    {
        free((matr_del->matr)[i].a);
    }
    free(matr_del->matr);
    free(matr_del);
}
void delete_matrix_i(matrix* matr_del,int elem)
{
    for (int i = 0;i < elem;i++)
    {
        free((matr_del->matr)[i].a);
    }
    free(matr_del->matr);
    free(matr_del);
}
