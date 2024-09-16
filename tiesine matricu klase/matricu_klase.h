#ifndef MATRIX_H
#define MATRIX_H
#endif // MATRIX_H
#include <iostream>
#include <thread>
#include <mutex>
/*Tiesine matricu klase nurasiau tai visai ne bloga gavos. Lygiagreti tai ir ne
pagal salyga ir isvis turbut nesamone. Sinchronizavimas kaip ir gal pavyko tik
nezinau ar visur jo reikia. Pabandziau kazka.

/*inputMatrix = [1.0, 3.0, 2.0,
              1.0, 1.0, 0.0
              0.0, 3.0, 0.0]*/
std::mutex m;


const int WORKERS = 4;
template <class T>
class Matrix
{

public:
//konstruktoriai
    Matrix();
    Matrix(int nRows, int nCols);
    Matrix(int nRows, int nCols, const T *inputData);
    Matrix(const Matrix<T>& inputMatrix);

//destruktorius
    ~Matrix();
//****************************************************************
//    BS PRASIDEDA
//****************************************************************
    std::thread t1(Matrix());
    std::thread t2(Matrix(int nRows, int nCols), 3, 3);
    std::thread t3(Matrix(int nRows, int nCols, const T *inputData)3,3,inputMatrix[9] = [1.0, 3.0, 2.0,
                                                                                                  1.0, 1.0, 0.0
                                                                                                  0.0, 3.0, 0.0]);
    std::thread t4(Matrix(const Matrix<T>& inputMatrix));
    std::thread t5(~Matrix());

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();



bool resize(int numRows, int numCols);

//prieiga prie elementu
T GetElement(int row, int col);
bool SetElement(int row, int col, T elementValue);
int GetNumRows();
int GetNumCols();

//Overloadai
bool operator== (const Matrix<T>& rhs);
template <class U> friend Matrix<U> operator+ (const Matrix<U>& lhs, const Matrix<U>& rhs);
template <class U> friend Matrix<U> operator+ (const U& lhs, const Matrix<U>& rhs);
template <class U> friend Matrix<U> operator+ (const Matrix<U>& lhs, const U& rhs);

template <class U> friend Matrix<U> operator- (const Matrix<U>& lhs, const Matrix<U>& rhs);
template <class U> friend Matrix<U> operator- (const U& lhs, const Matrix<U>& rhs);
template <class U> friend Matrix<U> operator- (const Matrix<U>& lhs, const U& rhs);

template <class U> friend Matrix<U> operator* (const Matrix<U>& lhs, const Matrix<U>& rhs);
template <class U> friend Matrix<U> operator* (const U& lhs, const Matrix<U>& rhs);
template <class U> friend Matrix<U> operator* (const Matrix<U>& lhs, const U& rhs);

private:
int Sub2Ind(int row, int col);

private:
double *m_matrixData;
int m_nRows, m_nCols, m_nElements;
};
//KONSTRUKTORIAUS DESTRUKTORIAUS FUNKCIJOS
template <class T>
Matrix<T>::Matrix()
{
    m.lock();
    m_nRows = 1;
    m_nCols = 1;
    m_nElements = 1;
    m_matrixData = new T[m_nElements];
    m_matrixData[0] = 0.0;
    m.unlock();
}

//tuscia matrica
template <class T>
Matrix<T>::Matrix(int nRows, int nCols)
{
    m.lock();
    m_nRows = nRows;
    m_nCols = nCols;
    m_nElements = m_nRows * m_nCols;
    m_matrixData = new T[m_nElements];
    for (int i=0; i<m_nElements; i++)
        m_matrixData[i] = 0.0;

    m.unlock();
}

//sukuria matrica kaip tiesini masyva
template <class T>
Matrix<T>::Matrix(int nRows, int nCols, const T *inputData)
{
    m.lock();
    m_nRows = nRows;
    m_nCols = nCols;
    m_nElements = m_nRows * m_nCols;
    m_matrixData = new T[m_nElements];
    for (int i=0; i<m_nElements; i++)
        m_matrixData[i] = inputData[i];

    m.unlock();
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& inputMatrix)
{
    m.lock();
    m_nRows = inputMatrix.m_nRows;
    m_nCols = inputMatrix.m_nCols;
    m_nElements = inputMatrix.m_nElements;
    m_matrixData = new T[m_nElements];
    for (int i=0; i<m_nElements; i++)
        m_matrixData[i] = inputMatrix.m_matrixData[i];

    m.unlock();
}
template <class T>
Matrix<T>::~Matrix()
{
    m.lock();
    if (m_matrixData != nullptr)
        delete[] m_matrixData;

    m.unlock();
}

//KONFIGURACIJOS FUNKCIJOS
template <class T>
bool Matrix<T>::resize(int numRows, int numCols)
{
    m.lock();
    m_nRows = numRows;
    m_nCols = numCols;
    m_nElements = (m_nRows * m_nCols);
    delete[] m_matrixData;
    m_matrixData = new T[m_nElements];
    if (m_matrixData != nullptr)
    {
        for (int i=0; i<m_nElements; i++)
        {
            m_matrixData[i] = 0.0;
        }
        return true;
    }
    else
    {
        return false;
    }
    m.unlock();
}
//ELEMENTU FUNKCIJOS
template <class T>
T Matrix<T>::GetElement(int row, int col)
{
    m.lock();
    int linearIndex = Sub2Ind(row, col);
    if (linearIndex >= 0)
        return m_matrixData[linearIndex];
    else
        return 0.0;

    m.unlock();
}

