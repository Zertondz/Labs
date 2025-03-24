#include "pric.h"
#include <fstream>
#include "AssemblyInstruction.h"
#include <string>
#include <sstream>
#include <istream>
AssemblyInstruction& create_instructtion()
{
    std::ifstream in_f;
    std::string line;
    in_f.open("instruct.txt");
    static AssemblyInstruction instruction;
    std::getline(in_f,line);
    in_f >> instruction;
    std::cout << instruction;
    return instruction;
}
void check_instr()
{
    std::string file_name("instruct.txt");
    std::string line;
    std::ifstream in_f;
    bool flag = false;
    in_f.open(file_name);
    do{
        std::getline(in_f, line);
        for(auto iter = line.begin(); iter != line.end(); ++iter)
        {
            if((*iter) == ' ')
            {
                flag  = true;
            }
        }
        if(!flag)
        {
            std::cout << line << std::endl;
        }
        flag = false;
    }while(!in_f.eof());
}
void now_instr()
{
    std::string file_name("instruct.txt");
    std::string line;
    std::string instr;
    std::ifstream in_f;
    std::stringstream flow;
    AssemblyInstruction instruction;
    std::cout << "Введите инструкцию: ";
    std::cin >> instr;
    bool flag1 = true, flag2 = false;
    in_f.open(file_name);
    do{
        std::getline(in_f, line);
        if((line != instr)&&(flag1 == true))
        {
            continue;
        }
        else if((line == instr)&&(flag1 == true))
        {
            flag1 = false;
            continue;
        }
        for(auto iter = line.begin(); iter != line.end(); ++iter)
        {
            if((*iter) == ' ')
            {
                flag2  = true;
                break;
            }
        }
        if(!flag2)
        {
            flow >> instruction;
            break;
        }
        else
        {
            flow << line << '\n';
        }
        flag2 = false;
    }while(!in_f.eof());
    if((!flag1)&&(in_f.eof()))
    {
        flow >> instruction;
    }
    std::cout << instruction.getAssemblyInstructions();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}