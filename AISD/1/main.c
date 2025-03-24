#include "huepph.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    while(1)
    {
        matrix* my_matr = create_matrix(),*individ_matrix = NULL;
        if (my_matr == (matrix*)-1){printf("The input is finished!!!\n");break;}
        else if (my_matr == NULL){printf("Error!!!\n");continue;}
        print_matrix(my_matr);
        individ_matrix = idivid_task(my_matr);
        printf("Polindrome matrix: \n");
        print_matrix(individ_matrix);
        delete_matrix(my_matr);
        delete_matrix(individ_matrix);
    }
    return 0;
}
matrix * idivid_task(matrix* individ_matr)
{
    int count_lines_in_my_matrix = 0;
    matrix * my_matr = (matrix*)malloc(sizeof(matrix));
    for (int i = 0;i < (individ_matr->lines);i++)
    {
        int count_elem = (individ_matr->matr)[i].n,flag = 1;
        for (int j = 0;j < round_up(count_elem,2);j++)
        {
            if (((individ_matr->matr)[i].a)[j] != ((individ_matr->matr)[i].a)[count_elem-j-1])
            {
                flag = 0;
                break;
            }
        }
        if(flag == 1)
        {
            if(count_lines_in_my_matrix == 0)
            {
                my_matr->matr = (line*)malloc((count_lines_in_my_matrix+1)*sizeof(line));
            }
            else
            {
                my_matr->matr = realloc(my_matr->matr,(count_lines_in_my_matrix+1)*sizeof(line));
            }
            (my_matr->matr)[count_lines_in_my_matrix].n = count_elem ;
            (my_matr->matr)[count_lines_in_my_matrix].a = (int*)malloc(sizeof(double)*count_elem);
            for (int j = 0;j < count_elem;j++)
            {
                ((my_matr->matr)[count_lines_in_my_matrix].a)[j] = ((individ_matr->matr)[i].a)[j];
            }
            count_lines_in_my_matrix++;
        }
    }
    my_matr->lines = count_lines_in_my_matrix;
    return my_matr;
}
