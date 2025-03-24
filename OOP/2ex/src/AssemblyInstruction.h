#ifndef ASSEMBLY_INSTRUCTION_H
#define ASSEMBLY_INSTRUCTION_H

#include <iostream>
#include "Detail.h"

class AssemblyInstruction {
private:
    Detail* details;    // Динамический массив деталей
    int detailCount;    // Текущее количество деталей
    int capacity;       // Емкость массива

    // Метод для изменения размера массива
    void resize(int newCapacity);
    // Вспомогательный метод для проверки циклов при сборке
    bool hasCycle(int detailIndex, std::vector<bool>& visited, std::vector<bool>& recursionStack) const;
    // Вспомогательный метод для проверки корректности последовательности сборки
    bool isValidSequence(const std::vector<Detail>& sequence) const;

public:
    // Конструктор по умолчанию
    AssemblyInstruction();

    // Конструктор с массивом деталей
    AssemblyInstruction(const Detail* detailArray, int count);

    // Копирующий конструктор
    AssemblyInstruction(const AssemblyInstruction& other);

    // Перемещающий конструктор
    AssemblyInstruction(AssemblyInstruction&& other) noexcept;

    // Оператор присваивания с перемещением
    AssemblyInstruction& operator=(AssemblyInstruction&& other) noexcept;

    // Деструктор
    ~AssemblyInstruction();

    // Метод для добавления новой детали
    AssemblyInstruction& operator+=(const Detail& detail);

    // Оператор доступа по индексу
    Detail& operator[](int index);

    // Метод для удаления детали
    void removeDetail(int index);

    // Метод для получения количества деталей
    int getDetailCount() const;

    // Проверка возможности сборки финальной детали
    bool canAssembleFinalDetail() const;
    
    // Получение отсортированного списка исходных деталей
    std::vector<std::string> getOriginalDetailsSorted() const;

    // Получение вектора деталей в порядке их сборки
    std::vector<Detail> getAssemblySequence() const;

    // Метод для получения пошаговой инструкции сборки
    std::string getAssemblyInstructions() const;

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const AssemblyInstruction& instruction);

    // Оператор ввода
    friend std::istream& operator>>(std::istream& is, AssemblyInstruction& instruction);
};

#endif // ASSEMBLY_INSTRUCTION_H