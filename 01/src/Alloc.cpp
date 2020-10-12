#include "../hpp/Alloc.hpp"
#include <iostream>

using namespace std;

Allocator::Allocator() : StartPointer(nullptr), Offset(0), MaxSize(0) {}; 

Allocator::~Allocator() {
    if (StartPointer) {
        delete[] StartPointer;
    }
}

char *Allocator::Alloc (size_t size) {
    if (!StartPointer) {
        cout << "You give empty Pointer. Please allocate memory in MakeAllocator()." << endl;
        return nullptr;
    } else  if ((size + Offset) > MaxSize) {
        cout << "You claimed more memory that you had allocated, nullptr returned. Allocate more memory in MakeAllocator()" << endl;
        return nullptr;
    }
    char *allocatedMemory = StartPointer + Offset;
    Offset += size;
    return allocatedMemory;
}

void Allocator::MakeAllocator(size_t maxSize) {
    if (maxSize == 0) {
        StartPointer = nullptr;
    } else {
        StartPointer = new char[maxSize];
    }
    Offset = 0;
    MaxSize = maxSize;
}

void Allocator::Reset() {
    Offset = 0;
}