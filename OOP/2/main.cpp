#include "Vector.hpp"
#include "Word.hpp"
#include "Words.hpp"
#include "tools.hpp"
#include <iostream>
#include <algorithm>
int main()
{
    int flag = 0;
    std::string line("pinisi");
    Words mywords;
    Words mywords1;
    Words mywords2;
    Word word;
    Vector<Word> vec;
    Vector<Word> pop;
    try
    {
        
        while (1)
        {
            std::cout << "(1) Ввод слов\n"
                         "(2) Вывод слова\n"
                         "(3) Поиск слова и вывод его индекса\n"
                         "(4) Сортировка\n"
                         "(5) Проверка на наличие этой подстроки\n";
            str_chint(flag);
            switch (flag)
            {
            case 1:
                mywords1.insert_words(std::cin);
                std::cin >> mywords1;
                std::cin >> word;
                mywords = std::move(mywords1);
                mywords += word;
                break;
            case 2:
                mywords.print_words(std::cout);
                std::cout << mywords;
                break;
            case 3:
                std::getline(std::cin, line);
                word.set_word(line.c_str());
                std::cout << (*mywords.find_word(word))->get_word() << std::endl;
                break;
            case 4:
                mywords.sort_up();
                mywords.print_words(std::cout);
                break;
            case 5:
                mywords1 = mywords;
                std::getline(std::cin, line);
                pop = mywords.sub_let(line.c_str()[0]);
                break;
            default:
                break;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}