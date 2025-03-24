#include <stdio.h>
#include <stdlib.h>
#include "matr_de.h"
#include "tools.h"
#include "dialo.h"
int entering_in_a_table(Table ** table)
{
    char * key,* value;
    key = readline12("Enter the key: ");
    if (key == NULL)
    {
        delete_all((*table));
        printf("End!");
        return -1;
    }
    value = readline12("Enter the value: ");
    if (value == NULL)
    {
        delete_all((*table));
        printf("End!");
        return -1;
    }
    input_in_table(key, value, table);
    return 0;
}
int deleting_all_items_by_key(Table *table)
{
    int error = 0;
    char* key;
    key = readline12("Enter the key: ");
    if (key == NULL)
    {
        delete_all(table);
        printf("End!");
        return -1;
    }
    error = delete_key_elem(key,table);
    free(key);
    if (error == -1)
    {
        printf("The element was not found!\n");
    }
    else if (error == -2)
    {
        printf("The table is empty!\n");
    }
    return 0;
}
int deleting_a_version_by_key(Table *table)
{
    int error = 0;
    unsigned int release = 0;
    char * key;
    key = readline12("Enter the key: ");
    if (key == NULL)
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
    error = delete_key_elem_rel(key,release,table);
    free(key);
    if (error == -1)
    {
        printf("The element was not found!\n");
    }
    else if (error == -2)
    {
        printf("The table is empty!\n");
    }
    return 0;
}
int search_by_key(Table * table)
{
    Table * copy_table = NULL;
    char * key;
    key = readline12("Enter the key: ");
    if (key == NULL)
    {
        delete_all(table);
        printf("End!");
        return -1;
    }
    copy_table = search_key_elem(key,table);
    if(copy_table == NULL)
    {
        printf("The element was not found!\n");
        return 1;
    }
    output_table(copy_table);
    delete_all(copy_table);
    return 0;
}
int search_by_key_and_release(Table *table)
{
    char *key;
    Table * copy_table = NULL;
    unsigned int release = 0;
    key = readline12("Enter the key: ");
    if (key == NULL)
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
