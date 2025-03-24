#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "struct.h"
namespace lab1
{
int dial_str_to_xml(Dict_m *&exm)
{
    std::string name_rec;
    if(exm != nullptr)
    {
        delete_str(exm);
    }
    exm = create_rec();
    do
    {
        std::cout << "Введите название записи: ";
        std::getline(std::cin,name_rec);
    }while ((name_rec.length() == 0)&&(!std::cin.eof())&&(!std::cin.bad()));
    if (std::cin.bad())
    {
        delete_str(exm);
        throw std::runtime_error("Broken input");
    }  
    else if (std::cin.eof())
    {
        delete_str(exm);
        throw std::runtime_error("EOF");
    }
    create_XML_rec(exm, name_rec.c_str());
    return 0;
}
void out_str(Dict_m *exm)
{
    if(exm != nullptr)
    {
        std::cout << "Слово = " << exm->word <<std::endl << "Значение = " << exm->meaning << std::endl << "Ударная согласная = " << exm->emp << std::endl;
    }
    else
    {
        printf("Тут пусто((");
    }
}
}