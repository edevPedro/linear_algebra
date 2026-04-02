#ifndef QBMATRIX2_H
#define QBMATRIX2_H

#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <math.h>
#include <vector>

template <class T>
class qbMatrix2 {
public:
    // Define the various constructors
    qbMatrix2();
    qbMatrix2(int nRows, int nCols);
    qbMatrix2(int nRows, int nCols, const T *inputData);
    qbMatrix2(const qbMatrix2<T>& inputMatrix);
    qbMatrix2(int nRows, int nCols, const std::vector<T>& inputData);

    ~qbMatrix2();

    // Configuration methods
    bool resize(int numRows, int numCols);

    // Element access methods
    T GetElement(int row, int col);
    bool setElement(int row, int col, T elementValue);
    int getNumRows();
    int getNumCols();

    // Overload == operator
    bool operator== (const qbMatrix2<T>& rhs);

    // Overload +, -, and * operators (friends)
    template <class U> friend qbMatrix2<U> operator+ (const qbMatrix2<U>& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator+ (const U& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator+ (const qbMatrix2<U>& lhs, const U& rhs);

    template <class U> friend qbMatrix2<U> operator- (const qbMatrix2<U>& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator- (const U& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator- (const qbMatrix2<U>& lhs, const U& rhs);

    template <class U> friend qbMatrix2<U> operator* (const qbMatrix2<U>& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator* (const U& lhs, const qbMatrix2<U>& rhs);
    template <class U> friend qbMatrix2<U> operator* (const qbMatrix2<U>& lhs, const U& rhs);

    private:
      int Sub2Ind(int row, int col);

    private:
      T *m_matrixData;
      int m_nRows, m_nCols, m_nElements;
};

//The default constructor
template <class T>
qbMatrix2<T>::qbMatrix2(){
  m_nRows = 1;
  m_nCols = 1;
  m_nElements = 1;
  m_matrixData = new T[m_nElements];
  m_matrixData[0] = 0.0;
}

//Construct empty matrix (All elements 0)
template <class T>
qbMatrix2<T>::qbMatrix2(int nRows, int nCols){
  m_nRows = nRows;
  m_nCols = nCols;
  m_nElements = m_nRows * m_nCols;
  m_matrixData = new T[m_nElements];
  for (int i=0; i<m_nElements; i++){
    m_matrixData[i] = 0.0;
  }

}

//Construct from const linear array.
template <class T>
qbMatrix2<T>::qbMatrix2(int nRows, int nCols, const T *inputData){
  m_nRows = nRows;
  m_nCols = nCols;
  m_nElements = m_nRows * m_nCols;
  m_matrixData = new T[m_nElements];
  for (int i=0; i<m_nElements; i++){
    m_matrixData[i] = inputData[i];
  }
}

//Copy constructor
template <class T>
qbMatrix2<T>::qbMatrix2(const qbMatrix2<T>& inputMatrix){
  m_nRows = inputMatrix.m_nRows;
  m_nCols = inputMatrix.m_nCols;
  m_nElements = inputMatrix.m_nElements;
  m_matrixData = new T[m_nElements];
  for (int i=0; i<m_nElements; i++){
    m_matrixData[i] = inputMatrix.m_matrixData[i];
  }
}

// Construct from std::vector
template <class T>
qbMatrix2<T>::qbMatrix2(int nRows, int nCols, const std::vector<T>& inputData){
  m_nRows = nRows;
  m_nCols = nCols;
  m_nElements = nRows * nCols;
  m_matrixData = new T[m_nElements];
  for (int i=0; i<m_nElements; ++i){
    m_matrixData[i] = inputData->at(i);
  }
}

//Destructor
template <class T>
qbMatrix2<T>::~qbMatrix2(){
  if (m_matrixData != nullptr){
    delete [] m_matrixData;
  }
}

/*********************************
CONFIGURATION FUNCTIONS
**********************************/
template <class T>
bool qbMatrix2<T>::resize(int numRows, int numCols){
  m_nRows = numRows;
  m_nCols = numCols;
  m_nElements = m_nRows * m_nCols;
  delete [] m_matrixData;
  m_matrixData = new T[m_nElements];
  if (m_matrixData != nullptr){
    for (int i=0; i<m_nElements; i++){
      m_matrixData[i] = 0.0;
    }
    return true;
  }
    return false;
  }


  /*********************************
   ELEMENT FUNCTIONS
  **********************************/

  template <class T>
  T qbMatrix2<T>::GetElement(int row, int col){
  int linearIndex = Sub2Ind(row, col);
  if (linearIndex >= 0){
    return m_matrixData[linearIndex];
  }
  return 0.0;
}

template <class T>
bool qbMatrix2<T>::setElement(int row, int col, T elementValue){
  int linearIndex = Sub2Ind(row, col);
  if (linearIndex >= 0){
    m_matrixData[linearIndex] = elementValue;
    return true;
  }
  return false;
}

template <class T>
int qbMatrix2<T>::getNumRows(){
  return m_nRows;
}

template <class T>
int qbMatrix2<T>::getNumCols(){
  return m_nCols;
}


/*********************************
OVERLOADED OPERATOR FUNCTIONS
**********************************/


/*********************************
THE + OPERATOR
**********************************/
// matrix + matrix
template <class T>
qbMatrix2<T> operator+ (const qbMatrix2<T>& lhs, const qbMatrix2<T>& rhs){
 int numRows = lhs.m_nRows;
 int numCols = lhs.m_nColsRows;
 int numElements = numRows * numCols;
 T *tempResult = new T[numElements];
 for (int i; i<numElements; i++){
   tempResult[i] = lhs.m_matrixData[i] + rhs.m_matrixData[i];
 }

 qbMatrix2<T> result(numRows, numCols, tempResult);
 delete[] tempResult;
 return result;
}

//scaler + matrix
template <class T>
qbMatrix2<T> operator+ (const T& lhs, const qbMatrix2<T>& rhs){
  int numRows = rhs.m_nRows;
  int numCols = rhs.m_nCols;
  int numElements = numRows * numCols;
  T *tempResult = new T[numElements];
  for (int i=0; i<numElements; i++){
    tempResult[i] = lhs + rhs.m_matrixData[i];
  }
  qbMatrix2<T> result(numRows, numCols, tempResult);
  delete[] tempResult;
  return result;
}

//matrix + scaler
template <class T>
qbMatrix2<T> operator+ (const qbMatrix2<T>& lhs, const T& rhs){
  int numRows = lhs.m_nRows;
  int numCols = lhs.m_nCols;
  int numElements = numRows * numCols;
  T *tempResult = new T[numElements];
  for (int i=0; i<numElements; i++){
    tempResult[i] = lhs.m_matrixData[i] + rhs;
  }
  qbMatrix2<T> result(numRows, numCols, tempResult);
  delete[] tempResult;
  return result;
}


/*********************************
THE - OPERATOR
**********************************/
//matrix - matrix
template <class T>
qbMatrix2<T> operator- (const qbMatrix2<T>& lhs, const qbMatrix2<T>& rhs){
  int numRows = lhs.m_nRows;
  int numCols = lhs.m_nCols;
  int numElements = numRows * numCols;
  T *tempResult = new T[numElements];
  for (int i=0; i<numElements; ++i){
    tempResult[i] = lhs.m_matrixData[i] - rhs.m_matrixData[i];
  }
  qbMatrix2<T> result(numRows, numCols, tempResult);
  delete[] tempResult;
  return result;
}

//scaler - matrix
template <class T>
qbMatrix2<T> operator- (const T& lhs, const qbMatrix2<T>& rhs){
  int numRows = rhs.m_nRows;
  int numCols = rhs.m_nCols;
  int numElements = numRows * numCols;
  T *tempResult = new T[numElements];
  for (int i=0; i<numElements; ++i){
    tempResult[i] = lhs - rhs.m_matrixData[i];
  }
  qbMatrix2<T> result(numRows, numCols, tempResult);
  delete[] tempResult;
  return result;
}

//matrix - scaler
template <class T>
qbMatrix2<T> operator- (const qbMatrix2<T>& lhs, const T& rhs){
  int numRows = lhs.m_nRows;
  int numCols = lhs.m_nCols;
  int numElements = numRows * numCols;
  T *tempResult = new T[numElements];
  for (int i=0; i<numElements; ++i){
    tempResult[i] = lhs.m_matrixData[i] - rhs;
  }
  qbMatrix2<T> result(numRows, numCols, tempResult);
  delete[] tempResult;
  return result;
}

/*********************************
THE * OPERATOR
**********************************/

// matrix * matrix
template <class T>
qbMatrix2<T> operator* (const qbMatrix2<T>& lhs, const qbMatrix2<T>& rhs){
  int l_numRows = lhs.m_nRows;
  int l_numCols = lhs.m_nCols;
  int r_numRows = rhs.m_nRows;
  int r_numCols = rhs.m_nCols;
  if (l_numCols == r_numRows){
    T *tempResult = new T[lhs.m_nRows * rhs.m_nCols];

    for (int lhsRow=0; lhsRow<l_numRows; lhsRow++){
      for (int rhsCol=0; rhsCol<r_numCols; rhsCol++){
        T elementResult = 0.0;
        for (int lhsCol=0; lhsCol<l_numCols; lhsCol++){
          // Compute the LHS linear index
          int lhsLinearIndex = (lhsRow * l_numCols) + lhsCol;

          // Compute the RHS linear index (based on LHS col)
          // rhs row number equal lhs column number
          int rhsLinearIndex = (lhsCol * r_numCols) + rhsCol;

          // Performance calculation on these elements
          elementResult += (lhs.m_matrixData[lhsLinearIndex] * rhs.m_matrixData[rhsLinearIndex]);
        }
        // Store the result
        int resultLinearIndex = (lhsRow * r_numCols) + rhsCol;
        tempResult[resultLinearIndex] = elementResult;
      }
    }
    qbMatrix2<T> result(l_numRows, r_numCols, tempResult);
    delete[] tempResult;
    return result;
  }
  else {
    qbMatrix2<T> result(1, 1);
    return result;
  }
}

// matrix * scaler
// template <class T>
// qbMatrix2<T> operator* (const qbMatrix2<T>& lhs, const T& rhs){
//   int numRows = lhs.m_nRows;
//   int numCols = lhs.m_nCols;
//   int numElements = numRows * numCols;
//   T *tempResult = new T[numElements];
//   for (int i=0; i<numElements; ++i){
//     tempResult[i] = lhs.m_matrixData[i] * rhs;
//   }
//   qbMatrix2<T> result(numRows, numCols, tempResult);
//   delete[] tempResult;
//   return result;
// }

// // scaler * matrix
// template <class T>
// qbMatrix2<T> operator* (const T& lhs, const qbMatrix2<T>& rhs){
//   int numRows = rhs.m_nRows;
//   int numCols = rhs.m_nCols;
//   int numElements = numRows * numCols;
//   T *tempResult = numRows * numCols;
//   for (int i=0; i<numElements; ++i){
//     tempResult[i] = lhs * rhs.m_matrixData[i];
//   }
//   qbMatrix2<T> result(numRows, numCols, tempResult);
//   delete[] tempResult;
//   return result;
// }

/*********************************
THE / OPERATOR
**********************************/

// matrix / matrix
template <class T>
qbMatrix2<T> operator/ (const qbMatrix2<T>& lhs, const qbMatrix2<T>& rhs){
  int numRows = lhs.m_nRows;
  int numCols = lhs.m_nCols;
  int numElements = numRows * numCols;
  T *tempResult = new T[numElements];
  for (int i=0; i<numElements; ++i){
    tempResult[i] = lhs.m_matrixData[i] / rhs.m_matrixData[i];
  }
  qbMatrix2<T> result(numRows, numCols, tempResult);
  delete[] tempResult;
  return result;
}



#endif
