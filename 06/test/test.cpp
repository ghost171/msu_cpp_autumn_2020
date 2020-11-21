#include <iostream>
#include <cassert>
#include <iomanip>
#include "../hpp/Formatizer.hpp"

class Date
{
    int mo, da, yr;
public:
    Date(int m, int d, int y)
    {
        mo = m; da = d; yr = y;
    }
    friend ostream& operator<<(ostream& os, const Date& dt);
};

ostream& operator<<(ostream& os, const Date& dt)
{
    os << dt.mo << '/' << dt.da << '/' << dt.yr;
    return os;
}


void test1() {
    auto text = format("{1}+{1} = {0}", 2, "one");
    assert(text == "one+one = 2");
}

void test2() {
    auto text = format("{1}{1} = {0}", 4.0, 2, "LLL");
    cout << text << endl;
}

void test3() {
    cout << format("{0}{0}={1}", 0.5, "0.25") << endl;
}

void test4() {
    auto text = format("{1}{1}{2}{3} = {0}", 4.0, 2);
}

void test5() {
    auto text = format("{1}+{1}{one} = {0}", 2, 1);
}

void test6() {
    auto text = format("{1{1}}+{1} = {0}", 2, 1);
}

void test7() {
    string text = format("{1}*{2}+{3}={0}","5", "two", 2, 1.0);
    cout << text << endl;
    assert(text == "two*2+1=5");
}

void test8() {
    string text = format("{1", 2);
    assert(text == "{1" );
}

void test9() {
    Date dt(5, 6, 92);
    string text = format("{0}", dt);
    assert(text == "5/6/92");
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
    return 0;
}