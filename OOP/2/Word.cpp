#include "Word.hpp"
#include <iostream>
#include <algorithm> 
#include <cstring>
#include <compare>

void Word::lowwer_case()
{
    for(int i = 0;i < Word::_lenght; i++)
    {
        if(Word::_word[i] < 'a')
        {
            Word::_word[i] = Word::_word[i] + 32;
        }
    }
}
Word::Word(const Word& word)
{
    if(word._word != nullptr)
    {
        Word::_word = new char[word._lenght + 1];
        Word::_lenght = word._lenght;
        std::copy_n(word.get_word(), word._lenght + 1, Word::_word);
    }
    else
    {
        Word::_word = nullptr;
        Word::_lenght = 0;
    }
}
Word::Word(Word&& word)
{
    if(word._word != nullptr)
    {
        Word::_word = word._word;
        Word::_lenght = word._lenght;
        word._word = nullptr;
    }
    else
    {
        Word::_word = nullptr;
        Word::_lenght = 0;
    }
}
bool Word::chstr(const char* line)
{
    if(Word::_lenght < (int)std::strlen(line))
    {
        throw std::runtime_error("Подстрока больше слова!!!");
    }
    for(int i = 0;i < (int)std::strlen(line);i++)
    {
        if(Word::_word[i] != line[i])
        {
            return false;
        }
    }
    return true;
}
int operator<=>(const Word& other1,const Word& other2) 
{
    return std::strcmp(other1.get_word(), other2.get_word());
}
Word& Word::operator = (const Word& other)
{
    if(Word::_word != nullptr)
    {
        delete[] Word::_word;
    }
    Word::_word = new char[other._lenght + 1];
    Word::_lenght = other._lenght;
    std::copy_n(other.get_word(), other._lenght + 1, Word::_word);
    return *this;
}
std::ostream & operator <<(std::ostream & stream, Word & exm)
{
    stream << exm.get_word() << std::endl;
    return stream;
}
std::istream & operator >>(std::istream & stream, Word & exm)
{
    std::string line;
    std::getline(stream, line);
    if (stream.bad())
    {
        throw std::runtime_error("Broken input");
    }  
    else if (stream.eof())
    {
        throw std::runtime_error("EOF");
    }
    Word exp(line.c_str());
    exm = exp;
    return stream;
}
Word::Word()
{
    Word::_word = nullptr;
    Word::_lenght = 0;
}
Word::Word(const char * line)
{
    int i = 0;
    if(line != nullptr)
    {
        while(1)
        {
            if(line[i] == ' ')
            {
                throw std::runtime_error("В строке пробелы!!");
            }
            if(line[i] == '\0')
            {
                break;
            }
            i++;
        }
        Word::_word = new char[i + 1];
        Word::_lenght = i;
        std::copy_n(line,i + 1,Word::_word);
    }
    else
    {
        throw std::runtime_error("Пустая строка!!!");
    }
}
Word::Word(const char * line, int lenght)
{
    if(line != nullptr)
    {
        for (int i = 0; i < lenght; i++)
        {
            if(line[i] == ' ')
            {
                throw std::runtime_error("В строке пробелы!!");
            }
        }
        Word::_word = new char[lenght + 1];
        std::copy_n(line, lenght, Word::_word);
        Word::_word[lenght] = '\0';
        Word::_lenght = lenght;
    }
    else
    {
        throw std::runtime_error("Пустая строка!!!");
    }
}
void Word::print(std::ostream& stream) const 
{
    stream << Word::_word << std::endl;
}
const char * Word::get_word() const
{
    return Word::_word;
}
int Word::get_lenght()
{
    return Word::_lenght;
}
void Word::set_word(const char* line)
{
    int i = 0;
    if(line != nullptr)
    {
        while(1)
        {
            if(line[i] == ' ')
            {
                throw std::runtime_error("В строке пробелы!!");
            }
            if(line[i] == '\0')
            {
                break;
            }
            i++;
        }
        if(Word::_word != nullptr)
        {
            delete[] Word::_word;
        }
        Word::_word = new char[i + 1];
        Word::_lenght = i;
        std::copy_n(line, i + 1, Word::_word);
    }
    else
    {
        throw std::runtime_error("Пустая строка!!!");
    }
}
void Word::set_word(const char* line, int lenght)
{
    if(line != nullptr)
    {
        for (int i = 0; i < lenght; i++)
        {
            if(line[i] == ' ')
            {
                throw std::runtime_error("В строке пробелы!!");
            }
        }
        if(Word::_word != nullptr)
        {
            delete[] Word::_word;
        }
        Word::_word = new char[lenght + 1];
        std::copy_n(line, lenght, Word::_word);
        Word::_word[lenght] = '\0';
    }
    else
    {
        throw std::runtime_error("Пустая строка!!!");
    }
}
Word::~Word()
{
    if(Word::_word != nullptr)
    {
        delete[] Word::_word;
        Word::_word = nullptr;
    }
}
void Word::input(std::istream & stream)
{
    std::string word;
    do
    {
        std::getline(stream, word);
    }while ((word.length() == 0)&&(!std::cin.eof())&&(!std::cin.bad()));
    if (std::cin.bad())
    {
        throw std::runtime_error("Broken input");
    }  
    else if (std::cin.eof())
    {
        throw std::runtime_error("EOF");
    }
    Word::set_word(word.c_str());
}
