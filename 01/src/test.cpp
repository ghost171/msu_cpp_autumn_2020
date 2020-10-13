#include <iostream>
#include <cassert>
#include "../hpp/Alloc.hpp"

using namespace std;

void test1() {
    Allocator allocator1;
    allocator1.MakeAllocator(10);
    char *allocated = allocator1.Alloc(5);
    allocated[0] = '1';
    allocated[1] = 'j';
    allocated[2] = '_';
    assert(allocated[0] == '1' && allocated[1] == 'j' && allocated[2] == '_');
}

void test2() {
    Allocator allocator2;
    allocator2.MakeAllocator(1);
    char *allocated = allocator2.Alloc(1);
    allocated[0] = '.';
    assert(allocated[0] == '.');
}

void test3() {
    Allocator allocator3;
    allocator3.MakeAllocator(3);
    char *allocated = allocator3.Alloc(3);
    allocated[0] = '1';
    allocated[1] = 'j';
    allocated[2] = '_';
    assert(allocated[0] == '1' && allocated[1] == 'j' && allocated[2] == '_');
}

void test4() {
    Allocator allocator4;
    allocator4.MakeAllocator(5);
    char *allocated = allocator4.Alloc(6); //in this case we have to return nullpttr because of arg Alloc function > arg MakeAllocator function
    assert(allocated == nullptr);
} 

void test5() {
    Allocator allocator5;
    allocator5.MakeAllocator(5);
    char *allocated = allocator5.Alloc(5);
    allocated[0] = '1';
    allocated[1] = 'j';
    allocated[2] = '_';
    allocator5.MakeAllocator(5);
    allocated = allocator5.Alloc(5); 
    allocated[0] = '2';
    allocated[1] = 'i';
    allocated[2] = '+';
    assert(allocated[0] == '2' && allocated[1] == 'i' && allocated[2] == '+');
}

void test6() {
    Allocator allocator6;
    allocator6.MakeAllocator(3);
    char *allocated = allocator6.Alloc(3);
    allocated[0] = 'a';
    allocated[1] = 'b';
    allocated[2] = 'c';
    allocator6.Reset();
    allocated = allocator6.Alloc(3); 
    allocated[0] = '1';
    allocated[1] = '2';
    assert(allocated[0] == '1' && allocated[1] == '2' && allocated[2] == 'c');
}

void test7() {
    Allocator allocator7;
    allocator7.MakeAllocator(0);
    char *allocated = allocator7.Alloc(7);
    assert(allocated == nullptr);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    cout << "All tests was accepted." << endl;
    cout << "OK" << endl;
    return 0;
}