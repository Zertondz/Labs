#include "matr.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    while(1)
    {
        int flag = 0,t = 0,d_flag = 0;
        char * name;
        matrix* mass = NULL,*polin_mass = NULL;
        printf("Select the input option. From a file(1) or from the keyboard(2):\n");
        t = str_chint(&flag);
        if (t == -1) return -1;
        switch(flag)
        {
        case 1:
            name = readline12("Enter the name of the file where the data is read: ");
            if(name ==NULL){printf("The input is finished");return-1;}
            mass = read_matr(name);
            print_matrix(mass);
            polin_mass = idivid_task(mass);
            if (polin_mass == NULL){delete_all(mass);return-1;}
            print_matrix(polin_mass);
            delete_all(mass);
            delete_all(polin_mass);
            break;
        case 2:
            name = create_keyboard_matrix(&d_flag);
            if(name ==NULL){printf("The input is finished");return-1;}
            if(d_flag == -1){printf("The input is finished");return-1;}
            mass = read_matr(name);
            print_matrix(mass);
            polin_mass = idivid_task(mass);
            if (polin_mass == NULL){delete_all(mass);return-1;}
            print_matrix(polin_mass);
            delete_all(mass);
            delete_all(polin_mass);
            break;
        default:
            printf("Select another menu item\n");
        }
    }
}
