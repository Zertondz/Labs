#ifndef WORD_HPP
#define WORD_HPP
#include <iostream>
/*!
	\brief Класс слово
	\author Теляковский Дмитрий Сергеевич
	\version 1.0
	\date Окт 2024 года

	Этот класс нужен для работы со словом: позволяет их сравнивать, проверить начинается ли слово с заданной подстроки и приведение всех символо к нижнему регистру.
*/
class Word
{
private:
    char * _word; ///< Строка
    int _lenght; ///< Длина слова
public:
    /// @brief Пустой конструктор
    Word();
    /// @brief Конструктор с инициализацией строкой
    /// @param line Строка нуль-терминированная
    Word(const char * line);
    /// @brief Конструктор с инициализацией массивом символом и его количеством
    /// @param line Массив символов
    /// @param lenght Длина массива
    /// @throw std::runtime_error Если есть пробелы в строке
    /// @throw std::runtime_error Если строка пустая
    Word(const char * line, int lenght);
    /// @brief Копирующий конструктор
    /// @param word Ссылка на класс Word
    /// @throw std::runtime_error Если есть пробелы в строке
    /// @throw std::runtime_error Если строка пустая
    Word(const Word& word);
    /// @brief Перемещающий конструктор
    /// @param words Ссылка на rvalue класса Word
    Word(Word&& word);
    /// @brief Деструктор
    ~Word();
    /// @brief Вывод в поток слова
    void print(std::ostream& stream) const;
    /// @brief Ввод слова из потока
    void input(std::istream & stream);
    /// @brief Получение слова
    /// @return Указатель на слово
    /// @throw std::runtime_error В случае ctrl-d;
    /// @throw std::runtime_error В случае сломаного ввода;
    /// @throw std::runtime_error Если есть пробелы в строке
    /// @throw std::runtime_error Если строка пустая
    const char * get_word() const;
    /// @brief Получение длины
    /// @return длина слова
    int get_lenght();
    /// @brief Изменение слова
    /// @param line Строка
    void set_word(const char* line);
    /// @brief Изменение слова
    /// @param line Массив символов
    /// @param lenght Длина массива
    /// @throw std::runtime_error Если есть пробелы в строке
    /// @throw std::runtime_error Если строка пустая
    void set_word(const char* line, int lenght);
    /// @brief Оператор <=>
    /// @param other1 Ссылка на класс левого слова
    /// @param other2 Ссылка на класс правого слова
    /// @return 0 если равны, >0 левое больше, <0 правое больше
    /// @throw std::runtime_error Если есть пробелы в строке
    /// @throw std::runtime_error Если строка пустая
    friend int operator<=>(const Word& other1,const Word& other2);
    /// @brief Оператор <<
    /// @param stream Выходной поток
    /// @param exm Ссылка на класс Words
    friend std::ostream & operator <<(std::ostream & stream, Word & exm);
    /// @brief Оператор >>
    /// @param stream Входной поток
    /// @param exm Ссылка на класс Words
    /// @throw std::runtime_error В случае ctrl-d;
    /// @throw std::runtime_error В случае сломаного ввода;
    friend std::istream & operator >>(std::istream & stream, Word & exm);
    /// @brief Копирующий оператор =
    /// @param other Ссылка на класс слово
    Word& operator = (const Word& other);
    /// @brief Находится ли данная подстрока в слове
    /// @param line Искомая подстрока
    /// @return True или False
    bool chstr(const char* line);
    /// @brief Понижение регистра каждого слова
    /// @throw std::runtime_error Когда подстрока больше слова
    void lowwer_case();
};
#endif