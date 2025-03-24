#ifndef ITERATOR_V
#define ITERATOR_V
#include <string>
#include <stdexcept>
template <typename T> using value_type = T;
template <typename T> using pointer = T*;
template <typename T> using reference = T&;
using difference_type = std::ptrdiff_t;
/*!
    \class iterator_v
    \brief Шаблонный класс итератора для контейнера.

    Реализует функциональность итератора, включая поддержку арифметики, сравнений и разыменования.
    Используется для последовательного доступа к элементам контейнера.
    \tparam T Тип данных, к которым предоставляет доступ итератор.
*/
template <typename T>
class iterator_v
{
public:
    /*!
        \brief Тип значения, к которому предоставляет доступ итератор.
    */
    using value_type = T;

    /*!
        \brief Тип разности между итераторами.
    */
    using difference_type = std::ptrdiff_t;

    /*!
        \brief Указатель на тип значения.
    */
    using pointer = T*;

    /*!
        \brief Ссылка на тип значения.
    */
    using reference = T&;

    /*!
        \brief Категория итератора.
        \details Указывает, что итератор является двунаправленным.
    */
    using iterator_category = std::bidirectional_iterator_tag;

    /*!
        \brief Конструктор по умолчанию.
        \details Инициализирует пустой итератор.
    */
    iterator_v();

    /*!
        \brief Конструктор с параметрами.
        \param other_ptr Указатель на начало контейнера.
        \param pos Текущая позиция итератора.
        \param size Размер контейнера.
    */
    iterator_v(pointer other_ptr, const int pos, const int size);

    /*!
        \brief Конструктор перемещения.
        \param exem Rvalue-ссылка на другой итератор.
    */
    iterator_v(iterator_v<T>&& exem);

    /*!
        \brief Конструктор копирования.
        \param exem Константная ссылка на другой итератор.
    */
    iterator_v(const iterator_v<T>& exem);

    /*!
        \brief Оператор префиксного инкремента.
        \return Ссылка на текущий итератор.
    */
    iterator_v<T>& operator++();

    /*!
        \brief Оператор постфиксного инкремента.
        \return Итератор до инкрементации.
    */
    iterator_v<T> operator++(int);

    /*!
        \brief Оператор префиксного декремента.
        \return Ссылка на текущий итератор.
    */
    iterator_v<T>& operator--();

    /*!
        \brief Оператор постфиксного декремента.
        \return Итератор до декрементации.
    */
    iterator_v<T> operator--(int);

    /*!
        \brief Разность между итераторами.
        \param other Итератор для вычисления разности.
        \return Разность в виде \c difference_type.
    */
    difference_type operator-(const iterator_v<T>& other);

    /*!
        \brief Сложение двух итераторов.
        \param other Итератор для сложения.
        \return Ссылка на текущий итератор.
    */
    iterator_v<T>& operator+(const iterator_v<T>& other);

    /*!
        \brief Вычитание позиции из итератора.
        \param pos Позиция для вычитания.
        \return Новый итератор.
    */
    iterator_v<T> operator-(const int pos);

    /*!
        \brief Сложение позиции с итератором.
        \param pos Позиция для сложения.
        \return Новый итератор.
    */
    iterator_v<T> operator+(const int pos);

    /*!
        \brief Умножение позиции на итератор.
        \param i Позиция для умножения.
        \return Новый итератор.
    */
    iterator_v<T> operator*(const int i);

    /*!
        \brief Деление итератора на позицию.
        \param i Делитель.
        \return Новый итератор.
    */
    iterator_v<T> operator/(const int i);

    /*!
        \brief Оператор присваивания копирования.
        \param other Константная ссылка на другой итератор.
        \return Ссылка на текущий итератор.
    */
    iterator_v<T>& operator=(const iterator_v<T>& other);

    /*!
        \brief Оператор присваивания перемещения.
        \param other Rvalue-ссылка на другой итератор.
        \return Ссылка на текущий итератор.
    */
    iterator_v<T>& operator=(iterator_v<T>&& other);

    /*!
        \brief Сравнение на равенство с другим итератором.
        \param other Другой итератор.
        \return \c true, если итераторы равны; иначе \c false.
    */
    bool operator==(const iterator_v<T>& other);

