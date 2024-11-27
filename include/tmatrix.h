// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

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
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) //constr copy
  {
    sz = v.sz;
    pMem = new T[sz];
    for (int i = 0;i < sz; i++)
    {pMem[i] = v.pMem[i];}
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    sz = v.sz;
    pMem = new T[sz];
    for (int i = 0;i < sz; i++)
    {pMem[i] = v.pMem[i];}
  }
  ~TDynamicVector() //vector deletion
  {
    delete pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (v != *this)
    {
      sz = v.sz;
      delete pMem;
      pMem = new T[sz];
      for (int i = 0;i<sz;i++)
      {pMem[i] = v.pMem[i];}
      return *this;
    }
    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (v != *this)
    {
      sz = v.sz;
      delete pMem;
      pMem = new T[sz];
      for (int i = 0;i<sz;i++)
      {pMem[i] = v.pMem[i];}
      return *this;
    }
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind > -1 && ind < sz)
    {
      return pMem[ind];
    }
    else{throw out_of_range("Index must be in 0 - (size - 1) range");}
  }
  const T& at(size_t ind) const
  {
    if (ind > -1 && ind < sz)
    {
      return pMem[ind];
    }
    else{throw out_of_range("Index must be in 0 - (size - 1) range");}
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (v.sz == sz)
    {
      for (int i = 0;i<sz;i++)
      {
        if (pMem[i] != v.pMem[i])
        {
          return false;
        }
      }
      return true;
    }
    return false;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    if (v.sz == sz)
    {
      for (int i = 0;i<sz;i++)
      {
        if (pMem[i] != v.pMem[i])
        {
          return true;
        }
      }
      return false;
    }
    return true;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector res(sz);
    for (int p = 0; p < sz; p++)
    {
      res.pMem[p] = pMem[p]+val;
    }
    return res;
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector res(sz);
    for (int p = 0; p < sz; p++)
    {
      res.pMem[p] = pMem[p]-val;
    }
    return res;
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector res(sz);
    for (int p = 0; p < sz; p++)
    {
      res.pMem[p] = pMem[p]*val;
    }
    return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (v.sz != sz)
    {
      throw "We cannot add vector to vector with different sizes";
    }
    TDynamicVector res(sz);
    for (int p = 0; p < sz; p++)
    {
      res.pMem[p] = pMem[p] + v.pMem[p];
    }
    return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (v.sz != sz)
    {
      throw "We cannot subtract vectors with different sizes";
    }
    TDynamicVector res(sz);
    for (int p = 0; p < sz; p++)
    {
      res.pMem[p] = pMem[p] - v.pMem[p];
    }
    return res;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
    T res = 0;
    if (v.sz != sz)
    {
      throw "We cannot multiply vectors with different sizes";
    }
    for (int p = 0; p < sz; p++)
    {
      res = res + (v.pMem[p]*pMem[p]);
    }
    return res;
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
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
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
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
    if (m.sz == sz)
    {
      for (int i = 0;i<sz;i++)
      {
        if (pMem[i] != m.pMem[i])
        {
          return false;
        }
      }
      return true;
    }
    return false;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
    if (m.sz == sz)
    {
      for (int i = 0;i<sz;i++)
      {
        if (pMem[i] != m.pMem[i])
        {
          return true;
        }
      }
      return false;
    }
    return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
    TDynamicMatrix res(sz);
    for (int p = 0; p < sz; p++)
    {
      res.pMem[p] = pMem[p]*val;
    }
    return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
    if (v.sz != sz)
    {
      throw "We cannot multiply quadratic matrix and vector with different sizes";
    }
    TDynamicVector<T> res(sz);
    for (int p = 0; p < sz; p++)
    {
      for (int j = 0; j < sz; j++)
      {
        res.pMem[p] = v.pMem[p] * pMem[j];
      }
    }
    return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
    if (m.sz != sz)
    {
      throw "We cannot add quadratic matrix to quadratic matrix with different sizes";
    }
    TDynamicMatrix res(sz);
    for (int i = 0;i<sz;i++)
    {
      res.pMem[i] = m.pMem[i] + pMem[i];
    }
    return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
    if (m.sz != sz)
    {
      throw "We cannot subtract quadratic matrixes with different sizes";
    }
    TDynamicMatrix res(sz);
    for (int i = 0;i<sz;i++)
    {
      res.pMem[i] = m.pMem[i] - pMem[i];
    }
    return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
    if (m.sz != sz)
    {
      throw "We cannot multiply quadratic matrixes with different sizes";
    }
    TDynamicMatrix sim(sz);
    for (int i = 0;i<sz;i++)
    {
      for (int j = 0;j<sz;j++)
      {
        sim.pMem[i][j] = pMem[i] * m.pMem[j];
      }
    }
    return sim;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i];
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' ';
    return ostr;
  }
};

#endif
