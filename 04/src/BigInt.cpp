#include <iostream>
#include "../hpp/BigInt.hpp"

using namespace std;

TBigInt::TBigInt(TBigInt &&number) {
    Size = move(number.Size);
    Sign = move(number.Sign);
    Buffer = move(number.Buffer);
}


void TBigInt::operator=(TBigInt &&number) {
    Size = move(number.Size);
    Sign = move(number.Sign);
    Buffer = move(number.Buffer);
}

TBigInt::TBigInt(const string &s) {
    Sign = 1;
    Buffer = NULL;
    int position = 0;
    while ((position < s.size()) && ((s[position] == '-') || (s[position] == '+'))) {
        if (s[position] == '-') {
            Sign = -Sign;
        }
        ++position;
    }
    for (int i = s.size() - 1, k = 0; i >= position; i -= 9, k++) {
        int x = 0;
        for (int j = max(position, i - 8); j <= i; j++) {
            x = x * 10 + s[j] - '0';
        }
        Buffer = (int *)realloc(Buffer, (k + 1) * sizeof(int));
        Buffer[k] = x;
        Size = k + 1;
    }
}

TBigInt::TBigInt() {
    Sign = 1;
    Buffer = NULL;
    Size = 0;
}

bool TBigInt::operator<(const TBigInt &number) const {
    if (Sign != number.Sign) {
        return (Sign < number.Sign);
    }
    for (int i = Size - 1; i >= 0; i--) {
        if (Buffer[i] != number.Buffer[i]) {
            return ((Buffer[i] * Sign) < (number.Buffer[i] * Sign));
        }
    }
    return false;
}

bool TBigInt::operator==(const TBigInt &number) const {
    return (!(*this < number) && !(number < *this));
}

bool TBigInt::operator!=(const TBigInt &number) const {
    return ((*this < number) || (number < *this));
}

int TBigInt::GetSize() {
    return Size;
}

bool TBigInt::operator<=(const TBigInt &number) const {
    return !(number < *this);
}

bool TBigInt::operator>(const TBigInt &number) const {
    return number < *this;
}

bool TBigInt::operator>=(const TBigInt &number) const {
    return !(*this < number);
}

TBigInt::TBigInt(long long number) {
    *this = number;
}

TBigInt::TBigInt(const TBigInt &number) {
    Sign = number.Sign;
    Buffer = new int [number.Size];
    for (int i = 0; i < number.Size; i++) {
        Buffer[i] = number.Buffer[i];
    }
    Size = number.Size;
}

void TBigInt::operator=(TBigInt &number) {
    Sign = number.Sign;
    Buffer = new int [number.Size];
    for (int i = 0; i < number.Size; i++) {
        Buffer[i] = number.Buffer[i];
    }
    Size = number.Size;
}

TBigInt TBigInt::operator=(long long number) {
    Sign = 1;
    if (number < 0) {
        Sign = -1;
        number = -number;
    }
    int i = 0;
    Buffer = NULL;
    for (;number > 0; number = number / Base) { 
        i++;
        Buffer = (int *)realloc(Buffer, i * sizeof(int));
        Buffer[i - 1] = number % Base;
    }
    Size = i + 1;
    return *this;
}

TBigInt TBigInt::operator-() const {
    TBigInt result = *this;
    result.Sign = -Sign;
    return result;
}
 

TBigInt TBigInt::operator+(TBigInt number) {
    if (Sign == number.Sign) {
        TBigInt result = TBigInt(number);
        for (int i = 0, carry = 0; i < max(number.Size, Size) || carry; i++) {
            if (i == result.Size) {
                result.Size++;
                result.Buffer = (int *)realloc(Buffer, (i + 1) * sizeof(int));
                result.Buffer[i] = 0;
            }
            result.Buffer[i] += carry + (i < Size ? Buffer[i] : 0);
            carry = result.Buffer[i] >= Base;
            if (carry) {
                result.Buffer[i] -= Base;
            }
        }
        return result;
    }
    return *this - (-number);
}

TBigInt TBigInt::operator-(TBigInt number) {
    if (Sign == number.Sign) {
        if (Abs() >= number.Abs()) {
            TBigInt result = *this;
            for (int i = 0, carry = 0; i  < number.Size; i++) {
                result.Buffer[i] -= carry + (i < number.Size ? number.Buffer[i] : 0);
                carry = result.Buffer[i] < 0;
                if (carry) {
                    result.Buffer[i] += Base;
                }
            }
            result.EraseToZeroes();
            return result;
        }    
        return -(number - *this);
    }
    return *this + (-number);
}

TBigInt TBigInt::Abs() {
    TBigInt result = *this;
    result.Sign *= result.Sign;
    return result;
}

bool TBigInt::operator>=(TBigInt number) {
    return (!(*this < number));
}

void TBigInt::EraseToZeroes() {
    while (Buffer != NULL && Buffer[Size - 1] != 0) {
        Buffer = (int *)realloc(Buffer, (Size - 1) * sizeof(int));
        Size--;
    }
    if (Buffer == NULL) {
        Sign = 1;
    }
}

TBigInt TBigInt::operator*(TBigInt number) {
    TBigInt result;
    result.Size = Size + number.Size;
    result.Buffer = new int [result.Size];
    for (int i = 0; i < Size; i++) {
        for (int j = 0, carry = 0; j < number.Size || carry; j++) {
            long long cur = result.Buffer[i + j] + static_cast<long long int>(Buffer[i]) * static_cast<long long int>(j < number.Size ? number.Buffer[j] : 0) + carry;
            result.Buffer[i + j] = cur % Base;
            carry = cur / Base;
        }
    }
    while(result.Size > 1 && result.Buffer[Size - 1] == 0) {
        result.Buffer = (int *)realloc(result.Buffer, (result.Size - 1) * sizeof(int));
        result.Size--;
    }
    if (Sign * number.Sign < 0) {
        result.Sign = -1;   
    } else {
        Sign = 1;
    }
    return result;
}