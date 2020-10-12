#include <iostream>

enum ERROR {
    ERR_BAD_SIZE,
    ERR_NULL_HEAP,
    ERR_NO_HEAP_MEM
};

class Allocator {
private:
    size_t MaxSize;
    char *StartPointer;
    size_t Offset;
public:
    Allocator(); 
    void MakeAllocator(size_t maxSize);
    char *Alloc(size_t size);
    void Reset();
    ~Allocator();
};