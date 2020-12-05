#include <iostream>
#include <cassert>
#include <sstream>
#include "../hpp/Serializer.hpp"

using namespace std;

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;
    template <class TSerializer>
    Error Serialize(TSerializer &serializer) {
        return serializer(a, b, c);
    }

    template <class TDeserializer>
    Error TDeserialize(TDeserializer &deserializer) {
        return deserializer(a, b, c);
    }
};

struct Data1 {
    bool a;
    uint64_t b;
    uint64_t c;
    template <class TSerializer>
    Error Serialize(TSerializer &serializer) {
        return serializer(a, b, c);
    }

    template <class TDeserializer>
    Error TDeserialize(TDeserializer &deserializer) {
        return deserializer(a, b, c);
    }
};

struct TBool {
    bool value;
    Error Serialize(TSerializer &serializer) {
        return serializer(value);
    }

    template <class TDeserializer>
    Error TDeserialize(TDeserializer &deserializer) {
        return deserializer(value);
    }
};

void test1() {
    Data x { 1, true, 2 };
    std::stringstream stream;
    TSerializer serializer(stream);
    serializer.Save(x);
    Data y {0, false, 0};
    TDeserializer deserializer(stream);
    const Error err = deserializer.Load(y);
    assert(err == Error::NoError);
    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

void test2() {
    TBool x;
    x.value = true;
    stringstream stream;
    TSerializer serializer(stream);
    serializer.Save(x);
    TBool y;
    y.value = false;
    TDeserializer deserializer(stream);
    const Error err = deserializer.Load(y);
    assert(err == Error::NoError);
    assert(x.value == y.value);
}

void test3() {
    Data x {1, false, 64};
    TBool y{false};
    stringstream stream;
    TSerializer serializer(stream);
    serializer.Save(x);
    TDeserializer deserializer(stream);
    const Error err = deserializer.Load(y);
    assert(err == Error::CorruptedArchive);
}

void test4() {
    Data x {3, false, 5};
    Data1 y {false, 3, 5};
    stringstream stream;
    TSerializer serializer(stream);
    serializer.Save(x);
    TDeserializer deserializer(stream);
    const Error err = deserializer.Load(y);
    assert(err == Error::CorruptedArchive);
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
    return 0;
}