template <class T>
bool Matrix<T>::SetElement(int row, int col, T elementValue)
{
    m.lock();
    int linearIndex = Sub2Ind(row, col);
    if (linearIndex >= 0)
    {
        m_matrixData[linearIndex] = elementValue;
        return true;
    }
    else
    {
        return false;
    }
    m.unlock();
}

template <class T>
int Matrix<T>::GetNumRows()
{
    m.lock();
    return m_nRows;
    m.unlock();
}

template <class T>
int Matrix<T>::GetNumCols()
{
    m.lock();
    return m_nCols;
    m.unlock();
}

//OPERATORIU FUNKCIJOS
// + OPERATORIUS

// matrica + matrica
template <class T>
Matrix<T> operator+ (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    m.lock();
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i<numElements; i++)
    {
        tempResult[i] = lhs.m_matrixData[i] + rhs.m_matrixData[i];
    }
    Matrix  <T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
    m.unlock();
}

//skaliaras + matrica
template <class T>
Matrix<T> operator+ (const T& lhs, const Matrix<T>& rhs)
{
    m.lock();
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i<numElements; ++i)
    {
        tempResult[i] = lhs + rhs.m_matrixData[i];
    }
    Matrix  <T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
    m.unlock();
}

//matrica + skaliaras
template <class T>
Matrix<T> operator+ (const Matrix<T>& lhs, const double& rhs)
{
    m.lock();
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i<numElements; ++i)
    {
        tempResult[i] = lhs.m_matrixData[i] + rhs;
    }
    Matrix  <T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
    m.unlock();
}
// - OPERATORIUS

// matrica - matrica
template <class T>
Matrix<T> operator- (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    m.lock();
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i<numElements; i++)
    {
        tempResult[i] = lhs.m_matrixData[i] - rhs.m_matrixData[i];
    }
    Matrix  <T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
    m.unlock();
}

//skaliaras - matrica
template <class T>
Matrix<T> operator- (const T& lhs, const Matrix<T>& rhs)
{
    m.lock();
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i<numElements; ++i)
    {
        tempResult[i] = lhs - rhs.m_matrixData[i];
    }
    Matrix  <T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
    m.unlock();
}

//matrica - skaliaras
template <class T>
Matrix<T> operator- (const Matrix<T>& lhs, const T& rhs)
{
    m.lock();
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i<numElements; ++i)
    {
        tempResult[i] = lhs.m_matrixData[i] - rhs;
    }
    Matrix  <T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
    m.unlock();
}

// *OPERATORIUS

// matrica * matrica
template <class T>
Matrix<T> operator* (const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    m.lock();
    int r_numRows =  rhs.m_nRows;
    int r_numCols = rhs.m_nCols;
    int l_numRows = lhs.m_nRows;
    int l_numCols = lhs.m_nCols;

    T *tempResult = new T[lhs.m_nRows * rhs.m_nCols];
    for (int lhsRow=0; lhsRow<l_numRows; lhsRow++)
    {
        for (int rhsCol=0; rhsCol<l_numCols; rhsCol++)
        {
            double elementResult = 0.0;
            for (int lhsCol=0; lhsCol<l_numCols; lhsCol++)
            {
                int lhsLinearIndex = (lhsRow * l_numCols) + lhsCol;
                int rhsLinearIndex = (lhsCol * r_numCols) + rhsCol;
                elementResult += (lhs.m_matrixData[lhsLinearIndex] * rhs.m_matrixData[rhsLinearIndex]);
            }
            int resultLinearIndex = (lhsRow * r_numCols) + rhsCol;
            tempResult[resultLinearIndex] = elementResult;
        }
    }
    Matrix<T> result(l_numRows, r_numCols, tempResult);
    delete[] tempResult;
    return result;
    m.unlock();
}



//skaliaras * matrica
template <class T>
Matrix<T> operator* (const T& lhs, const Matrix<T>& rhs)
{
    m.lock();
    int numRows = rhs.m_nRows;
    int numCols = rhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i<numElements; ++i)
    {
        tempResult[i] = lhs * rhs.m_matrixData[i];
    }
    Matrix  <T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
    m.unlock();
}

//matrica * skaliaras
template <class T>
Matrix<T> operator* (const Matrix<T>& lhs, const T& rhs)
{
    m.lock();
    int numRows = lhs.m_nRows;
    int numCols = lhs.m_nCols;
    int numElements = numRows * numCols;
    T *tempResult = new T[numElements];
    for (int i = 0; i<numElements; ++i)
    {
        tempResult[i] = lhs.m_matrixData[i] * rhs;
    }
    Matrix  <T> result(numRows, numCols, tempResult);
    delete[] tempResult;
    return result;
    m.unlock();
}
//== OPERATORIUS
template <class T>
bool Matrix<T>::operator== (const Matrix<T>& rhs)
{
    m.lock();
    bool flag = true;
    for (int i=0; i<this->m_nElements; ++i)
    {
        if (this -> m_matrixData[i] != rhs.m_matrixData[i])
            flag = false;
    }
    return flag;
    m.unlock();
}

template <class T>
int Matrix <T>::Sub2Ind(int row, int col)
{
    m.lock();
    if ((row < m_nRows) && (row >= 0) && (col <m_nCols) && (col >=0))
        return (row * m_nCols) + col;
    else
        return -1;

    m.unlock();
}
