#ifndef DETAIL_H
#define DETAIL_H

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <limits>
#include <compare>

/**
 * @enum DetailType
 * @brief Перечисление для типов деталей.
 */
enum class DetailType {
    Original,    ///< Исходная деталь
    Final,       ///< Финальная деталь
    Intermediate  ///< Промежуточная деталь
};

/**
 * @class Detail
 * @brief Класс, представляющий деталь.
 */
class Detail {
private:
    std::string name;                     ///< Наименование детали
    DetailType type;                       ///< Тип детали
    std::vector<int> requiredDetails;     ///< Номера требуемых деталей
    std::string assemblyInstructions;      ///< Указания по сборке

public:
    Detail();  ///< Пустой конструктор
    Detail(const std::string& name, DetailType type, const std::vector<int>& requiredDetails, const std::string& instructions); ///< Инициализирующий конструктор
    Detail(const std::string& name); ///< Инициализирующий конструктор для исходной детали

    std::string getName() const; ///< Получить наименование детали
    DetailType getType() const; ///< Получить тип детали
    std::vector<int> getRequiredDetails() const; ///< Получить требуемые детали
    std::string getAssemblyInstructions() const; ///< Получить указания по сборке

    void setName(const std::string& name); ///< Установить наименование детали
    void setType(DetailType type); ///< Установить тип детали
    void setAssemblyInstructions(const std::string& instructions); ///< Установить указания по сборке

    void addRequiredDetail(int detailNumber); ///< Добавить требуемую деталь
    std::unordered_map<int, int> getUniqueRequiredDetails() const; ///< Получить уникальные требуемые детали
    std::strong_ordering operator<=>(const Detail& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Detail& detail); ///< Оператор вывода
    friend std::istream& operator>>(std::istream& is, Detail& detail); ///< Оператор ввода
};

#endif // DETAIL_H
