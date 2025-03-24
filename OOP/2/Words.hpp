#ifndef WORDS_HPP
#define WORDS_HPP
#include "Word.hpp"
#include <ostream>
#include "Vector.hpp"
/*!
	\brief Класс слов
	\author Теляковский Дмитрий Сергеевич
	\version 3.0
	\date Окт 2024 года

	Этот класс нужен для работы со словами: позволяет их сортировать, искать нужные слова, выделять подмножество слов на заданную букву.
*/
class Words
{
private:
    Vector<Word> _words_vec; ///< Шаблонный класс вектор где хранятится массив слов(Экзепляров класса слово)
public:
    /// @brief Пустой конструктор
    Words();
    /// @brief Конструктор с инициализацией классом слово
    /// @param word Сылка на класс Word
    Words(Word& word);
    /// @brief Конструктор с инициализацией количеством слов и их массивом
    /// @param len Количество слов
    /// @param line Массив слов
    Words(const int len, const char** line);
    /// @brief Копирующий конструктор
    /// @param words Ссылка на класс Words
    Words(const Words& words);
    /// @brief Перемещающий конструктор
    /// @param words Ссылка на rvalue класса Words
    Words(Words&& words);
    /// @brief Получение массива слов
    /// @return Ссылка на класс вектор со словами
    const Vector<Word>& get_wordsi();
    /// @brief Вывод слов на экран
    void print_words(std::ostream& stream);
    /// @brief Ввод слов из входного потока
    void insert_words(std::istream& stream);
    /// @brief Получение подмножество слов на заданную букву
    /// @param letter Буква по которой происходит поиск
    /// @throw std::runtime_error В случае дубликата;
    /// @throw std::runtime_error В случае ctrl-d;
    /// @throw std::runtime_error В случае сломаного ввода;
    /// @return Экземпляр класса вектор со словами
    Vector<Word> sub_let(const char letter);
    /// @brief Поиск слова и возврат его индекса
    /// @param word Ссылка на класс Word
    /// @return Возврат итератора, в случае отсутствии слова возврат пустого итератора
    iterator_v<Word> find_word(Word& word);
    /// @brief Деструктор
    ~Words();
    /// @brief Оператор +=
    /// @param th_words Ссылка на класс Words
    /// @param word Ссылка на класс Word
    friend Words& operator +=(Words& th_words, Word& word);
    /// @brief Оператор +=
    /// @param th_words1 Ссылка на класс Words
    /// @param th_words1 Ссылка на класс Words
    friend Words& operator +=(Words& th_words1, Words const& th_words2);
    /// @brief Копирующий оператор =
    /// @param exm Ссылка на класс Words
    Words& operator=(const Words& exm);
    /// @brief Перемещающий оператор =
    /// @param exm Ссылка rvalue класса Words
    Words& operator=(Words&& exm);
    /// @brief Оператор <<
    /// @param stream Выходной поток
    /// @param other Ссылка на класс Words
    friend std::ostream& operator <<(std::ostream& stream, const Words& other);
    /// @brief Оператор >>
    /// @param stream Входной поток
    /// @throw std::runtime_error В случае дубликата;
    /// @throw std::runtime_error В случае ctrl-d;
    /// @throw std::runtime_error В случае сломаного ввода;
    /// @param other Ссылка на класс Words
    friend std::istream& operator >>(std::istream& stream, Words& other);
    /// @brief Оператор []
    /// @param i Номер слова от 0 до n - 1, где n количество слов
    const Word& operator [](int i) const;
    /// @brief Сортировка в лексикографическом порядке
    void sort_up();
};
#endif