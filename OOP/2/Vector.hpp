#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include "iterator_v.hpp"
template <typename T>
class Vector
{
private:
    T ** _vector;
    int _capaсity;
    int _size;
    void expand();
public:
    Vector();
    Vector(const Vector<T> & exm);
    ~Vector();
    iterator_v<T> begin() const;
    iterator_v<T> end() const;
    int get_cap() const;
    void push(const T& exm);
    void clean();
    const T& operator [](int i) const;
    Vector<T>& operator =(Vector<T>&& other);
    Vector<T>& operator =(const Vector<T>& other);
    bool is_empty();
};
template <typename T>
iterator_v<T> Vector<T>::begin() const
{
    return iterator_v<T>(Vector<T>::_vector, 0, Vector<T>::_size);
}
template <typename T>
int Vector<T>::get_cap() const
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
    Vector<T>::_size = 1;
    Vector<T>::_capaсity = 0;
    Vector<T>::_vector = new T*[1];
    for(iterator_v<T> iter = exm.begin(); iter != exm.end(); ++iter)
    {
        Vector<T>::push(*(*iter));
    }
}
template <typename T>
Vector<T>& Vector<T>::operator =(const Vector<T>& other)
{
    Vector<T>::clean();
    for(iterator_v<T> iter = other.begin(); iter != other.end(); ++iter)
    {
        Vector<T>::push(*(*iter));
    }
    other._capaсity = 0;
    return (*this);
}
template <typename T>
Vector<T>& Vector<T>::operator = (Vector<T>&& other)
{
    Vector<T>::clean();
    while(Vector<T>::_size < other._capaсity)
    {
        Vector<T>::expand();
    }
    for(iterator_v<T> iter_o = other.begin(), iter_w = Vector<T>::begin(); iter_o != other.end(); ++iter_o, ++iter_w)
    {
        (*iter_w) = (*iter_o);
    }
    Vector::_capaсity = other._capaсity;
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
    int i = 0;
    T ** copy = new T* [Vector<T>::_size * 2];
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
    for(iterator_v<T> iter = Vector<T>::begin(); iter != Vector<T>::end(); ++iter)
    {
        delete[] (*iter);
    }
    delete [] Vector<T>::_vector;
}
template <typename T>
void Vector<T>::clean()
{
    for(iterator_v<T> iter = Vector<T>::begin(); iter != Vector<T>::end(); ++iter)
    {
        delete[] (*iter);
    }
    Vector<T>::_capaсity = 0;
}
template <typename T>
Vector<T>::Vector()
{
    Vector<T>::_size = 1;
    Vector<T>::_capaсity = 0;
    Vector<T>::_vector = new T*[1];
}
template <typename T>
void Vector<T>::push(const T& exm)
{
    if(Vector<T>::_capaсity + 1 > Vector<T>::_size)
    {
        Vector<T>::expand();
    }
    Vector<T>::_vector[Vector<T>::_capaсity] = new T[1](exm);
    Vector<T>::_capaсity++;
}
template <typename T>
const T& Vector<T>::operator [](int i) const
{
    if(i >= Vector<T>::_capaсity)
    {
        throw std::out_of_range("Invalid read");
    }
    return (const T&) (*Vector<T>::_vector[i]);
}
#endif