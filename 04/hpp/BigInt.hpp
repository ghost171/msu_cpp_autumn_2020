#pragma once
#include <iostream>

using namespace std;

class TBigInt {
private:
    long long int *Buffer;
    char Sign;
    long long int Size;
    const static long long int Base = 1000000000;
public:
    TBigInt();
    TBigInt(long long number);  
    TBigInt operator=(const TBigInt &number);
    TBigInt operator=(long long number);
    TBigInt(const TBigInt &number);
    TBigInt(const string &s);
    long long int GetSize() const;
    TBigInt operator*(long long int number) const;
    friend ostream& operator<<(ostream &out, const TBigInt &number) {
        if (number.Sign < 0) {
            out << "-";
        }
        if (number.Buffer == nullptr || number.Size == 0) {
            out << 0 << endl;
            return out;
        } else {
            if (number.Buffer[number.Size - 1] != 0) {
                out << number.Buffer[number.Size - 1];
            }
        }
        for (long long int i = number.Size - 2; i >= 0; i--) {
            out << number.Buffer[i];
        }
        return out;
    }
    TBigInt operator=(TBigInt &&number);
    TBigInt operator-() const;
    TBigInt operator+(TBigInt number); 
    TBigInt operator*(TBigInt number);
    TBigInt operator-(TBigInt number);
    bool operator<(const TBigInt &number) const;
    bool operator>(const TBigInt &number) const;
    bool operator<=(const TBigInt &number) const;
    bool operator>=(const TBigInt &number) const;
    bool operator!=(const TBigInt &number) const;
    bool operator==(const TBigInt &number) const;
    TBigInt(TBigInt &&number);
    TBigInt Abs();
    void EraseToZeroes();
    ~TBigInt() = default;
};