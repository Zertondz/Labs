#include <iostream>
#include <format>
#include <iomanip>
#include <fstream>
#include <string>
#include <regex>
#include "struct.h"
namespace lab1
{
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
Dict_m* create_rec()
{
    Dict_m* exm = nullptr;
    std::string word;
    std::string mean;
    char *word_ch = nullptr, *mean_ch = nullptr;
    do
    {
        std::cout << "Введите слово: ";
        std::getline(std::cin,word);
    }while (((word.length() == 0)||(word.length() > 20))&&(!std::cin.eof())&&(!std::cin.bad()));
    do
    {
        std::cout << "Введите значение: ";
        std::getline(std::cin,mean);
    }while((mean.length() == 0)&&(!std::cin.eof())&&(!std::cin.bad()));
    if (std::cin.bad())
    {
        throw std::runtime_error("Broken input");
    }  
    else if (std::cin.eof())
    {
        throw std::runtime_error("EOF");
    }
    int emp = 0;
    std::cout << "Введите номер ударной гласной: ";
    str_chint(emp);
    exm = new Dict_m;
    word_ch = new char[word.length() + 1];
    mean_ch = new char[mean.length() + 1];
    std::copy(word.begin(), word.end() + 1, word_ch);
    std::copy(mean.begin(), mean.end() + 1, mean_ch);
    exm->word = word_ch;
    exm->meaning = mean_ch;
    exm->emp = emp;
    return exm;
}
void delete_str(Dict_m *& exm)
{
    delete[] exm->word;
    delete[] exm->meaning;
    delete exm;
    exm = nullptr;
}
int create_XML_rec(Dict_m *&exm, const char * name_rec)
{
    std::ofstream fout;
    std::string filename;
    do
    {
        std::cout << "Ввидите название файла: ";
        std::getline(std::cin, filename);
    }while ((filename.length() == 0)&&(!std::cin.eof())&&(!std::cin.bad()));
    if (std::cin.bad())
    {
        throw std::runtime_error("Broken input");
    }  
    else if (std::cin.eof())
    {
        throw std::runtime_error("EOF");
    }
    fout.open(filename.data(), std::ios::app);
    if(!fout.is_open())
    {
        delete_str(exm);
        throw std::runtime_error("Такого файла не существует!!!");
    }
    fout << std::format("<{}><word>{}</word><meaning>{}</meaning><emphisis>{}</emphasis></{}>\n", name_rec,exm->word,exm->meaning,exm->emp, name_rec);
    fout.close();
    delete_str(exm);
    return 0;
}
Dict_m* create_struct_rec()
{
    std::string filename;
    std::string line;
    std::ifstream fin;
    int num = 0;
    Dict_m *exm = nullptr;
    do
    {
        std::cout << "Ввидите название файла: ";
        std::getline(std::cin, filename);
    }while ((filename.length() == 0)&&(!std::cin.eof())&&(!std::cin.bad()));
    if (std::cin.bad())
    {
        throw std::runtime_error("Broken input");
    }  
    else if (std::cin.eof())
    {
        throw std::runtime_error("EOF");
    }
    fin.open(filename.data(),std::ios::in);
    if(!fin.is_open())
    {
        throw std::runtime_error("Такого файла не существует!!!");
    }
    std::cout <<"Введите номер записи: ";
    str_chint(num);
    for (int i = 0;i < (num - 1);i++)
    {
        fin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    std::getline(fin,line);
    fin.close();
    exm = create_str(line.c_str(), line.length());
    return exm;
}
Dict_m* create_str(const std::string &line)
{
    char *word = nullptr, *mean = nullptr;
    std::smatch matches;   
    Dict_m *exm = nullptr;
    std::regex r("^<([a-zA-Z0-9]{1,20})><word>([a-zA-Z0-9]+)</word><meaning>([a-zA-Z0-9]+)</meaning><emphisis>([0-9]+)</emphasis></([a-zA-Z0-9]+)>$");
    if(std::regex_search(line,matches,r))
    {
        std::cout <<matches[1]<<std::endl;
        exm = new Dict_m;
        word = new char[matches[2].length() + 1];
        mean = new char[matches[3].length() + 1];
        std::copy(matches[2].first,matches[2].second,word);
        std::copy(matches[3].first,matches[3].second,mean);
        mean[matches[3].length()] = '\0';
        word[matches[2].length()] = '\0';
        exm->word = word;
        exm->meaning = mean;
        exm->emp = std::stoi(matches[4]);
    }
    else{
        throw std::runtime_error("Неправильный формат ввода!!!");
    }
    return exm;
}
Dict_m *strcr(const char *line)
{
    char *word = nullptr, *mean = nullptr;
    std::cmatch matches;
    Dict_m *exm = nullptr;
    std::regex r("^<([a-zA-Z0-9]{1,20})><word>([a-zA-Z0-9]+)</word><meaning>([a-zA-Z0-9]+)</meaning><emphisis>([0-9]+)</emphasis></([a-zA-Z0-9]+)>$");
    if(std::regex_search(line,matches,r))
    {
        if (matches[2].length() > 20)
        {
            throw std::runtime_error("Неправильный формат ввода!!!");
        }
        std::cout <<matches[1]<<std::endl;
        exm = new Dict_m;
        word = new char[matches[2].length() + 1];
        mean = new char[matches[3].length() + 1];
        std::copy(matches[2].first,matches[2].second,word);
        std::copy(matches[3].first,matches[3].second,mean);
        mean[matches[3].length()] = '\0';
        word[matches[2].length()] = '\0';
        exm->word = word;
        exm->meaning = mean;
        exm->emp = std::stoi(matches[4]);
    }
    else{
        throw std::runtime_error("Неправильный формат ввода!!!");
    }
    return exm;
}
Dict_m* create_str(const char* line)
{
    return strcr(line);
}
Dict_m* create_str(const char* line, size_t num)
{
    if (line[num] == '\0')
    {
        std::cout << line << std::endl;
        return strcr(line);
    }
    else
    {
        char * new_line = new char[num + 1];
        std::copy_n(line, num, new_line);
        new_line[num] = '\0';
        std::cout << new_line << std::endl;
        return strcr(new_line);
    }
}
}