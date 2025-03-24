#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "iterator_v.hpp"
#include <string>
/*!
    \class Vector
    \brief Шаблонный класс динамического массива.

    Обеспечивает функциональность для работы с динамическими массивами, включая добавление, удаление, изменение размера и итерацию.
    Реализует семантику копирования и перемещения.
    \tparam T Тип данных, которые будут храниться в контейнере.
*/
template <typename T>
class Vector
{
private:
    /*!
        \brief Указатель на динамический массив элементов.
    */
    T * _vector;

    /*!
        \brief Текущее количество элементов в массиве.
        \details Хранит число реально добавленных элементов.
    */
    mutable int _capaсity;

    /*!
        \brief Размер выделенной памяти для массива.
    */
    int _size;

    /*!
        \brief Расширяет массив при необходимости.
        \details Удваивает размер массива для обеспечения роста.
    */
    void expand();

public:
    /*!
        \brief Конструктор по умолчанию.
        \details Инициализирует массив с минимально возможным размером.
    */
    Vector();

    /*!
        \brief Конструктор копирования.
        \param exm Константная ссылка на объект, который нужно скопировать.
    */
    Vector(const Vector<T> & exm);

    /*!
        \brief Деструктор.
        \details Освобождает память, выделенную под массив.
    */
    ~Vector();

    /*!
        \brief Итератор на начало массива.
        \return Итератор, указывающий на первый элемент массива.
    */
    iterator_v<T> begin() const;

    /*!
        \brief Итератор на конец массива.
        \return Итератор, указывающий на элемент за последним.
    */
    iterator_v<T> end() const;

    /*!
        \brief Получает количество элементов в массиве.
        \return Число добавленных элементов.
    */
    size_t size() const;

    /*!
        \brief Добавляет элемент в конец массива.
        \param exm Константная ссылка на добавляемый элемент.
    */
    void push_back(const T& exm);

    /*!
        \brief Изменяет размер массива.
        \param new_capacity Новый размер массива.
        \details Если новый размер больше текущего, выделяется дополнительная память.
                 Если меньше — массив усекается.
    */
    void resize(int new_capacity);

    /*!
        \brief Очищает массив.
        \details Устанавливает значения всех элементов по умолчанию.
    */
    void clean();

    /*!
        \brief Оператор доступа к элементу по индексу.
        \param i Индекс элемента.
        \return Ссылка на элемент по индексу.
        \throw std::out_of_range Если индекс выходит за границы массива.
    */
    T& operator [](int i) const;

    /*!
        \brief Оператор присваивания перемещения.
        \param other Rvalue-ссылка на другой объект.
        \return Ссылка на текущий объект.
    */
    Vector<T>& operator =(Vector<T>&& other);

    /*!
        \brief Оператор присваивания копирования.
        \param other Константная ссылка на другой объект.
        \return Ссылка на текущий объект.
    */
    Vector<T>& operator =(const Vector<T>& other);

    /*!
        \brief Проверяет, пуст ли массив.
        \return true, если массив пуст; false в противном случае.
    */
    bool is_empty();
};

