#include <iostream>
#include <algorithm>
#include <format>
int str_chint(int& n1)
{
    int ke = 1,n2 = 0;
    std::string c;
    while (ke !=0)
    {
        ke = 0;
        std::cin >> n2;        
        if (std::cin.bad())
        {
            throw std::runtime_error("Broken input");
        }  
        else if (std::cin.eof())
        {
            throw std::runtime_error("EOF");
        }
        else if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Enter an integer: ";
            ke = 1;
        }
        else
        {
            if(std::cin.peek() == '\n')
            {
                n1 = n2;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                return 1;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout << "Enter an integer: ";
                ke = 1;
            }
        }
    }
    return 1;
}