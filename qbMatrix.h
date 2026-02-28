#ifndef QBMATRIX2_H 
#define QBMATRIX2_H

template <class T>
class qbMatrix2{
  public:
    //Define the various constructors
    qbMatrix2();
    qbMatrix2(int nRows, int nCols);
    qbMatrix2(int nRows, int nCols, const T *inputData);
    qbMatrix2(const qbMatrix2<T>& inputMatrix);

    //and the destructor
    ~qbMatrix2();

    //Configuration methods
    bool resize(int numRows, int numCols);

    //Element access methods
    T GetElement(int row, int col);
    bool setElement(int row, int col, T elementValue);
    int getNumRows();
    int getNumCols();

    //Overload == operator
    bool operator== (const qbMatrix2<T>& rhs)

#endif 
