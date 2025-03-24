#include "matr.h"
#include <stdio.h>
#include <stdlib.h>
void delete_all(matrix* matr_del)
{
    free(matr_del->matr);
    free(matr_del->name_f);
    free(matr_del);
}
void print_matrix(const matrix* matr)
{
    int count_line = matr->lines;
    FILE*file = fopen(matr->name_f,"rb+");
    printf("----------------------------\n");
    for(int i = 0;i < count_line;i++)
    {
        int local_offset = matr->matr[i].offset,amount_elem = matr->matr[i].n;
        fseek(file,local_offset * sizeof(int),SEEK_SET);
        printf("%d:",i);
        for(int j = 0;j < amount_elem;j++)
        {
            int elem = 0;
            fread(&elem,sizeof(int),1,file);
            printf("[%d]",elem);
        }
        printf("\n");
    }
    printf("----------------------------\n");
    fclose(file);
}
matrix * idivid_task(matrix* individ_matr)
{
    int count_lines_in_my_matrix = 0,count_elem_mem = 0,offset = 0;
    FILE * file = fopen(individ_matr->name_f,"rb+"),* file_out = NULL;
    matrix * my_matr = (matrix*)calloc(1,sizeof(matrix));
    for (int i = 0;i < (individ_matr->lines);i++)
    {
        int count_elem = (individ_matr->matr)[i].n,flag = 1;
        for (int j = 0;j < round_up(count_elem,2);j++)
        {
            int local_offset = individ_matr->matr[i].offset,lower_g = 0,upper_g = 0;
            fseek(file,local_offset * sizeof(int),SEEK_SET);
            local_offset+=j;
            fseek(file,local_offset*sizeof(int),SEEK_SET);
            fread(&lower_g,sizeof(int),1,file);
            local_offset = (local_offset - j)+(count_elem-1-j);
            fseek(file,local_offset*sizeof(int),SEEK_SET);
            fread(&upper_g,sizeof(int),1,file);
            if (lower_g != upper_g)
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
            (my_matr->matr)[count_lines_in_my_matrix].offset = individ_matr->matr[i].offset;
            count_lines_in_my_matrix++;
        }
    }
    my_matr->lines = count_lines_in_my_matrix;
    my_matr->name_f = readline12("Enter the name of the output file: ");
    if (my_matr->name_f == NULL){delete_all(my_matr);fclose(file);return NULL;}
    file_out = fopen(my_matr->name_f,"wb+");
    fwrite(&(my_matr->lines) ,sizeof(int),1,file_out);
    offset = (1+2*(my_matr->lines));
    for (int i = 0;i < my_matr->lines;i++)
    {
        int count_elem = 0;
        count_elem = my_matr->matr[i].n;
        fwrite(&count_elem,sizeof(int),1,file_out);
        offset+=count_elem_mem;

        fwrite(&offset,sizeof(int),1,file_out);
        count_elem_mem = count_elem;
    }
    for(int i = 0;i < my_matr->lines;i++)
    {
        int count_elem = 0;
        fseek(file,sizeof(int)*(my_matr->matr[i].offset),SEEK_SET);
        for (int j = 0;j < my_matr->matr[i].n;j++)
        {
            fread(&count_elem,sizeof(int),1,file);
            fwrite(&count_elem,sizeof(int),1,file_out);
        }
    }
    fseek(file_out,sizeof(int),SEEK_SET);
    for (int i = 0;i < my_matr->lines;i++)
    {
        int count_elem = 0;
        fread(&count_elem,sizeof(int),1,file_out);
        fread(&offset,sizeof(int),1,file_out);
        my_matr->matr[i].offset = offset;
    }
    fclose(file);
    fclose(file_out);
    return my_matr;
}
matrix* read_matr(char * name)
{
    FILE * file = fopen(name,"rb+");
    matrix *mass = (matrix*)calloc(1,sizeof(matrix));
    fread(&(mass->lines),sizeof(int),1,file);
    mass->matr = (line*)calloc(mass->lines,sizeof(line));
    for(int i = 0;i < mass->lines;i++)
    {
        int data_1;
        fread(&(data_1),sizeof(int),1,file);
        mass->matr[i].n = data_1;
        fread(&(data_1),sizeof(int),1,file);
        mass->matr[i].offset = data_1;
    }
    fclose(file);
    mass->name_f = name;
    return mass;
}

char * create_keyboard_matrix(int * d)
{
    int count_line = 0,g = 0,count_elem_mem = 0,offset = 0;
    char *name = readline12("Enter the name of the file where the data is saved (Attention erases data if a file with the same name exists!!!): ");
    if (name == NULL)return NULL;
    FILE * file = fopen(name,"wb+");
    printf("Inter count of lines(To exit, enter ctrl+d/z): ");
    while(1)
    {
        g = str_chint(&count_line);
        if (g == -1){(*d) = -1;fclose(file);free(name);return NULL;}
        else if (count_line <= 0){printf("Input error\n");continue;}
        break;
    }
    fwrite(&count_line ,sizeof(int),1,file);
    offset = (1+2*(count_line));
    for (int i = 0;i < count_line;i++)
    {
        int count_elem = 0;
        printf("Inter count of element: ");
        while(1)
        {
            g = str_chint(&count_elem);
            if (g == -1) {(*d) = -1;fclose(file);free(name);return NULL;}
            else if(count_elem <= 0){printf("Input error\n");continue;}
            break;
        }
        fwrite(&count_elem,sizeof(int),1,file);
        offset+=count_elem_mem;
        fwrite(&offset,sizeof(int),1,file);
        count_elem_mem = count_elem;
    }
    for(int i = 0;i < count_line;i++)
    {
        int count_elem = 0;
        fseek(file,sizeof(int)*(1+2*i),SEEK_SET);
        fread(&count_elem,sizeof(int),1,file);
        fseek(file,sizeof(int)*(2+2*i),SEEK_SET);
        fread(&offset,sizeof(int),1,file);
        fseek(file,sizeof(int)*offset,SEEK_SET);
        printf("[%d] line:\n",i);
        for (int j = 0;j < count_elem;j++)
        {
            int b = 0;
            while(1)
            {
                g = str_chint(&b);
                if (g == -1){(*d) = -1;fclose(file);free(name);return NULL;}
                break;
            }
            fwrite(&b,sizeof(int),1,file);
        }
    }
    fclose(file);
    return name;
}
