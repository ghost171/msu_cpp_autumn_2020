#pragma once

#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

enum class Error {
    NoError, 
    CorruptedArchive
};

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

class TSerializer {
    static constexpr char Separator = ' ';
    ostream &CurrentStream;

    template <class... Args>
    Error Process(uint64_t &current, Args&&... args) {
        CurrentStream << current << Separator;
        Process(args...);
        return Error::NoError;
    }

    template <class... Args>
    Error Process(bool &current) {
        if (current) {
            CurrentStream << "true" << Separator;
        } else {
            CurrentStream << "false" << Separator;
        }
        return Error::NoError;
    }

    template <class... Args>
    Error Process(uint64_t &current) {
        CurrentStream << current << Separator;
        return Error::NoError;
    }

    template <class... Args>
    Error Process(bool &current, Args&&... args) {
        if (current) {
            CurrentStream << "true" << Separator;
        } else {
            CurrentStream << "false" << Separator;
        }
        Process(args...);
        return Error::NoError;
    }

public:
    explicit TSerializer(ostream &out) : CurrentStream(out) {};

    template<class T>
    Error Save(T &object) {
        return object.Serialize(*this);
    }

    template<class... Args>
    Error operator()(Args&&... args) {
        return TSerializer::Process(args...);
    }

};

class TDeserializer {
private:
    istream &CurrentStream;

    template<class... Args>
    Error Process(bool &current, Args&&... args) {
        string text;
        CurrentStream >> text;
        if (text == "true") {
            current = true;
        } else if (text == "false") {
            current =  false;
        } else {
            return Error::CorruptedArchive;
        }

        return Process(args...);
    }

    template<class... Args>
    Error Process(bool &current) {
        string text;
        CurrentStream >> text;
        if (text == "true") {
            current = true;
        } else if (text == "false") {
            current =  false;
        } else {
            return Error::CorruptedArchive;
        }

        return Error::NoError;
    }

    template<class... Args>
    Error Process(uint64_t &current) {
        string text;
        CurrentStream >> text;
        if (is_number(text)) {
            current = stoi(text);
        } else {
            return Error::CorruptedArchive;
        }
        return Error::NoError;
    }

    template<class... Args>
    Error Process(uint64_t &current, Args&&... args) {
        string text;
        CurrentStream >> text;
        if (is_number(text)) {
            current = stoi(text);
        } else {
            return Error::CorruptedArchive;
        }
        return Process(args...);
    }

public:
    explicit TDeserializer(istream &in) : CurrentStream(in) {};
    
    template<class T>
    Error Load(T &object) {
        return object.TDeserialize(*this);
    }

    template<class... Args>
    Error operator()(Args&&... args) {
        return TDeserializer::Process(args...);
    }
};