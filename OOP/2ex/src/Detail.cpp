#include "Detail.h"

// Реализация методов класса Detail

Detail::Detail() : name(""), type(DetailType::Original), assemblyInstructions("") {}

Detail::Detail(const std::string& name, DetailType type, const std::vector<int>& requiredDetails, const std::string& instructions)
    : name(name), type(type), requiredDetails(requiredDetails), assemblyInstructions(instructions) {}

Detail::Detail(const std::string& name) : name(name), type(DetailType::Original), assemblyInstructions("") {}

std::string Detail::getName() const { return name; }
DetailType Detail::getType() const { return type; }
std::vector<int> Detail::getRequiredDetails() const { return requiredDetails; }
std::string Detail::getAssemblyInstructions() const { return assemblyInstructions; }

void Detail::setName(const std::string& name) { this->name = name; }
void Detail::setType(DetailType type) { this->type = type; }
void Detail::setAssemblyInstructions(const std::string& instructions) { this->assemblyInstructions = instructions; }

void Detail::addRequiredDetail(int detailNumber) {
    requiredDetails.push_back(detailNumber);
}

std::unordered_map<int, int> Detail::getUniqueRequiredDetails() const {
    std::unordered_map<int, int> uniqueDetails;
    for (int number : requiredDetails) {
    uniqueDetails[number]++; // Увеличиваем счетчик для каждой детали
    }
    return uniqueDetails; // Возвращаем уникальные детали
}

std::strong_ordering Detail::operator<=>(const Detail& other) const {
    return name <=> other.name; // Сравнение только по имени
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Detail& detail) {
    os << "Detail Name: " << detail.name << "\n"
       << "Detail Type: " << static_cast<int>(detail.type) << "\n"
       << "Required Details: ";
    for (int number : detail.requiredDetails) {
        os << number << " "; // Выводим номера требуемых деталей
    }
    os << "\nAssembly Instructions: " << detail.assemblyInstructions << "\n"; // Выводим указания по сборке
    return os; // Возвращаем поток
}

// Оператор ввода
std::istream& operator>>(std::istream& is, Detail& detail) {
    bool isConsole = (&is == &std::cin); // Проверяем, является ли поток стандартным вводом (будем выводить пользовательские сообщения только если является)
    if (isConsole) std::cout << "Enter detail name: ";
    std::getline(is, detail.name); // Вводим наименование детали
    int type;
    if (isConsole) std::cout << "Enter detail type (0 - Original, 1 - Final, 2 - Intermediate): ";
    is >> type; // Вводим тип детали
    detail.type = static_cast<DetailType>(type); // Приводим к типу DetailType
    if (isConsole) std::cout << "Enter number of required details: ";
    int count;
    is >> count; // Вводим количество требуемых деталей
    detail.requiredDetails.clear(); // Очищаем вектор перед вводом
    for (int i = 0; i < count; ++i) {
        int number;
        if (isConsole) std::cout << "Enter required detail number: ";
        is >> number; // Вводим номер требуемой детали
        detail.requiredDetails.push_back(number); // Добавляем номер в вектор требуемых деталей
    }
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер перед вводом строки
    if (isConsole) std::cout << "Enter assembly instructions: ";
    std::getline(is, detail.assemblyInstructions); // Вводим указания по сборке
    return is; // Возвращаем поток
}
