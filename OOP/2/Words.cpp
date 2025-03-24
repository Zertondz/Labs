#include "Words.hpp"
#include "tools.hpp"
#include "Vector.hpp"
#include <algorithm>
#include <cstring>
#include <iostream>

bool check_duplicate(const Vector<Word> words, const char * line)
{
    for(iterator_v<Word> iter = words.begin(); iter != words.end(); ++iter)
    {
        if(std::strcmp((*iter)->get_word(), line) == 0)
        {
            return false;
        }
    }
    return true;
}
bool check_duplicate(const char** words, int len_w, const char * line)
{
    for(int i = 0; i < len_w; i++)
    {
        if(std::strcmp(words[i], line) == 0)
        {
            return false;
        }
    }
    return true;
}
bool check_duplicate(const char** words, int len_w, const char * line, int ii)
{
    for(int i = 0; i < len_w; i++)
    {
        if(i != ii)
        {
            if(std::strcmp(words[i],line) == 0)
            {
                return false;
            }
        }
    }
    return true;
}
Vector<Word> Words::sub_let(const char letter)
{
    int len = 0;
    Vector<Word> res;
    if(!Words::_words_vec.is_empty())
    {
        for(iterator_v<Word> iter = Words::_words_vec.begin(); iter != Words::_words_vec.end(); ++iter)
        {
            if(((*iter)->get_word()[0] == letter)
            ||((*iter)->get_word()[0] - 32 == letter)
            ||((*iter)->get_word()[0] == letter - 32))
            {
                len++;
            }
        }
        for(iterator_v<Word> iter = Words::_words_vec.begin(); iter != Words::_words_vec.end(); ++iter)
        {
            if(((*iter)->get_word()[0] == letter)
            ||((*iter)->get_word()[0] - 32 == letter)
            ||((*iter)->get_word()[0] == letter - 32))
            {
                res.push(*(*iter));
            }
        }
    }
    return res;
}
Words::Words(): _words_vec(){}
const Vector<Word>& Words::get_wordsi()
{
    return Words::_words_vec;
}
Words::Words(Word& words)
{
    if(words.get_word() != nullptr)
    {
        Words::_words_vec.push(words);
    }
}
Words::Words(const int len, const char ** line)
{
    for(int i = 0;i < len;i++)
    {
        if(!check_duplicate(line, len, line[i], i))
        {
            throw std::runtime_error("Дубликат!!!\n");
        }
    }
    for(int i = 0; i < len; i++)
    {
        Words::_words_vec.push(Word(line[i]));
    }
}
Words::~Words()
{
    std::cout<< "Ад очищен" <<std::endl;
}
iterator_v<Word> Words::find_word(Word& word)
{
    for(iterator_v<Word> iter = Words::_words_vec.begin(); iter != Words::_words_vec.end(); ++iter)
    {
        if(strcmp((*iter)->get_word(), word.get_word()) == 0)
        {
            iterator_v<Word> iter_copy = iter;
            return iter_copy;
        }
    }
    return iterator_v<Word>();
}
void Words::print_words(std::ostream& stream)
{
    stream << _words_vec.get_cap() << std::endl;
    if(!_words_vec.is_empty())
    {
        for (auto& elem : _words_vec)
        {
            elem->print(stream);
        }
    }
    else
    {
        std::cout << "Тут пусто" << std::endl;
    }
}
void Words::insert_words(std::istream& stream)
{
    int len = 0;
    stream >> len;
    std::string line;
    char **new_world = new char*[len];
    for(int i = 0; i < len; i++)
    {
        std::getline(stream, line, '\n');
        if (stream.bad())
        {
            delete[] new_world;
            throw std::runtime_error("Broken input");
        }  
        else if (stream.eof())
        {
            delete[] new_world;
            throw std::runtime_error("EOF");
        }
        if(!check_duplicate(Words::get_wordsi(), line.c_str()))
        {
            for(int j = 0; j < i; j++)
            {
                delete[] new_world[j];
            }
            delete[] new_world;
            throw std::runtime_error("Дубликат!!!\n");
        }
        if(!check_duplicate((const char**)new_world, i, line.c_str()))
        {
            for(int j = 0; j < i; j++)
            {
                delete[] new_world[j];
            }
            delete[] new_world;
            throw std::runtime_error("Дубликат!!!\n");
        }
        new_world[i] = new char[line.length() + 1];
        std::copy_n(line.c_str(), line.length() + 1, new_world[i]);
    }
    for(int i = 0; i < len; i++)
    {
        Words::_words_vec.push(new_world[i]);
    }
    for(int i = 0; i < len; i++)
    {
        delete[] new_world[i];
    }
    delete[] new_world;
}

Words& operator +=(Words& th_words, Word& word)
{
    if(!check_duplicate(th_words.get_wordsi(), word.get_word()))
    {
        throw std::runtime_error("Дубликат!!!\n");
    }
    th_words._words_vec.push(word);
    return th_words;
}
Words& operator +=(Words& th_words1, Words const& th_words2)
{
    for(iterator_v<Word> iter = th_words2._words_vec.begin(); iter != th_words2._words_vec.end(); ++iter)
    {
        if(!check_duplicate(th_words1.get_wordsi(), (*iter)->get_word()))
        {
            throw std::runtime_error("Дубликат!!!\n");
        }
    }
    for(iterator_v<Word> iter = th_words2._words_vec.begin(); iter != th_words2._words_vec.end(); ++iter)
    {
        th_words1._words_vec.push(*(*iter));
    }
    return th_words1;
}
const Word& Words::operator [](int i) const
{
    return Words::_words_vec[i];
}
Words& Words::operator=(const Words& exm)
{
    Words::_words_vec.clean();
    for (iterator_v<Word> iter = exm._words_vec.begin(); iter != exm._words_vec.end(); ++iter)
    {
        Words::_words_vec.push(*(*iter));
    }
    return *this;
}
std::ostream& operator <<(std::ostream& stream, const Words& other)
{
    for(iterator_v<Word> iter = other._words_vec.begin(); iter != other._words_vec.end(); ++iter)
    {
        stream << (*iter)->get_word() << std::endl;
    }
    return stream;
}
std::istream& operator >>(std::istream& stream, Words& other)
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
    if(!check_duplicate(other.get_wordsi(), line.c_str()))
    {
        throw std::runtime_error("Дубликат!!!");
    }
    Word exp(line.c_str());
    other += exp;
    return stream;
}
bool compare_w(Word*& left, Word*& right)
{
    return std::strcmp(left->get_word(),right->get_word()) <= 0;
}
void Words::sort_up()
{
    std::sort(Words::_words_vec.begin(), Words::_words_vec.end(), compare_w);
}
Words::Words(const Words& words)
{
    for(iterator_v<Word> iter = words._words_vec.begin(); iter != words._words_vec.end(); ++iter)
    {
        Words::_words_vec.push(*(*iter));
    }
}
Words::Words(Words&& words)
{
    Words::_words_vec = std::move(words._words_vec);
}
Words& Words::operator=(Words&& exm)
{
    Words::_words_vec.clean();
    Words::_words_vec = std::move(exm._words_vec);
    return *this;
}