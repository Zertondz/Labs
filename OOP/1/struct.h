#ifndef STRUCT_H
#define STRUCT_H
/// @brief основной namespace lab1
namespace lab1
{
    /// @brief структура словаря
    /// @param word слово длиной максимум 20 символов
    /// @param meaning значение слова
    /// @param emp номер ударной гласной
    typedef struct Dict_m
    {
        char *word;
        char *meaning;
        unsigned int emp;
    }Dict_m;
    /// @brief проверяет ввод на наличие только числа
    /// @param n1 сслылка на число введеное пользователем
    /// @return код ошибки
    /// @throws std::runtime_error("EOF") в случае конфа файла или ctrl-d
    /// @throws std::runtime_error("Broken input") в случае сломаного вывода
    int str_chint(int& n1);
    /// @brief создает структуру из пользовательского ввода
    /// @return экземпляр структуры
    /// @throws std::runtime_error("EOF") в случае конфа файла или ctrl-d
    /// @throws std::runtime_error("Broken input") в случае сломаног вывода
    Dict_m* create_rec();
    /// @brief создает XML запись в текстовом файле
    /// @param exm экземпляр структуры
    /// @param name_rec название записи
    /// @return код ошибки
    /// @throws std::runtime_error("EOF") в случае конфа файла или ctrl-d
    /// @throws std::runtime_error("Broken input") в случае сломаног вывода
    int create_XML_rec(Dict_m*& exm, const char * name_rec);
    /// @brief диалоговая функция для чтения строки из текстого файла и её обработки в экземпляр структуры
    /// @return экземпляр структуры
    /// @throws std::runtime_error("EOF") в случае конфа файла или ctrl-d
    /// @throws std::runtime_error("Broken input") в случае сломаног вывода
    Dict_m* create_struct_rec();
    /// @brief удаляет структуру и освобождает выделенную память 
    void delete_str(Dict_m *& exm);
    /// @brief диалоговая функция для создания XML записи в текстовом файле
    /// @param exm экземпляр структуры
    /// @return код ошибки
    /// @throws std::runtime_error("EOF") в случае конфа файла или ctrl-d
    /// @throws std::runtime_error("Broken input") в случае сломаног вывода
    int dial_str_to_xml(Dict_m *&exm);
    /// @brief проверяет xml запись и создает экземпляр структуры
    /// @param line экземпляр класса string - строка типа XML
    /// @return экземпляр структуры
    /// @throws std::runtime_error("Неправильный формат ввода!!!") в случае неправильного формата XML
    Dict_m* create_str(const std::string &line);
    /// @brief проверяет xml запись и создает экземпляр структуры
    /// @param line нуль-терминированная строка
    /// @return экземпляр структуры
    /// @throws std::runtime_error("Неправильный формат ввода!!!") в случае неправильного формата XML
    Dict_m* create_str(const char* line);
    /// @brief проверяет xml запись и создает экземпляр структуры
    /// @param line указатель на массив символов
    /// @param num количество символов в массиве
    /// @return экземпляр структуры
    /// @throws std::runtime_error("Неправильный формат ввода!!!") в случае неправильного формата XML
    Dict_m* create_str(const char* line, size_t num);
    /// @brief вывод структуры на экран
    void out_str(Dict_m *exm);
    Dict_m *strcr(const char *line);
}
#endif 