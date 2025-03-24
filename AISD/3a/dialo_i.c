#include <stdio.h>
#include <stdlib.h>
#include "matr_de.h"
#include "tools.h"
#include "dialo.h"
int entering_in_a_table(Table * table)
{
    Iterator ind;
    unsigned int key = 0, value = 0;
    if (str_chint(&key,3) == -1)
    {
        delete_all(table);
        printf("End!");
        return -1;
    }
    if (str_chint(&value,4) == -1)
    {
        delete_all(table);
        printf("End!");
        return -1;
    }
    ind = input_in_table(key, value, table);
    if (ind.ptr == 0)
    {
        printf("The table is full!\n");
    }
    return 0;
}
int deleting_all_items_by_key(Table *table)
{
    int error = 0;
    unsigned int key = 0;
    if (str_chint(&key, 3) == -1)
    {
        delete_all(table);
        printf("End!");
        return -1;
    }
    Iterator ind = search_bin_2_0_I(key, table, &error);
    if (error == -1)
    {
        printf("The element was not found!\n");
    }
    else if (table->csize == 0)
    {
        printf("The table is empty!\n");
    }
    else
    {
        ind = delete_key_elem(ind,table);
    }
    return 0;
}
int deleting_a_version_by_key(Table *table)
{
    int error = 0;
    unsigned int key = 0, release = 0;

    if (str_chint(&key, 3) == -1)
    {
        delete_all(table);
        printf("End!");
        return -1;
    }
    if (str_chint(&release, 5) == -1)
    {
        delete_all(table);
        printf("End!");
        return -1;
    }
    Iterator ind = search_bin_2_0_I(key, table, &error);
    if (error == -1)
    {
        printf("The element was not found!\n");
    }
    else if (table->csize == 0)
    {
        printf("The table is empty!\n");
    }
    else
    {
        ind = delete_key_elem_rel(ind,release,table);
        if (ind.ptr == 0)
        {
            printf("The element was not found!\n");
        }
    }
    return 0;
}
int search_by_key(Table * table)
{
    int error = 0;
    Iterator ind;
    unsigned int key = 0;
    if (str_chint(&key, 3) == -1)
    {
        delete_all(table);
        printf("End!");
        return -1;
    }
    ind = search_bin_2_0_I(key,table,&error);
    if (error != -1)
    {
        output_table_i(ind);
    }
    else
    {
        printf("The element was not found!\n");
        return 1;
    }
    return 0;
}
int search_by_key_and_release(Table *table)
{
    Table * copy_table = NULL;
    unsigned int key = 0, release = 0;
    if (str_chint(&key, 3) == -1)
    {
        delete_all(table);
        printf("End!");
        return -1;
    }
    if (str_chint(&release, 5) == -1)
    {
        delete_all(table);
        printf("End!");
        return -1;
    }
    copy_table = search_key_elem_rel(key,release,table);
    if(copy_table == NULL)
    {
        printf("The element was not found!\n");
        return 1;
    }
    output_table(copy_table);
    delete_all(copy_table);
    return 0;
}
int output_to_a_file(Table * table)
{
    char * fname = NULL;
    fname = readline12("Enter the file name\n");
    if (fname == NULL)
    {
        delete_all(table);
        printf("End!");
        return -1;
    }
    output_table_files(fname,table);
    free(fname);
    return 0;
}
int input_from_a_file(Table ** table)
{
    Table * copy_table = NULL;
    char * fname = NULL;
    fname = readline12("Enter the file name\n");
    if (fname == NULL)
    {
        delete_all((*table));
        printf("End!");
        return -1;
    }
    if (check_file(fname) == -1)
    {
        printf("Incorrect file format!!\n");
        free(fname);
        return 1;
    }
    copy_table = input_from_file(fname);
    if (copy_table != NULL)
    {
        delete_all((*table));
        (*table) = NULL;
        (*table) = copy_table;
        copy_table = NULL;
    }
    else
    {
        printf("Error in the file name\n");
    }
    free(fname);
    return 0;
}
int initialization(Table ** table)
{
    unsigned int size = 0;
    if (str_chint(&size, 2) == -1)
    {
        printf("End!");
        return -1;
    }
    if (size == 0)
    {
        printf("Enter a positive length!\n");
        return 1;
    }
    else
    {
        (*table) = initialization_table(size);
    }
    return 0;
}
int input_from_a_file_initial(Table ** table)
{
    char * fname = NULL;
    fname = readline12("Enter the file name\n");
    if (fname == NULL)
    {
        printf("End!");
        return -1;
    }
    if (check_file(fname) == -1)
    {
        free(fname);
        printf("Incorrect file format!!\n");
        return 1;
    }
    (*table) = input_from_file(fname);
    if ((*table) == NULL)
    {
        printf("Error in the file name\n");
        return 1;
    }
    free(fname);
    return 0;
}
