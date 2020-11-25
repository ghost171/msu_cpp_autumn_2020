#include <iostream>
#include <memory>
#include <cassert>
#include "../hpp/vector.hpp"

using namespace std;

void test1() {
    TVector<int> a;
    a.PushBack(300);
    a.PushBack(2);
    a.PushBack(3);
    a.PushBack(4);
    a.PushBack(5);
    for (TIterator<int> iterator = a.Begin(); iterator != a.End(); iterator++) { 
        cout << *iterator << " "; 
    }
    cout << endl;
    assert(a[0] == 300 && a[1] == 2 && a[2] == 3 && a[3] == 4 && a[4] == 5);
}

void test2() {
    TVector<int> a;
    a.PushBack(300);
    a.PushBack(2);
    a.PushBack(3);
    a.PushBack(4);
    a.PushBack(5);
    a[5];
}

void test3() {
    TVector<string> a;
    a.PushBack("-1");
    a.PushBack("2");
    a.PushBack("a");
    a.PushBack("abcd");
    assert(a.Empty() == 0);
    assert(a.GetCapacity() == 4);
}

void test4() {
    TVector<double> a;
    a.Reserve(10);
    a.PushBack(-1);
    a.PushBack(2);
    a.PushBack(0.3);
    a.PushBack(4.2);
    assert(a.Empty() == 0);
    assert(a.GetCapacity() == 10);
}

void test5() {
    TVector<float> a;
    a.PushBack(-0.3);
    a.PushBack(0.3);
    a.PushBack(0.3);
    a.PushBack(4.2);
    a.Clear();
    assert(a.Empty() == 1);
    assert(a.Size() == 0);
}

void test6() {
    TVector<int> a;
    a.PushBack(300);
    a.PushBack(2);
    a.PushBack(3);
    a.PushBack(4);
    a.PushBack(5);
    a.PopBack();
    a.PushBack(400);
    assert(a[4] == 400);
}

void test7() {
    TAllocator<int> a1;
    int *a = a1.Allocate(1);
    a1.Construct(a, 7);
    assert(a[0] == 7);
    a1.Deallocate(a, 1);
}

void test8() {
    TVector<int> a;
    a.PushBack(300);
    a.PushBack(2);
    a.PushBack(3);
    a.PushBack(4);
    a.PushBack(5);
    a.EmplaceBack(1, 400);
    a.EmplaceBack(5, 300);
    for (TIterator<int> i = a.Begin(); i != a.End(); ++i) { 
        cout << *i << " "; 
    }
    assert(a[1] == 400 && a[5] == 300);
}

int main()
{
    cout << "Test1 "; 
    test1();
    cout << "OK" << endl;
    cout << "Test2 "; 
    test2();
    cout << "OK" << endl;
    cout << "Test3 "; 
    test3();
    cout << "OK" << endl;
    cout << "Test4 "; 
    test4();
    cout << "OK" << endl;
    cout << "Test5 "; 
    test5();
    cout << "OK" << endl;
    cout << "Test6 "; 
    test6();
    cout << "OK" << endl;
    cout << "Test7 "; 
    test7();
    cout << "OK" << endl;
    cout << "Test8 "; 
    test8();
    cout << "OK" << endl;
    return 0;
}