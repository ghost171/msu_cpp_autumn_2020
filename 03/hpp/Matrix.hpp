#pragma once
#include <iostream>

class TMatrix {
private:
    size_t Rows = 5;
    size_t Columns = 5;
    int **Matrix;

public:
    class TRow {
    private:
        friend class TMatrix;
        TMatrix &Parent;
        int RowOfTRow;
        TRow(TMatrix &parent, int row) : Parent(parent), RowOfTRow(row) {}
    public:
        int &operator[](const int &col);
        const int &operator[](const int &col) const;
    };
    TMatrix &operator=(const TMatrix &secondMatrix);
    TMatrix operator*=(const int &number);
    TMatrix operator+(TMatrix secondMatrix) const;
    bool operator==(TMatrix secondMatrix) const;
    bool operator!=(TMatrix secondMatrix) const;
    TRow operator[](const int &row);
    TMatrix(const TMatrix &p2);
    TMatrix(size_t rows, size_t columns);
    TMatrix();
    void OutStream(std::ostream &stream) const;
    size_t GetRows() const;
    size_t GetColumns() const;
    ~TMatrix();
};

std::ostream &operator<<(std::ostream &stream, TMatrix &OutMatrix);