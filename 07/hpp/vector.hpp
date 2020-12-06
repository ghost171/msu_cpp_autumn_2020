#include <iostream>
#include <memory>
#include <limits>

using namespace std;

struct Error
{
    string message_;
    const char *fileName_;
    int line_;
    Error(const string& message, const char *fileName, int line) : message_(message), fileName_(fileName), line_(line) {}
};

template<typename T>
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

template <typename T,  typename Allocator = TAllocator<T>> 
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



template <typename T,  typename Allocator = TAllocator<T>> 
class TVector {
private:
    T *Buffer;
    int Capacity;
    int Current;

    void Grow();

    Allocator currentAllocator;

public:
    TVector();

    TVector(size_t s);

    template <typename C, typename U> 
    friend class TIterator;
    
    TIterator<T, Allocator> Begin() const;

    TIterator<T, Allocator> End() const; 

    TIterator<T, Allocator> RBegin() const;

    TIterator<T, Allocator> REnd() const;

    void PushBack(const T &data);   

    void PushBack(T &&data);     

    template<class... Args >
    void EmplaceBack(Args&&... args);

    void Clear();

    bool Empty() const;
 
    T *Get(const size_t &index) const;

    TVector& operator=(const TVector &arg);

    TVector& operator=(TVector &&arg);
    
    T &operator[](const size_t index) const;

    TVector(const TVector &arg);

    TVector(TVector &&arg);

    void PopBack();
 
    int Size() const;
 
    int GetCapacity() const;
 
    void Print() const;

    void Resize(size_t newSize);
    
    void Reserve(size_t newCapacity);

    ~TVector();
};

template<typename T, typename A>
TVector<T, A> &TVector<T, A>::operator=(const TVector& arg) {
    Capacity = arg.Capacity;
    Current = arg.Current;
    T *current = Buffer;
    Buffer = arg.Buffer;
    delete[] current;
    return *this;
}

template<typename T, typename A>
TVector<T, A> &TVector<T, A>::operator=(TVector &&arg) {
    Capacity = arg.Capacity;
    Current = arg.Current;
    std::swap(Buffer, arg.Buffer);
    return *this;
}

template<typename T, typename A>
TVector<T, A>::TVector(TVector &&arg) {
    Capacity = arg.Capacity;
    Current = arg.Current;
    Buffer = currentAllocator.Allocate(Capacity);
    swap(Buffer, arg.Buffer);
}

template<typename T, typename A>
TVector<T, A>::TVector(const TVector &arg) {
    Capacity = arg.Capacity;
    Current = arg.Current;
    Buffer = currentAllocator.Allocate(Capacity);
    for (int i = 0; i < Current; i++) {
        Buffer[i] = arg.Buffer[i];
    }
}

template<typename T, typename A>
TVector<T, A>::TVector(size_t s) {
    Capacity  = s + 1;
    Current = s;
    Buffer = currentAllocator.Allocate(Capacity);
    if (Buffer == nullptr) {
        Current = 0;
        return;
    }
    T *temp = currentAllocator.Allocate(Capacity);
    currentAllocator.Deallocate(Buffer, Capacity);
    Buffer = temp;
}

template<typename T, typename A>
template<class... Args >
void TVector<T, A>::EmplaceBack( Args&&... args ) {
    T data = T(std::move(args...));
    if (Current == Capacity) {
        T *temp = currentAllocator.Allocate(2 * Capacity);
        for (int i = 0; i < Capacity; i++) {
            temp[i] = move(Buffer[i]);
        }

        Capacity *= 2;
        Buffer = temp;
    }

    Buffer[Current] = data;
    Current++;
}

template<typename T, typename A>
TVector<T, A>::TVector() : TVector(0) {} 

template<typename T, typename A>
TIterator<T, A>::TIterator() : m_pCurrentNode(TVector<T, A>::Buffer) { } 

template <typename T, typename A>
TIterator<T, A> TVector<T, A>::Begin() const {
    return TIterator<T, A>(Buffer);
}

