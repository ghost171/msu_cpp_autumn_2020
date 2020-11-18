#include <iostream>
#include <cassert>
#include "../hpp/Formatizer.hpp"

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
    assert(text == "two*2+1.000000=5");
}

void test8() {
    string text = format("{1", 2);
    assert(text == "{1" );
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
    return 0;
}