    /*!
        \brief Сравнение на неравенство с другим итератором.
        \param other Другой итератор.
        \return \c true, если итераторы не равны; иначе \c false.
    */
    bool operator!=(const iterator_v<T>& other);

    /*!
        \brief Сравнение "больше" с другим итератором.
        \param other Другой итератор.
        \return \c true, если текущий итератор больше; иначе \c false.
    */
    bool operator>(const iterator_v<T>& other);

    /*!
        \brief Сравнение "меньше" с другим итератором.
        \param other Другой итератор.
        \return \c true, если текущий итератор меньше; иначе \c false.
    */
    bool operator<(const iterator_v<T>& other);

    /*!
        \brief Сравнение на равенство с позицией.
        \param pos Позиция для сравнения.
        \return \c true, если текущая позиция итератора равна указанной; иначе \c false.
    */
    bool operator==(const int pos);

    /*!
        \brief Сравнение на неравенство с позицией.
        \param pos Позиция для сравнения.
        \return \c true, если текущая позиция итератора не равна указанной; иначе \c false.
    */
    bool operator!=(const int pos);

    /*!
        \brief Сравнение "больше" с позицией.
        \param pos Позиция для сравнения.
        \return \c true, если текущая позиция итератора больше указанной; иначе \c false.
    */
    bool operator>(const int pos);

    /*!
        \brief Сравнение "меньше" с позицией.
        \param pos Позиция для сравнения.
        \return \c true, если текущая позиция итератора меньше указанной; иначе \c false.
    */
    bool operator<(const int pos);

    /*!
        \brief Разыменование итератора.
        \return Ссылка на текущий элемент.
    */
    reference operator*();

    /*!
        \brief Деструктор.
    */
    ~iterator_v();

private:
    /*!
        \brief Указатель на текущий элемент массива.
    */
    pointer _ptr;

    /*!
        \brief Текущая позиция итератора.
    */
    int _position;

    /*!
        \brief Размер контейнера.
    */
    int _size;
};

