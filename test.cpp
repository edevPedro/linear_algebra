#include <iostream>
#include <string>
#include <math.h>

#include "qbMatrix.h"

using namespace std;

template <class T>
void PrintMatrix(qbMatrix2<T> matrix) {
  int nRows = matrix.getNumRows();
  int nCols = matrix.getNumCols();
  for (int row = 0; row < nRows; ++row) {
    for (int col = 0; col < nCols; ++col) {
      cout << matrix.GetElement(row, col) << "  ";
    }
    cout << endl;
  }
}

int main(){
  cout << "Code to test qbMatrix2" << endl;

  double simpleData[12] = {1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0, 1.0, 2.0, 3.0};
  qbMatrix2<double> testMatrix(3, 4, simpleData);

  cout << endl << "**************************" << endl;
  cout << "4x3 matrix test (testMatrix)" << endl;
  PrintMatrix(testMatrix);

  cout << endl << "**************************" << endl;
  cout << "Element retrieval test" << endl;
  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 4; ++col) {
      cout << "testMatrix(" << row << ", " << col << ") = " << testMatrix.GetElement(row, col) << endl;
    }
  }

  cout << endl << "**************************" << endl;
  cout << "Matrix addition test" << endl;
  qbMatrix2<double> testMatrix2(4, 3, simpleData);
  qbMatrix2<double> sumMatrix = testMatrix + testMatrix2;
  PrintMatrix(sumMatrix);

  cout << endl << "**************************" << endl;
  cout << "Matrix subtraction test" << endl;
  qbMatrix2<double> diffMatrix = testMatrix - testMatrix2;
  PrintMatrix(diffMatrix);

  cout << endl << "**************************" << endl;
  cout << "Matrix * scalar test" << endl;
  qbMatrix2<double> multScalarMatrix = testMatrix * 2.0;
  PrintMatrix(multScalarMatrix);

  cout << endl << "**************************" << endl;
  cout << "Scalar * matrix test" << endl;
  qbMatrix2<double> scalarMultMatrix = 2.0 * testMatrix;
  PrintMatrix(scalarMultMatrix);

  cout << endl << "**************************" << endl;
  cout << "Matrix division test" << endl;
  qbMatrix2<double> divMatrix = testMatrix / testMatrix2;
  PrintMatrix(divMatrix);

  cout << endl << "**************************" << endl;
  cout << "Equality operator test" << endl;
  cout << "testMatrix == testMatrix2? " << (testMatrix == testMatrix2 ? "Yes" : "No") << endl;
  cout << "testMatrix == testMatrix? " << (testMatrix == testMatrix ? "Yes" : "No") << endl;

  cout << endl << "**************************" << endl;
  cout << "Matrix multiplication test" << endl;
  qbMatrix2<double> testMatrix3(4, 3, simpleData);
  qbMatrix2<double> resultMatrix = testMatrix * testMatrix3;
  PrintMatrix(resultMatrix);

  cout << endl << "**************************" << endl;
  cout << "Test multiplication of column vector by matrix" << endl;
  double columnData[3] = {1.0, 2.5, 3.5};
  double squareData[9] = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
  qbMatrix2<double> testColumn(3, 1, columnData);
  qbMatrix2<double> squareMatrix(3, 3, squareData);
  cout << "Column vector = " << endl;
  PrintMatrix(testColumn);
  cout << "Square matrix = " << endl;
  PrintMatrix(squareMatrix);
  cout << "Column vector * Square matrix = " << endl;
  PrintMatrix(testColumn * squareMatrix);
  cout << "Square matrix * Column vector = " << endl;
  PrintMatrix(squareMatrix * testColumn);

  cout << "Square matrix + 1.0" << endl;
  qbMatrix2<double> squareMatrix2 = squareMatrix + 1.0;
  PrintMatrix(squareMatrix2);

  cout << "(Square matrix + 1.0) * Column vector = " << endl;
  PrintMatrix(squareMatrix2 * testColumn);

  return 0;
}