template <typename T>
void Vector<T>::resize(int new_capacity)
{
    if(new_capacity > _capaсity)
    {
        T * copy = new T [new_capacity * 2];
        int i = 0;
        for(iterator_v<T> iter = Vector<T>::begin(); iter != Vector<T>::end(); ++iter, i++)
        {
            copy[i] = T(*iter);
        }
        for(int j = i; j <= (new_capacity-1); j++)
        {
            copy[j] = T();
        }
        Vector<T>::clean();
        delete[] Vector<T>::_vector;
        Vector<T>::_vector = copy;
        Vector<T>::_capaсity = new_capacity;
        Vector<T>::_size = new_capacity * 2;
    }
    else if(new_capacity < _capaсity)
    {
        T * copy = new T [new_capacity * 2];
        int i = 0;
        for(iterator_v<T> iter = Vector<T>::begin(); iter !=Vector<T>::end(); ++iter, i++)
        {
            if(i < new_capacity)
            {
                copy[i] = T(*iter);
            }
        }
        delete[] Vector<T>::_vector;
        Vector<T>::_vector = copy;
        Vector<T>::_capaсity = new_capacity;
        Vector<T>::_size = new_capacity * 2;
    }
}
template <typename T>
iterator_v<T> Vector<T>::begin() const
{
    return iterator_v<T>(Vector<T>::_vector, 0, Vector<T>::_size);
}
template <typename T>
size_t Vector<T>::size() const
{
    return Vector<T>::_capaсity;
}
template <typename T>
iterator_v<T> Vector<T>::end() const
{
    return iterator_v<T>(Vector<T>::_vector, Vector<T>::_capaсity, Vector<T>::_size);
}
template <typename T>
Vector<T>::Vector(const Vector<T> & exm)
{
    Vector<T>::_vector = new T [exm.size() * 2];
    int i = 0;
    for(iterator_v<T> iter = exm.begin(); iter != exm.end(); ++iter, i++)
    {
        Vector<T>::_vector[i] = T(*iter);
    }
    Vector<T>::_size = exm.size() * 2;
    Vector<T>::_capaсity = exm.size();
}
template <typename T>
Vector<T>& Vector<T>::operator =(const Vector<T>& other)
{
    delete[] Vector<T>::_vector;
    Vector<T>::_vector = new T [other.size() * 2];
    int i = 0;
    for(iterator_v<T> iter = other.begin(); iter != other.end(); ++iter, i++)
    {
        _vector[i] = (*iter);
    }
    _capaсity = other.size();
    _size = other.size() * 2;
    other._capaсity = 0;
    return (*this);
}
template <typename T>
Vector<T>& Vector<T>::operator = (Vector<T>&& other)
{
    delete[] Vector<T>::_vector;
    Vector<T>::_vector = new T [other.size() * 2];
    for(iterator_v<T> iter_o = other.begin(), iter_w = Vector<T>::begin(); iter_o != other.end(); ++iter_o, ++iter_w)
    {
        (*iter_w) = (*iter_o);
    }
    _capaсity = other._capaсity;
    _size = other._capaсity * 2;
    other._capaсity = 0;
    return (*this);
}
template <typename T>
bool Vector<T>::is_empty()
{
    return Vector<T>::_capaсity == 0;
}
template <typename T>
void Vector<T>::expand()
{
    T * copy = new T [Vector<T>::_size * 2];
    int i = 0;
    for(iterator_v<T> iter = Vector<T>::begin(); iter != Vector<T>::end(); ++iter, i++)
    {
        copy[i] = (*iter);
    }
    delete[] Vector<T>::_vector;
    Vector<T>::_vector = copy;
    Vector<T>::_size = Vector<T>::_size * 2;
}
template <typename T>
Vector<T>::~Vector()
{
    delete [] Vector<T>::_vector;
}
template <typename T>
void Vector<T>::clean()
{
    for(iterator_v<T> iter = Vector<T>::begin(); iter != Vector<T>::end(); ++iter)
    {
        (*iter) = T();
    }
    Vector<T>::_capaсity = 0;
}
template <typename T>
Vector<T>::Vector()
{
    Vector<T>::_size = 1;
    Vector<T>::_capaсity = 0;
    Vector<T>::_vector = new T[1];
}
template <typename T>
void Vector<T>::push_back(const T& exm)
{
    if(Vector<T>::_capaсity + 1 > Vector<T>::_size)
    {
        Vector<T>::expand();
    }
    int ncp = Vector<T>::_capaсity;
    Vector<T>::_vector[ncp] = T(exm);
    Vector<T>::_capaсity++;
}
template <typename T>
T& Vector<T>::operator [](int i) const
{
    if(i >= Vector<T>::_capaсity)
    {
        throw std::out_of_range("Invalid read i = " + std::to_string(i));
    }
    return Vector<T>::_vector[i];
}

#endif