template <typename T>
reference<T> iterator_v<T>::operator*()
{
    if(iterator_v<T>::_ptr == nullptr)
    {
        throw std::runtime_error("Пустой итератор");
    }
    return *(iterator_v<T>::_ptr + iterator_v<T>::_position);
}
template <typename T>
difference_type iterator_v<T>::operator-(const iterator_v<T>& other)
{
    return iterator_v<T>::_position - other._position;
}
template <typename T>
iterator_v<T>& iterator_v<T>::operator+(const iterator_v<T>& other)
{
    if(iterator_v<T>::_position + other._position > iterator_v<T>::_size)
    {
        throw std::out_of_range("Invalid read +");
    }
    iterator_v<T>::_position += other._position;
    return *this;
}
template <typename T>
iterator_v<T>& iterator_v<T>::operator=(const iterator_v<T>& other)
{
    this->_position = other._position;
    this->_ptr = other._ptr;
    this->_size = other._size;
    return *this;
}
template <typename T>
iterator_v<T>& iterator_v<T>::operator=(iterator_v<T>&& other)
{
    this->_position = other._position;
    this->_ptr = other._ptr;
    this->_size = other._size;
    return *this;
}
template <typename T>
iterator_v<T> iterator_v<T>::operator-(const int pos)
{
    if(iterator_v<T>::_position - pos < 0)
    {
        throw std::out_of_range("Invalid read -");
    }
    return iterator_v<T>(iterator_v<T>::_ptr, iterator_v<T>::_position - pos, iterator_v<T>::_size);
}
template <typename T>
iterator_v<T> iterator_v<T>::operator+(const int pos)
{
    if(iterator_v<T>::_position + pos > iterator_v<T>::_size)
    {
        throw std::out_of_range("Invalid read +");
    }
    return iterator_v<T>(iterator_v<T>::_ptr, iterator_v<T>::_position + pos, iterator_v<T>::_size);
}
template <typename T>
iterator_v<T> iterator_v<T>::operator*(const int i)
{
    if(iterator_v<T>::_position * i > iterator_v<T>::_size)
    {
        throw std::out_of_range("Invalid read *");
    }
    return iterator_v<T>(iterator_v<T>::_ptr, iterator_v<T>::_position * i, iterator_v<T>::_size);
}
template <typename T>
iterator_v<T> iterator_v<T>::operator/(const int i)
{
    if(iterator_v<T>::_position / i > iterator_v<T>::_size)
    {
        throw std::out_of_range("Invalid read /");
    }
    return iterator_v<T>(iterator_v<T>::_ptr, iterator_v<T>::_position / i, iterator_v<T>::_size);
}
template <typename T>
iterator_v<T> iterator_v<T>::operator++(int)
{    
    if(iterator_v<T>::_position + 1 > iterator_v<T>::_size)
    {
        throw std::out_of_range("Invalid read ++");
    }
    iterator_v<T> temp(iterator_v<T>::_ptr, 1 + iterator_v<T>::_position, iterator_v<T>::_size);
    iterator_v<T>::operator++();
    return temp;
}
template <typename T>
bool iterator_v<T>::operator==(const iterator_v<T>& other)
{
    return iterator_v<T>::_position == other._position;
}
template <typename T>
bool iterator_v<T>::operator!=(const iterator_v<T>& other)
{
    return iterator_v<T>::_position != other._position;
}
template <typename T>
bool iterator_v<T>::operator<(const iterator_v<T>& other)
{
    return iterator_v<T>::_position < other._position;
}
template <typename T>
bool iterator_v<T>::operator>(const iterator_v<T>& other)
{
    return iterator_v<T>::_position > other._position;
}
template <typename T>
bool iterator_v<T>::operator==(const int pos)
{
    return iterator_v<T>::_position == pos;
}
template <typename T>
bool iterator_v<T>::operator!=(const int pos)
{
    return iterator_v<T>::_position != pos;
}
template <typename T>
bool iterator_v<T>::operator<(const int pos)
{
    return iterator_v<T>::_position < pos;
}
template <typename T>
bool iterator_v<T>::operator>(const int pos)
{
    return iterator_v<T>::_position > pos;
}
template <typename T>
iterator_v<T>& iterator_v<T>::operator++()
{
    iterator_v<T>::_position++;
    return *this;
}
template <typename T>
iterator_v<T>& iterator_v<T>::operator--()
{
    if(iterator_v<T>::_position - 1 < 0)
    {
        throw std::out_of_range("Invalid read --");
    }
    iterator_v<T>::_position--;
    return *this;
}
template <typename T>
iterator_v<T> iterator_v<T>::operator--(int)
{
    if(iterator_v<T>::_position - 1 < 0)
    {
        throw std::out_of_range("Invalid read --");
    }
    iterator_v<T> temp(iterator_v<T>::_ptr, iterator_v<T>::_position - 1, iterator_v<T>::_size);
    iterator_v<T>::operator--();
    return *this;
}
template <typename T>
iterator_v<T>::iterator_v()
{
    iterator_v<T>::_ptr = nullptr;
    iterator_v<T>::_size = 0;
    iterator_v<T>::_position = 0;
}
template <typename T>
iterator_v<T>::iterator_v(iterator_v<T> && exem)
{
    iterator_v<T>::_ptr = exem._ptr;
    iterator_v<T>::_size = exem._size;
    iterator_v<T>::_position = exem._position;
}
template <typename T>
iterator_v<T>::iterator_v(const iterator_v<T> & exem)
{
    iterator_v<T>::_ptr = exem._ptr;
    iterator_v<T>::_size = exem._size;
    iterator_v<T>::_position = exem._position;
}
template <typename T>
iterator_v<T>::iterator_v(pointer other_ptr,const int pos,const int size)
{
    if(pos > size)
    {
        std::string exep("Invalid read: pos = ");
        exep = exep + std::to_string(pos) + "size = " + std::to_string(size);
        throw std::out_of_range(exep);
    }
    iterator_v<T>::_ptr = other_ptr;
    iterator_v<T>::_size = size;
    iterator_v<T>::_position = pos;
}
template <typename T>
iterator_v<T>::~iterator_v(){}

#endif