/*#include "Vector.hpp"
#include "Word.hpp"
#include "Words.hpp"
template <typename T>
void Vector<T>::expand()
{
    T ** copy = new T* [Vector<T>::_size * 2];
    for(int i = 0; i < Vector<T>::_capaсity; i++)
    {
        copy[i] = Vector<T>::_Vector[i];
    }
    delete[] Vector<T>::_Vector;
    Vector<T>::_Vector = copy;
    Vector<T>::_size = Vector<T>::_size * 2;
}
template <typename T>
Vector<T>::~Vector()
{
    for(int i = 0; i < Vector<T>::_capaсity; i++)
    {
        delete[] Vector<T>::_Vector[i];
    }
    delete [] Vector<T>::_Vector;
}
template <typename T>
Vector<T>::Vector()
{
    Vector<T>::_size = 1;
    Vector<T>::_capaсity = 0;
    Vector<T>::_Vector = new T*[1];
}
template <typename T>
void Vector<T>::push(const T& exm)
{
    if(Vector<T>::_capaсity + 1 > Vector<T>::_size)
    {
        Vector<T>::expand();
    }
    T* copy = new T(exm);
    Vector<T>::_Vector[Vector<T>::_capaсity] = copy;
    Vector<T>::_capaсity++;
}
template <typename T>
const T& Vector<T>::operator [](int i)
{
    return (const T*) Vector<T>::_Vector[i];
}*/
