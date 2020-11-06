#include <iostream>
#include <cstring>
#include "../hpp/BigInt.hpp"

using namespace std;

TBigInt::TBigInt(TBigInt &&number) {
    Size = number.Size;
    Sign = number.Sign;
    swap(Buffer,number.Buffer);
}

TBigInt TBigInt::operator=(TBigInt &&number) {
    Size = number.Size;
    Sign = number.Sign;
    swap(Buffer,number.Buffer);
    return *this;
}

TBigInt::TBigInt(const string &s) {
    Sign = 1;
    Buffer = nullptr;
    long long int position = 0;
    while ((position < s.size()) && ((s[position] == '-') || (s[position] == '+'))) {
        if (s[position] == '-') {
            Sign = -Sign;
        }
        ++position;
    }
    for (long long int i = s.size() - 1, k = 0; i >= position; i -= 9, k++) {
        long long int x = 0;
        for (long long int j = max(position, i - 8); j <= i; j++) {
            x = x * 10 + s[j] - '0';
        }
        if (Buffer == nullptr) {
            Buffer = static_cast<long long int *>(malloc((k + 1) * sizeof(long long int)));    
        } else {
            Buffer = static_cast<long long int *>(realloc(Buffer, (k + 1) * sizeof(long long int)));
        }
        Buffer[k] = x;
        Size = k + 1;
    }
}

TBigInt::TBigInt() {
    Sign = 1;
    Buffer = nullptr;
    Size = 0;
}

bool TBigInt::operator<(const TBigInt &number) const {
    for (long long int i = Size; i >= 0; i--) {
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

long long int TBigInt::GetSize() const {
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
    if (Buffer != nullptr) {
        Buffer = static_cast<long long int *>(realloc(number.Buffer, number.Size * sizeof(long long int)));
    } else {
        Buffer = static_cast<long long int *>(malloc(number.Size * sizeof(long long int)));
    }
    for (long long int i = 0; i < number.Size; i++) {
        Buffer[i] = number.Buffer[i];
    }
    Size = number.Size;
}


TBigInt TBigInt::operator=(const TBigInt &number) {
    if (*this != number) {
        Sign = number.Sign;
        if (Buffer != nullptr) {
            free(Buffer);
        }
        if (Buffer != nullptr) {
            Buffer = static_cast<long long int *>(realloc(Buffer, number.Size * sizeof(long long int)));    
        } else {
            Buffer = static_cast<long long int *>(malloc(number.Size * sizeof(long long int)));    
        }
        for (long long int i = 0; i < number.Size; i++) {
            Buffer[i] = number.Buffer[i];
        }
        Size = number.Size;
    }
    return *this;
}

TBigInt TBigInt::operator=(long long number) {
    Sign = 1;
    if (number < 0) {
        Sign = -1;
        number = -number;
    }
    long long int i = 0;
    Buffer = nullptr;
    if (number == 0) {
        Size = 0;
        return *this;
    }
    for (;number > 0; number = number / Base) { 
        i++;
        if (Buffer == nullptr) {
            Buffer = static_cast<long long int *>(malloc(i * sizeof(long long int)));    
        } else {
            Buffer = static_cast<long long int *>(realloc(Buffer, i * sizeof(long long int)));
        }
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
        TBigInt result = number;
        for (long long int i = 0, carry = 0; i < max(number.Size, Size) || carry; i++) {
            if (i == result.Size) {
                result.Size++;
                if (result.Buffer == nullptr) {
                    result.Buffer = static_cast<long long int *>(malloc((i + 1) * sizeof(long long int)));    
                } else {
                    result.Buffer = static_cast<long long int *>(realloc(Buffer, (i + 1) * sizeof(long long int)));
                }
                result.Buffer[i] = 0;
            }
            result.Buffer[i] += carry + (i < Size ? Buffer[i] : 0);
            carry = result.Buffer[i] >= Base;
        }
        return result;
    }
    return *this - (-number);
}

TBigInt TBigInt::operator-(TBigInt number) {
    if (Sign == number.Sign) {
        if (Abs() >= number.Abs()) {
            TBigInt result = *this;
            for (long long int i = 0, carry = 0; i  < number.Size || carry; i++) {
                result.Buffer[i] -= carry + (i < number.Size ? number.Buffer[i] : 0);
                carry = result.Buffer[i] < 0;
                if (carry) {
                    result.Buffer[i] += Base;
                }
            }
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

void TBigInt::EraseToZeroes() {
    while (Buffer != nullptr && Buffer[Size - 1] != 0) {
        Buffer = static_cast<long long int *>(realloc(Buffer, (Size - 1) * sizeof(long long int)));
        Size--;
        if (Size == 0) {
            Buffer = nullptr;
        }
    }
    if (Buffer == nullptr) {
        Sign = 1;
    }
}

TBigInt TBigInt::operator*(TBigInt number) {
    TBigInt result;
    result.Size = Size + number.Size;
    if (result.Buffer == nullptr) {
        result.Buffer = static_cast<long long int *>(malloc(result.Size * sizeof(long long int)));    
    } else {
        result.Buffer = static_cast<long long int *>(realloc(result.Buffer, result.Size * sizeof(long long int)));
    }
    for (long long int i = 0; i < Size; i++) {
        for (long long int j = 0, carry = 0; j < number.Size || carry; j++) {
            long long cur = result.Buffer[i + j] + static_cast<long long int>(Buffer[i]) * static_cast<long long int>(j < number.Size ? number.Buffer[j] : 0) + carry;
            result.Buffer[i + j] = cur % Base;
            carry = cur / Base;
        }
    }
    while(result.Size > 1 && result.Buffer[Size - 1] == 0) {
        if (result.Buffer == nullptr) {
            result.Buffer = static_cast<long long int *>(malloc((result.Size - 1) * sizeof(long long int)));    
        } else {
            result.Buffer = (long long int *)realloc(result.Buffer, (result.Size - 1) * sizeof(long long int));
        }
        result.Size--;
        if (result.Size == 0) {
            result.Buffer = nullptr;
        }
    }
    if (Sign * number.Sign < 0) {
        result.Sign = -1;   
    } else {
        Sign = 1;
    }
    return result;
}