template <typename T, typename A>
TIterator<T, A> TVector<T, A>::End() const {
    return TIterator<T, A>(Buffer + Current);
}

template<typename T, typename A>
TIterator<T, A> TVector<T, A>::RBegin() const {
    return End();
} 

template<typename T, typename A>
TIterator<T, A> TVector<T, A>::REnd() const {
    return Begin();
} 

template<typename T, typename A>
void TVector<T, A>::PushBack(const T &data) {
    if (Current == Capacity) {
        T *temp = currentAllocator.Allocate(2 * Capacity);
        for (int i = 0; i < Capacity; i++) {
            temp[i] = move(Buffer[i]);
        }
        Capacity *= 2;
        Buffer = temp;
    }
    Buffer[Current] = data;
    Current++;
}

template<typename T, typename A>
void TVector<T, A>::PushBack(T &&data) {
    if (Current == Capacity) {
        T *temp = currentAllocator.Allocate(2 * Capacity);
        for (int i = 0; i < Capacity; i++) {
            temp[i] = move(Buffer[i]);
        }
        Capacity *= 2;
        Buffer = temp;
    }
    Buffer[Current] = data;
    Current++;
}

template<typename T, typename A>
void TVector<T, A>::Clear() {
    if (Buffer == nullptr) {
        Current = 0;
        return;
    }
    Current = 0;
    T *temp = currentAllocator.Allocate(Capacity);
    currentAllocator.Deallocate(Buffer, Capacity);
    Buffer = temp;

}

template<typename T, typename A>
bool TVector<T, A>::Empty() const {
    if (Buffer == nullptr || Capacity == 0 || Current == 0) {
        return true;
    }
    return false;
}

template<typename T, typename A>
T *TVector<T, A>::Get(const size_t &index) const {
    if (index <= Current)
        return Buffer + index;
    throw(Error("Your index is out of range. Exiting...", __FILE__, __LINE__));
    return nullptr;
}

template<typename T, typename A>
T &TVector<T, A>::operator[] (const size_t index) const {
    if (Get(index) == nullptr) {
        throw(Error("You try to get value of nullptr pointer. This is unacceptable operation. Returning -1.", __FILE__, __LINE__));
        return *Get(0);
    } else {
        return *Get(index);
    }
} 

template<typename T, typename A>
void TVector<T, A>::PopBack() { 
    if (Current == 0) {
        throw(Error("You try to get element from empty stack. This is unacceptable operation.", __FILE__, __LINE__));
        return;
    }
    Current--; 
}

template<typename T, typename A>
int TVector<T, A>::Size() const { return Current; }

template<typename T, typename A>
int TVector<T, A>::GetCapacity() const { return Capacity; }

template<typename T, typename A>
void TVector<T, A>::Print() const {
    for (int i = 0; i < Current; i++) {
        cout << Buffer[i] << " ";
    }
    cout << endl;
}

template<typename T, typename A>
void TVector<T, A>::Resize(size_t newSize) {
    if (newSize < Capacity) {
        T *transfer = Buffer;
        Current = newSize;
        Buffer = currentAllocator.Allocate(newSize);
        for (int i = 0; i < newSize; i++) {
            Buffer[i] = move(transfer[i]);
        }
        currentAllocator.Deallocate(transfer, newSize);
        return;
    }

    if (newSize < Current) {
        Current = newSize;
    }

    int currentSize = Current;
    for (int i = 0; i < (newSize - currentSize); i++) {
        PushBack(T());
    }
}

template<typename T, typename A>
void TVector<T, A>::Reserve(size_t newCapacity) {
    if (newCapacity <= Capacity) {
        return;
    }
    /*T *transfer = Buffer;
    Buffer = currentAllocator.Allocate(newCapacity);
    currentAllocator.Deallocate(transfer, Capacity);*/
    *this = TVector(newCapacity + 1);
    Capacity = newCapacity;
}

template<typename T, typename A>
TVector<T, A>::~TVector() {
    currentAllocator.Deallocate(Buffer, Capacity);
    Capacity = 0;
    Current = 0;
}