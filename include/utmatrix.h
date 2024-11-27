﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz < 0)
        {
            throw out_of_range("Vector size cant be neggative");
        }
        if (sz > MAX_VECTOR_SIZE)
        {
            throw out_of_range("Vector size cant be more than max");
        }
        pMem = new T[sz]();
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        sz = v.sz;
        pMem = v.pMem;
        v.sz = 0;
        v.pMem = nullptr;
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v)
        {
            return *this;
        }

        delete[] pMem;
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);

        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this == &v)
        {
            return *this;
        }

        delete[] pMem;

        sz = v.sz;
        pMem = v.pMem;

        v.sz = 0;
        v.pMem = nullptr;

        return *this;

    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind >= sz)
        {
            throw std::out_of_range("Index id out of range");
        }
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind >= sz)
        {
            throw std::out_of_range("Index id out of range");
        }
        return pMem[ind];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind >= sz)
        {
            throw std::out_of_range("Index id out of range");
        }
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz)
        {
            throw std::out_of_range("Index id out of range");
        }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
        {
            return false;
        }
        if (sz == v.sz)
        {
            for (int i = 0; i < sz; i++)
            {
                if (pMem[i] != v.pMem[i])
                {
                    return false;
                }
            }
        }

        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz)
        {
            return true;
        }
        else
        {
            for (int i = 0; i < sz; i++)
            {
                if (pMem[i] != v.pMem[i])
                {
                    return true;
                }
            }
        }

        return false;
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector sum(sz);
        for (int i = 0; i < sz; i++)
        {
            sum.pMem[i] = pMem[i] + val;
        }
        return sum;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector res(sz);
        for (int i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] - val;
        }
        return res;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector mul(sz);
        for (int i = 0; i < sz; i++)
        {
            mul.pMem[i] = pMem[i] * val;
        }
        return mul;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw std::out_of_range("Vectors are not with the same size");
        }

        TDynamicVector sum(sz);
        for (size_t i = 0; i < sz; i++)
        {
            sum.pMem[i] = pMem[i] + v.pMem[i];
        }
        return sum;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
        {
            throw std::out_of_range("Vectors are not with the same size");
        }

        TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++)
        {
            res.pMem[i] = pMem[i] - v.pMem[i];
        }
        return res;
    }
    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz)
        {
            throw std::out_of_range("Vectors are not with the same size");
        }

        T mul{};
        for (size_t i = 0; i < sz; i++)
        {
            mul += pMem[i] * v.pMem[i];
        }
        return mul;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор >> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор << для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (sz == 0)
            throw out_of_range("Matrix size should be greater than zero");

        if (sz > MAX_MATRIX_SIZE)
        {
            throw std::out_of_range("size cant be more than max");
        }
        for (size_t i = 0; i < sz; i++)
        {
            pMem[i] = TDynamicVector<T>(sz); // инициализация каждого вектора
        }
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    using TDynamicVector<TDynamicVector<T>>::size;

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz)
            return false;

        for (size_t i = 0; i < sz; i++)
            if (pMem[i] != m.pMem[i])
                return false;

        return true;
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept
    {
        return !(*this == m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix<T> result(sz);
        for (size_t i = 0; i < sz; i++)
        {
            result[i] = pMem[i] * val; //  векторное умножение
        }
        return result;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size())
            throw std::out_of_range("cant mult different sizes");

        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; i++)
        {
            result[i] = pMem[i] * v; //  векторное умножение
        }
        return result;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw std::out_of_range("cant sum matrices of different sizes");

        TDynamicMatrix<T> result(sz);
        for (size_t i = 0; i < sz; i++)
        {
            result[i] = pMem[i] + m.pMem[i]; //  векторное сложение
        }
        return result;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw std::out_of_range("cant subtract matrices of different sizes");

        TDynamicMatrix<T> result(sz);
        for (size_t i = 0; i < sz; i++)
        {
            result[i] = pMem[i] - m.pMem[i]; //  векторное вычитание
        }
        return result;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw std::out_of_range("cant mult matrices of different sizes");

        TDynamicMatrix<T> result(sz);
        for (size_t i = 0; i < sz; i++)
        {
            for (size_t j = 0; j < sz; j++)
            {
                result[i][j] = T(); // инициализация
                for (size_t k = 0; k < sz; k++)
                {
                    result[i][j] += pMem[i][k] * m.pMem[k][j]; // векторное умножение
                }
            }
        }
        return result;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++)
            istr >> m.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
    {
        for (size_t i = 0; i < m.sz; i++)
            ostr << m.pMem[i] << '\n'; // выводим каждую строку
        return ostr;
    }
};
