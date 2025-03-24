#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include "struct.h"
using namespace lab1;
int main()
{
    setlocale(LC_ALL, "Russian");
    Dict_m* exm = nullptr;
    int flag = 0;
    try
    {
        while(1)
        {
            try
            {
                std::cout << "(1) Создание записи в словарь" << std::endl << "(2) Считать запись из XML файла" << std::endl << "(3) Вывод структуры в памяти" << std::endl << "Введите номер: ";
                if(str_chint(flag) == -1)
                {
                    if(exm != nullptr)
                    {
                        delete_str(exm);
                    }
                    return -1;
                }
                switch (flag)
                {
                    case 1:
                        dial_str_to_xml(exm);
                        break;
                    case 2:
                        if (exm != nullptr)
                        {
                            delete_str(exm);
                        }
                        exm = create_struct_rec();
                        break;
                    case 3:
                        out_str(exm);
                        break;
                    default:
                        printf("Нет такого пункта!!!\n");
                        break;
                }
            }
            catch(std::runtime_error& e)
            {
                std::cout<< "exceptini " << e.what() <<std::endl;
                if(std::strcmp(e.what(), "EOF") == 0)
                {
                    if(exm != nullptr)
                    {
                        delete_str(exm);
                    }
                    return 0;
                }
            }
        }
    }
    catch(std::exception& e)
    {
        std::cout<<e.what()<<std::endl;    
        if(exm != nullptr)
        {
            delete_str(exm);
        }
    }
    return 0;
}