// Верхнетреугольная матрица - реализация на основе шаблона вектора (заголовочный файл)
#ifndef __TMATRIX_H__
#define __TMATRIX_H__
#include <iostream>
using namespace std;
const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{ protected:
    ValType *pVector;
    int Size;       // размер вектора
    int StartIndex; // индекс первого элемента вектора
  public:
    //Конструкторы и деструкторы
    TVector(int s = 10, int si = 0);
    TVector(const TVector &v);                // конструктор копирования
    ~TVector();
    //Доступ к полям
    int GetSize()      { return Size;       } // размер вектора
    int GetStartIndex(){ return StartIndex; } // индекс первого элемента
    ValType& operator[](int pos);             // доступ
    //Перегрузка операций
    bool operator==(const TVector &v) const;  // сравнение
    bool operator!=(const TVector &v) const;  // сравнение
    TVector& operator=(const TVector &v);     // присваивание
    //Скалярные операции
    TVector  operator+(const ValType &val);   // прибавить скаляр
    TVector  operator-(const ValType &val);   // вычесть скаляр
    TVector  operator*(const ValType &val);   // умножить на скаляр
    //Векторные операции
    TVector  operator+(const TVector &v);     // сложение
    TVector  operator-(const TVector &v);     // вычитание
    ValType  operator*(const TVector &v);     // скалярное произведение
    //Перегрузка ввод-вывод
    friend istream& operator>>(istream &in, TVector &v)
    { for (int i = 0; i < v.Size; i++)
      { in >> v.pVector[i];}
      return in;
     }
    friend ostream& operator<<(ostream &out, const TVector &v)
    { for (int i = 0; i < v.Size; i++)
      { out << v.pVector[i] << ' ';}
      return out;
    }
};
// Реализация функций класса вектора 
    //Конструкторы и деструкторы    
    template <class ValType>
    TVector<ValType>::TVector(int s, int si)
    { if ((s >= 0) && (s < MAX_VECTOR_SIZE)&&(si>=0))
      { Size = s;      
        StartIndex = si; 
        pVector = new ValType[Size];
        for(int i=0; i< Size;i++)
        {pVector[i]=0;}
    }
    else { throw 1;  }
    } 
    template <class ValType> //конструктор копирования
    TVector<ValType>::TVector(const TVector<ValType> &v)
    {   Size = v.Size;
        StartIndex = v.StartIndex;
        pVector = new ValType[Size];
        for(int i=0; i< Size;i++)
        { pVector[i]=v.pVector[i];}
    } 
    template <class ValType>
    TVector<ValType>::~TVector()
    { if (pVector != NULL)
	  {	delete[] pVector;
		pVector = NULL;}
    }
    //Доступ к полям
    template <class ValType> 
    ValType& TVector<ValType>::operator[](int pos)
    {
        if ((pos < 0) || (pos > Size + StartIndex) || (pos < StartIndex))
        {throw 1;}
        else
        { return pVector[pos - StartIndex];}
    } 
    //Перегрузка операций
    template <class ValType> // сравнение
    bool TVector<ValType>::operator==(const TVector &v) const
    { int flag = 1; 
      if ((Size==v.Size)&&(StartIndex==v.StartIndex))
      { int i = 0; 
        while ((i < Size)&&(flag==1))
        { if (pVector[i] != v.pVector[i]) { flag = 0;} i++;}  
        return flag;}
      else { return 0; }
    } 
    template <class ValType> // сравнение
    bool TVector<ValType>::operator!=(const TVector &v) const
    { if(*this==v){return 0;}
      else {return 1;}
    } 
    template <class ValType> // присваивание
    TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
    { if (this != &v)
      { delete[] pVector;
        Size = v.Size;
        StartIndex = v.StartIndex;
        pVector = new ValType[Size];
        for (int i = 0; i < Size; i++)
        { pVector[i] = v.pVector[i];}
       }
       return *this;
    } 
    //Скалярные операции
    template <class ValType> // прибавить скаляр
    TVector<ValType> TVector<ValType>::operator+(const ValType &val)
    {   TVector R(Size, StartIndex);
        for (int i = 0; i < Size; i++)
        {R.pVector[i] = pVector[i] + val;}
        return R;
    } 
    template <class ValType> // вычесть скаляр
    TVector<ValType> TVector<ValType>::operator-(const ValType &val)
     { TVector R;
       ValType v = val*(-1);
       R = (*this) + v;
       return R;
     } 
    template <class ValType> // умножить на скаляр
    TVector<ValType> TVector<ValType>::operator*(const ValType &val)
    {   TVector R(Size, StartIndex);
        for (int i = 0; i < Size; i++)
        {R.pVector[i] = pVector[i] * val;}
        return R;
    } 
    //Векторные операции
    template <class ValType> // сложение
    TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
    {  if( Size==v.Size){
      if(StartIndex< v.StartIndex)
      { TVector R(*this);
        int n = v.StartIndex - StartIndex;
        for (int i = n; i < Size; i++)
        {R.pVector[i] = pVector[i] + v.pVector[i-n];}
        return R;
      } else
      { TVector R(v);
        int n = StartIndex - v.StartIndex;
        for (int i = n; i < Size; i++)
        { R.pVector[i] = pVector[i-n] + v.pVector[i];}
        return R;}
      }
      else { throw 1; }
    } 
    template <class ValType> // вычитание
    TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
    { if( Size==v.Size){
        if(StartIndex< v.StartIndex)
      { TVector R(*this);
        int n = v.StartIndex - StartIndex;
        for (int i = n; i < Size; i++)
        {R.pVector[i] = pVector[i] - v.pVector[i-n];}
        return R;
      } else
      { TVector R(v);
        int n = StartIndex - v.StartIndex;
        for (int i = n; i < Size; i++)
        { R.pVector[i] = pVector[i-n] - v.pVector[i];}
        return R;
      }
    }
      else { throw 1; }
    } 
    template <class ValType> // скалярное произведение
    ValType TVector<ValType>::operator*(const TVector<ValType> &v)
    { if( Size==v.Size){
      ValType r = 0;
      if(StartIndex< v.StartIndex)
      { int n = v.StartIndex - StartIndex;
        for (int i = n; i < Size; i++)
        {r = r + pVector[i]*v.pVector[i-n];}
      } else
      { int n = StartIndex - v.StartIndex;
        for (int i = n; i < Size; i++)
        { r = r + pVector[i-n]*v.pVector[i];}
      }
      return r;
    }
    else { throw 1; }
    } 

