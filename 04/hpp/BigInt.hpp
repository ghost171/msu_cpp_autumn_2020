#pragma once
#include <iostream>
#include "BigInt.hpp"

using namespace std;

class TBigInt {
private:
    int *Buffer;
    char Sign;
    int Size;
    const static int Base = 1000000000;
public:
    TBigInt();
    TBigInt(long long number);  
    void operator=(TBigInt &number);
    TBigInt operator=(long long number);
    TBigInt(const TBigInt &number);
    TBigInt(const string &s);
    int GetSize();
    TBigInt operator*(int number) const;
    friend ostream& operator<<(ostream &out, const TBigInt &number) {
        if (number.Sign < 0) {
            out << "-";
        }
        if (number.Buffer == NULL) {
            out << 0;
        } else {
            if (number.Buffer[number.Size - 1] != 0) {
                out << number.Buffer[number.Size - 1];
            }
        }
        for (int i = number.Size - 2; i >= 0; i--) {
            out << number.Buffer[i];
        }
        return out;
    }
    TBigInt operator-() const;
    TBigInt operator+(TBigInt number); 
    bool operator>=(TBigInt number);
    TBigInt operator*(TBigInt number);
    TBigInt operator-(TBigInt number);
    bool operator<(const TBigInt &number) const;
    bool operator>(const TBigInt &number) const;
    bool operator<=(const TBigInt &number) const;
    bool operator>=(const TBigInt &number) const;
    bool operator!=(const TBigInt &number) const;
    bool operator==(const TBigInt &number) const;
    void operator=(TBigInt &&number);
    TBigInt(TBigInt &&number);
    TBigInt Abs();
    void EraseToZeroes();

};