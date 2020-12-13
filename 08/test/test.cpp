#include <iostream>
#include "../hpp/ThreadPool.hpp"
#include <cassert>

using namespace std;

struct A {};

int foo1(int a) { return a; }

void foo2() {
    cout << "exec" << endl; 
}

void foo3(const A&) {
    cout << "Structure getted" << endl;
}

void test1() {
    TThreadPool pool(2);
    auto x = pool.Exec(foo1, 2);
    auto y = pool.Exec(foo1, 3);
    assert(x.get() == 2 && y.get() == 3);
}

void test2() {
    TThreadPool pool(2);
    int task1 = (pool.Exec([]() { return 1; })).get();
    assert(task1 == 1);
}

void test3() {
    TThreadPool pool(2);
    auto task1 = (pool.Exec([]() { return "exec3"; }));
    string answer = task1.get();
    assert(answer == "exec3");
}

void test4() {
    TThreadPool pool(2);
    auto task1 = pool.Exec([]() { cout << "exec4" << endl; });
}

void test5() {
    TThreadPool pool(6);
    pool.Exec(foo2);
    pool.Exec(foo2);
    pool.Exec(foo2);
    pool.Exec(foo2);
    pool.Exec(foo2);
    pool.Exec(foo2);
}

void test6() {
    TThreadPool pool(6);
    auto task1 = pool.Exec(foo3, A());

}

void test7() {
    TThreadPool pool(9);
    pool.Exec(foo2);
    pool.Exec(foo2);
    pool.Exec(foo2);
    pool.Exec(foo1, 4);
    pool.Exec(foo1, 6);
    pool.Exec(foo3, A());
    pool.Exec(foo3, A());
    pool.Exec(foo3, A());
}

int main() 
{ 
    cout << "Test1 " << endl;
    test1();
    cout << "OK" << endl;
    cout << "Test2 " << endl;
    test2();
    cout << "OK" << endl;
    cout << "Test3 " << endl;
    test3();
    cout << "OK" << endl;
    cout << "Test4 " << endl;
    test4();
    cout << "OK" << endl;
    cout << "Test5 " << endl;
    test5();
    cout << "OK" << endl;
    cout << "Test6 " << endl;
    test6();
    cout << "OK" << endl;
    cout << "Test7 " << endl;
    test7();
    cout << "OK" << endl;
    return 0; 
} 