#include <stdio.h>
#include <stdlib.h>
#include "matr_de.h"
#include "tools.h"
#include "dialo.h"
int main()
{
    int error = 0;
    unsigned int option = 0,a = 0,b = 0;
    Table * table = NULL;
    while (table == NULL)
    {
        if (str_chint(&option,6) == -1)
        {
            printf("End!");
            return -1;
        }
        switch(option)
        {
        case 1:
            error = initialization(&table);
            if (error == -1)
            {
                return -1;
            }
            break;
        case 2:
            error = input_from_a_file_initial(&table);
            if (error == -1)
            {
                return -1;
            }
            break;
        default:
            printf("Select another item!\n");
        }
    }
    while(str_chint(&option, 1) != -1)
    {
        switch (option)
        {
        case 1:
            error = entering_in_a_table(&table);
            if (error == -1)
            {
                return -1;
            }
            break;
        case 2:
            output_table(table);
            break;
        case 3:
            error = deleting_all_items_by_key(table);
            if (error == -1)
            {
                return -1;
            }
            break;
        case 4:
            error = deleting_a_version_by_key(table);
            if (error == -1)
            {
                return -1;
            }
            break;
        case 5:
            error = search_by_key(table);
            if (error == -1)
            {
                return -1;
            }
            else if (error == 1)
            {
                break;
            }
            break;
        case 6:
            error = search_by_key_and_release(table);
            if (error == -1)
            {
                return -1;
            }
            else if (error == 1)
            {
                break;
            }
            break;
        case 7:
            error = output_to_a_file(table);
            if (error == -1)
            {
                return -1;
            }
            break;
        case 8:
            error = input_from_a_file(&table);
            if (error == -1)
            {
                return -1;
            }
            else if (error == 1)
            {
                break;
            }
            break;
        case 9:
            table = expend_table(table);
            break;
        case 10:
            str_chint(&a,4);
            str_chint(&b,4);
            printf("===%d\n",NOD(a,b));
            break;
        default:
            printf("Select another item!\n");
        }
    }
    if (table != NULL)
    {
        delete_all(table);
    }
    return 0;
}
