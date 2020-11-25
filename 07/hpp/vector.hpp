#include <iostream>
#include <memory>
#include <limits>

using namespace std;

template <typename T> 
class TAllocator { 
public:
    template <class U>
    struct rebind {
        typedef TAllocator<U> other;
    };

    T *Address (T &value) const {
        return &value;
    }
    
    const T *Address (const T &value) const {
        return &value;
    }

    TAllocator() {}

    TAllocator(const TAllocator&) {}

    template <class U>
    TAllocator (const TAllocator<U>&) {}
    
    ~TAllocator() {}

    size_t max_size () const {
        return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

    T *Allocate(size_t num, const void* = 0) {
        T *ret = (T *)(operator new(num * sizeof(T)));
        return ret;
    }

    void Construct (T *p, const T& value) {
        new((void *) p)T(value);
    }

    void Destroy (T *p) {
        p->~T();
    }

    void Deallocate (T *p, size_t num) {
        operator delete((void*)p);
    }
};

template <typename T> 
class TIterator { 
private: 
    T* m_pCurrentNode; 
public:
    TIterator();

    TIterator(T *pNode) : m_pCurrentNode (pNode) { } 

    TIterator& operator=(T *pNode) 
    { 
        this->m_pCurrentNode = pNode; 
        return *this; 
    } 

    TIterator& operator++() 
    { 
        if (m_pCurrentNode) 
            m_pCurrentNode = m_pCurrentNode + 1; 
        return *this; 
    } 

    TIterator operator++(int) 
    { 
        TIterator TIterator = *this; 
        ++*this; 
        return TIterator; 
    } 

    bool operator!=(const TIterator& TIterator) 
    { 
        return m_pCurrentNode != TIterator.m_pCurrentNode; 
    } 

    int operator*() 
    { 
        return *m_pCurrentNode; 
    } 

};



template <typename T> 
class TVector {
private:
    T *Buffer;
    int Capacity;
    int Current;

public:
    TVector();

    template <typename C> 
    friend class TIterator;

    
    TIterator<T> Begin();

    TIterator<T> End(); 

    TIterator<T> RBegin();

    TIterator<T> REnd();

    void PushBack(T data);
    
    void EmplaceBack(int index, T value); 

    void Clear();

    bool Empty();

    void Push(int data, int index);
 
    T *Get(int index);
    
    T operator[](int index);

    void PopBack();
 
    int Size();
 
    int GetCapacity();
 
    void Print();

    void Resize(int newSize);
    
    void Reserve(int newCapacity);

    ~TVector();
};

template <typename T>
void TVector<T>::EmplaceBack(int index, T value) {
    if (index - 1 > Current) {
        cout << "You try to assign element which is out of range. It is unacceptable operation." << endl;
        return;
    }
    if (index == Current) {
        PushBack(value);
        return;
    }
    Buffer[index] = value;
}

template <typename T> 
TVector<T>::TVector() {
    Buffer = new T[1];
    Capacity = 1;
    Current = 0;
} 

template <typename T> 
TIterator<T>::TIterator() : m_pCurrentNode(TVector<T>::Buffer) { } 

template <typename T> 
TIterator<T> TVector<T>::Begin() { 
    return TIterator<T>(Buffer); 
} 

template <typename T> 
TIterator<T> TVector<T>::End() { 
    return TIterator<T>(Buffer + Current); 
} 

template <typename T> 
TIterator<T> TVector<T>::RBegin() { 
    return End(); 
} 

template <typename T> 
TIterator<T> TVector<T>::REnd() { 
    return Begin(); 
} 

template <typename T> 
void TVector<T>::PushBack(T data)
{
    if (Current == Capacity) {
        T *temp = new T[2 * Capacity];

        for (int i = 0; i < Capacity; i++) {
            temp[i] = Buffer[i];
        }

        Capacity *= 2;
        Buffer = temp;
    }

    Buffer[Current] = data;
    Current++;
}

template <typename T> 
void TVector<T>::Clear() {
    if (Buffer == nullptr) {
        Current = 0;
        return;
    }
    Current = 0;
    T *temp = new T[Capacity];
    delete[] Buffer;
    Buffer = temp;

}

template <typename T> 
bool TVector<T>::Empty() {
    if (Buffer == nullptr || Capacity == 0 || Current == 0) {
        return true;
    }
    return false;
}

template <typename T> 
void TVector<T>::Push(int data, int index)
{

    if (index == Current)
        PushBack(data);
    else
        Buffer[index] = data;
}

template <typename T> 
T *TVector<T>::Get(int index)
{
    if (index < Current)
        return Buffer + index;
    cout << "Your index is out of range. Exiting..." << endl;
    
    return nullptr;
}

template <typename T> 
T TVector<T>::operator[](int index) 
{ 
    if (Get(index) == nullptr) {
        cout << "You try to get value of nullptr pointer. This is unacceptable operation. Returning -1." << endl;
        return -1;
    } else {
        return *Get(index);
    }
} 

template <typename T> 
void TVector<T>::PopBack() { 
    if (Current == 0) {
        cout << "You try to get element from empty stack. This is unacceptable operation." << endl; 
        return;
    }
    Current--; 
}

template <typename T> 
int TVector<T>::Size() { return Current; }

template <typename T> 
int TVector<T>::GetCapacity() { return Capacity; }

template <typename T> 
void TVector<T>::Print()
{
    for (int i = 0; i < Current; i++) {
        cout << Buffer[i] << " ";
    }
    cout << endl;
}

template <typename T> 
void TVector<T>::Resize(int newSize) {
    if (newSize < Size) {
        cout << "Decreasing vector's size is unaccaptable operation. Exiting..." << endl;
        exit(1);
    }
    int currentSize = Current;
    for (int i = 0; i < (newSize - currentSize); i++) {
        PushBack(0);
    }
}

template <typename T> 
void TVector<T>::Reserve(int newCapacity) {
    if (newCapacity < Capacity) {
        cout << "Decreasing vector's capacity is unaccaptable operation. Exiting..." << endl;
        exit(1);
    }
    Capacity = newCapacity;
}

template <typename T> 
TVector<T>::~TVector() {
    delete[] Buffer;
    Capacity = 0;
    Current = 0;
}