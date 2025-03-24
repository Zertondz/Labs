#ifndef ITERATOR_V
#define ITERATOR_V
#include <iostream>
template <typename T> using value_type = T*;
template <typename T> using pointer = T**;
template <typename T> using reference = T*&;
using difference_type = std::ptrdiff_t;
template <typename T>
class iterator_v
{
public:
    using value_type = T*;
    using difference_type = std::ptrdiff_t;
    using pointer = T**;
    using reference = T*&;
    using iterator_category = std::bidirectional_iterator_tag;
    iterator_v();
    iterator_v(pointer other_ptr, const int pos, const int size);
    iterator_v(iterator_v<T> && exem);
    iterator_v(const iterator_v<T> & exem);
    iterator_v<T>& operator++();
    iterator_v<T> operator++(int);
    iterator_v<T>& operator--();
    iterator_v<T> operator--(int);
    difference_type operator-(const iterator_v<T>& other);
    iterator_v<T>& operator+(const iterator_v<T>& other);
    iterator_v<T> operator-(const int pos);
    iterator_v<T> operator+(const int pos);
    iterator_v<T> operator*(const int i);
    iterator_v<T> operator/(const int i);
    iterator_v<T>& operator=(const iterator_v<T>& other);
    iterator_v<T>& operator=(iterator_v<T>&& other);
    bool operator==(const iterator_v<T>& other);
    bool operator!=(const iterator_v<T>& other);
    bool operator >(const iterator_v<T>& other);
    bool operator <(const iterator_v<T>& other);
    bool operator==(const int pos);
    bool operator!=(const int pos);
    bool operator >(const int pos);
    bool operator <(const int pos);
    reference operator*();
    ~iterator_v();
private:
    pointer _ptr;
    int _position;
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
        throw std::out_of_range("Invalid read");
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
        throw std::out_of_range("Invalid read");
    }
    return iterator_v<T>(iterator_v<T>::_ptr, iterator_v<T>::_position - pos, iterator_v<T>::_size);
}
template <typename T>
iterator_v<T> iterator_v<T>::operator+(const int pos)
{
    if(iterator_v<T>::_position + pos > iterator_v<T>::_size)
    {
        throw std::out_of_range("Invalid read");
    }
    return iterator_v<T>(iterator_v<T>::_ptr, iterator_v<T>::_position + pos, iterator_v<T>::_size);
}
template <typename T>
iterator_v<T> iterator_v<T>::operator*(const int i)
{
    if(iterator_v<T>::_position * i > iterator_v<T>::_size)
    {
        throw std::out_of_range("Invalid read");
    }
    return iterator_v<T>(iterator_v<T>::_ptr, iterator_v<T>::_position * i, iterator_v<T>::_size);
}
template <typename T>
iterator_v<T> iterator_v<T>::operator/(const int i)
{
    if(iterator_v<T>::_position / i > iterator_v<T>::_size)
    {
        throw std::out_of_range("Invalid read");
    }
    return iterator_v<T>(iterator_v<T>::_ptr, iterator_v<T>::_position / i, iterator_v<T>::_size);
}
template <typename T>
iterator_v<T> iterator_v<T>::operator++(int)
{    
    if(iterator_v<T>::_position + 1 > iterator_v<T>::_size)
    {
        throw std::out_of_range("Invalid read");
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
    if(iterator_v<T>::_position + 1 > iterator_v<T>::_size)
    {
        throw std::out_of_range("Invalid read");
    }
    iterator_v<T>::_position++;
    return *this;
}
template <typename T>
iterator_v<T>& iterator_v<T>::operator--()
{
    if(iterator_v<T>::_position - 1 < 0)
    {
        throw std::out_of_range("Invalid read");
    }
    iterator_v<T>::_position--;
    return *this;
}
template <typename T>
iterator_v<T> iterator_v<T>::operator--(int)
{
    if(iterator_v<T>::_position - 1 < 0)
    {
        throw std::out_of_range("Invalid read");
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
        throw std::out_of_range("Invalid read");
    }
    iterator_v<T>::_ptr = other_ptr;
    iterator_v<T>::_size = size;
    iterator_v<T>::_position = pos;
}
template <typename T>
iterator_v<T>::~iterator_v(){}

#endif