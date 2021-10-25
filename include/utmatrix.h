// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize()      { return Size;       } // размер вектора
  int GetStartIndex(){ return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
      for (int i = 0; i < v.Size; i++) 
      {
          ValType k= v.pVector[i];
          if (k < 1) k = 1;
          while (k < 100000)
          {   
              k *= 10;
              out << ' ';
          }
          out << v.pVector[i] << ' ';
      }
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    pVector = new ValType[s];
    Size = s; 
    StartIndex = si;

    for (int i = 0; i < Size; i++)
        pVector[i] = 0;
    
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    for (int i = 0; i < Size ; i++)
        pVector[i] = v.pVector[i];
        
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    Size = 0;
    if(pVector!=0)
        delete[] pVector;
    pVector = 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    if ((pos < (Size + StartIndex)) && (pos >= StartIndex))
        return pVector[pos - StartIndex];
    return pVector[0];
    
} /*--------------\-----------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
    if (this->Size != v.Size || StartIndex != v.StartIndex)
        return false;
    for (int i = 0; i < this->Size; i++)
        if (this->pVector[i] != v.pVector[i])
            return false;
    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
        return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (this != &v) {
        if (Size != v.Size) {
            delete[] pVector;
            pVector = new ValType[v.Size];
        }
        Size = v.Size; StartIndex = v.StartIndex;
        for (int i = 0; i < Size; i++) pVector[i] = v.pVector[i];
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
    for (int i = 0; i < Size; i++)
    {
        pVector[i] = pVector[i] + val;
    }
    return this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
    for (int i = 0; i < Size; i++)
    {
        pVector[i] = pVector[i] - val;
    }
    return this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
    for (int i = 0; i < Size; i++)
        pVector[i] = pVector[i] * val;

    return this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
    TVector<ValType> res;
    res.Size = Size;
    res.pVector = new ValType[res.Size];
    for (int i = 0; i < res.Size; i++)
    {
        res.pVector[i] = pVector[i] + v.pVector[i];
    }
    return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{   
    TVector<ValType> res;
    res.Size = Size;
    res.pVector = new ValType[res.Size];
    for (int i = 0; i < res.Size; i++)
    {
        res.pVector[i] = pVector[i] - v.pVector[i];
    }
    return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
        if (Size != v.Size) return 1;
        if (StartIndex != v.StartIndex) return 2;

        ValType res = 0;

        for (int i = 0; i < Size; i++)
            res = res + (pVector[i] * v.pVector[i]);

        return res;
} /*-------------------------------------------------------------------------*/

// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание
  ~TMatrix();
  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
      for (int i = 0; i < mt.Size; i++)
          in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
      for (int i = 0; i < mt.Size; i++) {
          for (int j = 0; j < i; j++)
              out << ' ' << ' ' << ' ' << ' ' << ' ' << ' ' << ' ';
          out << mt.pVector[i] << endl;
      }
    return out;
  }
};
template<class ValType>
TMatrix<ValType>::~TMatrix() = default;

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
    for (int i = 0; i < s; i++)
        this->pVector[i] = TVector<ValType>(s - i, i);
        
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    if (this->Size != mt.Size)
        return false;
    for (int i = 0; i < this->Size; i++)
        if (this->pVector[i] != mt.pVector[i])
            return false;
    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
    if (this != &mt) {

        if (this->Size != mt.Size) {
            delete[] this->pVector;
            this->Size = mt.Size;
            this->pVector = new TVector<ValType>[mt.Size];
            for (int i = 0; i < mt.Size; i++) {
                this->pVector[i] = mt.pVector[i];
            }
        }
        for (int i = 0; i < this->Size; ++i) {
            this->pVector[i] = mt.pVector[i];
        }
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    return TVector<TVector<ValType>>::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    return TVector<TVector<ValType>>::operator-(mt);
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