// Класс верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{ public:
    //Конструкторы и деструкторы 
    TMatrix(int s = 10);                           
    TMatrix(const TMatrix &mt);                    // копирование
    TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
    //Перегрузка операций
    bool operator==(const TMatrix &mt) const;      // сравнение
    bool operator!=(const TMatrix &mt) const;      // сравнение
    TMatrix& operator= (const TMatrix &mt);        // присваивание
    TMatrix  operator+ (const TMatrix &mt);        // сложение
    TMatrix  operator- (const TMatrix &mt);        // вычитание
    //Перегрузка ввод-вывод
    friend istream& operator>>(istream &in, TMatrix &mt)
    { for (int i = 0; i < mt.Size; i++)
      { in >> mt.pVector[i];}
      return in;
    }
    friend ostream & operator<<( ostream &out, const TMatrix &mt)
    { for (int i = 0; i < mt.Size; i++)
      { out << mt.pVector[i] << endl;}
      return out;
    }
};

// Реализация функций класса матрицы 
    //Конструкторы и деструкторы 
    template <class ValType>
    TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
    { if ((s > 0) && (s < MAX_MATRIX_SIZE)) 
      { Size = s;
        for (int i = 0; i < s; i++) 
        { pVector[i] = TVector<ValType>(Size - i, i);}
	  } else { throw 1;}
    } 
    template <class ValType> // конструктор копирования
    TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
    TVector<TVector<ValType> >(mt) {}
    template <class ValType> // конструктор преобразования типа
    TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
    TVector<TVector<ValType> >(mt) {}
    //Перегрузка операций
    template <class ValType> // сравнение
    bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
    { if(Size==mt.Size) 
      { int flag = 1, i = 0; 
        while ((i < Size)&&(flag==1))
        { if (pVector[i] != mt.pVector[i]){flag=0;}
        i++;} 
      return flag;}
      else { return 0; }
    }
    template <class ValType> // сравнение
    bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
    { if(*this== mt){return 0;}
      else {return 1;}
    }
    template <class ValType> // присваивание
    TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
    { if (this != &mt)
      { if(Size!=mt.Size)
        { delete[] pVector;
          pVector = new TVector<ValType>[mt.Size];
          Size = mt.Size;
          StartIndex = mt.StartIndex;
        }
        for (int i = 0; i < Size; i++) 
          { pVector[i] = mt.pVector[i];}
      }
       return *this;
    } 
    template <class ValType> // сложение
    TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
    {
        return TVector <TVector<ValType> >:: operator +(mt);
    }
    template <class ValType> // вычитание
    TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
    {
        return TVector <TVector<ValType> >:: operator -(mt);
    }

#endif
