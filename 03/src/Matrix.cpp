#include <iostream>
#include "../hpp/Matrix.hpp"

using namespace std;

TMatrix::TMatrix(const TMatrix &p2) : TMatrix(p2.Rows, p2.Columns) {
    *this = p2;
}

TMatrix &TMatrix::operator=(const TMatrix &secondMatrix) {
    for (int i = 0; i < Rows; ++i)
        for (int j = 0; j < Columns; ++j)
            Matrix[i][j] = secondMatrix.Matrix[i][j];
    return *this;
}

int& TMatrix::TRow::operator[](const int &col) {
    if(col >= Parent.GetColumns()) {
        throw std::out_of_range("OUT_OF_RANGE_ERROR.");
    }
    return Parent.Matrix[RowOfTRow][col];
}

TMatrix::TRow TMatrix::operator[](const int &row) {
    if(row >= GetRows()) {
        throw std::out_of_range("OUT_OF_RANGE_ERROR.");
    }
    return TRow(*this, row);
}

ostream &operator<<(ostream &stream, TMatrix &OutMatrix) {
    for (int i = 0; i < OutMatrix.GetRows(); i++) {
        for (int j = 0; j < OutMatrix.GetColumns(); j++) {
            stream << OutMatrix[i][j] << " ";
        }
        stream << endl;
    }
    return stream;
}

void TMatrix::operator*=(const int &number) {
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            Matrix[i][j] *= number;
        }
    }
}

size_t TMatrix::GetColumns() const {
    return Columns;
}

size_t TMatrix::GetRows() const {
    return Rows;
}

TMatrix::TMatrix() {
    Matrix = new int *[Rows];
    for (int i = 0; i < Rows; i++) {
        Matrix[i] = new int[Columns];
    }
}

TMatrix::TMatrix(size_t rows, size_t columns) : Rows(rows), Columns(columns) {
    Matrix = new int *[Rows];
    for (int i = 0; i < Rows; i++) {
        Matrix[i] = new int[Columns];
    }
}

TMatrix::~TMatrix() {
    for (int i = 0; i < Rows; i++) {
        delete[] Matrix[i];
    }
    delete[] Matrix;
}

void TMatrix::OutStream(ostream &stream) const {
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            stream << Matrix[i][j] << " ";
        }
        stream << endl;
    }
}

TMatrix TMatrix::operator+(TMatrix secondMatrix) const {
    if (Rows != secondMatrix.GetRows()) {
        cout << "Error in sum of matrix. Rows of matrix don't equal." << endl;
        return *this;
    }
    if (Columns != secondMatrix.GetColumns()) {
        cout << "Error in sum of matrix. Columns of matrix don't equal." << endl;
        return *this;
    }
    TMatrix sumMatrix(Rows, Columns);
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            sumMatrix[i][j] = Matrix[i][j] + secondMatrix[i][j];
        }
    }
    return sumMatrix;
}

bool TMatrix::operator==(TMatrix secondMatrix) {
    if (Rows != secondMatrix.GetRows()) {
        return false;
    }
    if (Columns != secondMatrix.GetColumns()) {
        return false;
    }
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            if (Matrix[i][j] != secondMatrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}