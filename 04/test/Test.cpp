#include <iostream>
#include <cassert>
#include "../hpp/BigInt.hpp"

using namespace std;

void test1() {
    TBigInt a = 1024;
    assert(a == 1024);
}

void test2() {
    TBigInt a("1024");
    TBigInt b;
    assert(a == 1024);
}

void test3() {
    TBigInt a = 1024;
    TBigInt b = 1025;
    TBigInt c = a + b;
    assert(c == 2049);
}

void test4() {
    TBigInt a = 1024;
    TBigInt b = 1025;
    TBigInt c = b - a;
    assert( c == 1);
}

void test5() {
    TBigInt a = 1024;
    TBigInt b = 1025;
    TBigInt c = a - b;
    assert( c == -1);
}

void test6() {
    TBigInt a = 1024;
    TBigInt b = 2;
    assert(a * b == 2048);
}

void test7() {
    TBigInt a = 20;
    TBigInt b = 40;
    TBigInt c = a * b;
    c = c + 2;
    assert(c == 802);
}

void test8() {
    TBigInt a = 1024;
    TBigInt b = -2;
    TBigInt c = a * b;
    assert(c == -2048);
}

void test9() {
    TBigInt a = 1024;
    TBigInt b;
    b = std::move(static_cast<TBigInt &&>(a));
    assert(1024);
}

void test10() {
    TBigInt a("123456789012345678901234567890");
    cout << a << endl;
}

void test11() {
    TBigInt a = 2;
    a = -a;
    assert(a == -2);
}

void test12() {
    TBigInt b = 78;
    TBigInt a(b);
    assert(a == 78);
}

void test13() {
    TBigInt a = static_cast<int>(0);
    cout << a;
}

void test14() {
    TBigInt a("99999999999999999999999");
    TBigInt b("99999999999999999999999");
    TBigInt c = a * b;
    cout << c << endl;
}

int main() {
    cout << "test1 ";
    test1();
    cout << "OK" << endl;
    cout << "test2 ";
    test2();
    cout << "OK" << endl;
    cout << "test3 ";
    test3();
    cout << "OK" << endl;
    cout << "test4 ";
    test4();
    cout << "OK" << endl;
    cout << "test5 ";
    test5();
    cout << "OK" << endl;
    cout << "test6 ";
    test6();
    cout << "OK" << endl;
    cout << "test7 ";
    test7();
    cout << "OK" << endl;
    cout << "test8 ";
    test8();
    cout << "OK" << endl;
    cout << "test9 ";
    test9();
    cout << "OK" << endl;
    cout << "test10 ";
    test10();
    cout << "OK" << endl;
    cout << "test11 ";
    test11();
    cout << "OK" << endl;
    cout << "test12 ";
    test12();
    cout << "OK" << endl;
    cout << "test13 ";
    test13();
    cout << "OK" << endl;
    cout << "test14 ";
    test14();
    cout << "OK" << endl;
    return 0;
}