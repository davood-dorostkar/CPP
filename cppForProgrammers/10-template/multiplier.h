#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include <iostream>
using namespace std;

template <class T>
class Multiplier
{
    T m1, m2;
    T prod;
    public:
    Multiplier(){}
    void setM1(T in);
    void setM2(T in);
    void setProduct();
    void printEquation();
};

template <class T>
void Multiplier<T>::setM1(T in)
{
    m1 = in;
}

template <class T>
void Multiplier<T>::setM2(T in)
{
    m2 = in;
}

template <class T>
void Multiplier<T>::setProduct()
{
    prod = m1 * m2;
}

template <class T>
void Multiplier<T>::printEquation()
{
    cout<<m1<<" * "<<m2<<" = "<<prod;
}
#endif // MULTIPLIER_H
