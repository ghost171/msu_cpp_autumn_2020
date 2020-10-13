# Allocator

This is Allocator implemetation. 
## How to execute the project
You can clone this project with command.
```
  git clone https://github.com/ghost171/msu_cpp_autumn_2020/
 ```
And now you have files to start  the project. Now you have to do a make command to execute him:
```
  cd msu_cpp_autumn_2020/01
  chmod +rwx bin/test
  make test
```
 
## Important values
There 3 important values in programme. One of them is StartPointer. There is a pointer that points to your start place in memory. 
It needs to have a place to start. 
Another important value is MaxSize. It can be used in start memory allocating when we have selected the maximum size block where we want to work.
Ant the last value is Offset. There is a value to help us allocates and go through the memory. If we want to go from the start we can use Reset() function.

## Important functions

You can give him a number of wanted memory with help of Allocator::MakeAllocator(size_t maxSize). That will be his maximum memory size.
You can move through this max size momory with help of Allocator::Alloc(size_t size). You can use this function to allocating through memory ans assign different values to memory frames.
Function Allocator::Offset() can give you a possability to use your allocating memory for many times.
If you used some memory frames given from Alloc() your values was the same. You just change Offset to 0, not change, clean values in frames or especially delete frames.

### Allocator::Allocator()
There is a constructor. Here we have to prepare our values to work. As a deafault i initialize this  by zeros. However, this isn't so important.

  ```Allocator::Allocator() : StartPointer(nullptr), Offset(0), MaxSize(0) {}; ```

### void Allocator::MakeAllocator(size_t maxSize)
In this function we have to find place to our StartPointer. We use key-word new for this. 
As addition we have to check, is it 0? Because, it is we have to give a user nullptr, as we can't allocate memory size 0.
Also, assign our variables to appropriate values.
```
  void Allocator::MakeAllocator(size_t maxSize) {
      if (maxSize == 0) {
          StartPointer = nullptr;
      } else {
          StartPointer = new char[maxSize];
      }
      Offset = 0;
      MaxSize = maxSize;
  }
```
### char *Allocator::Alloc (size_t size)
We have to shift there on size value. We have to plus our offset to size and shift out StartPointer to size value.
But before it, we have to check two important cases: When the given StartPointer is nullptr (user can forgets to make his/her allocator or just give us nullptr specially).
And another case is when we want allocate more memory than our maximum size memory was allocated in MakeAllocator. In this case we ruturn nullptr.
```
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
```
### void Allocator::Reset() 

In this function we just assign our Offset to 0. As i write earlier, we need it to get through this memory. 
```
  void Allocator::Reset() {
      Offset = 0;
  }
```
### Allocator::~Allocator() 
This is destructor. In it we have to delete our StartPointer.
```
  Allocator::~Allocator() {
      if (StartPointer) {
          delete[] StartPointer;
      }
  }
```
##Tests
My tests located at src/test.cpp, include cases of "few times use MakeAllocator", "empty Allocator", "more memory than we have" and another cases of this issue. 
I implemented it in appropriate functions.
```
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
      allocated = allocator5.Alloc(5); //in this case we have to make memory leak like in malloc()
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
```
You can write tests by yourself. This program can throw the errors. If all tests in your occasion are accepted you see "All tests was accepted.OK" on your screen.
  
