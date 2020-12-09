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

    Error TakeBool(const bool current);

    template <class... Args>
    Error Process(const uint64_t current, const Args&... args) {
        CurrentStream << current << Separator;
        Process(args...);
        return Error::NoError;
    }

    template <class... Args>
    Error Process(const bool current) {
        TakeBool(current);
        return Error::NoError;
    }

    template <class... Args>
    Error Process(const uint64_t current) {
        CurrentStream << current << Separator;
        return Error::NoError;
    }

    template <class... Args>
    Error Process(const bool current, const Args&... args) {
        TakeBool(current);
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
    Error operator()(const Args&... args) {
        return TSerializer::Process(args...);
    }
};

class TDeserializer {
private:
    istream &CurrentStream;

    Error getBool(bool &current, const string &text);

    Error getInt(uint64_t &current, const string &text);

    template<class... Args>
    Error Process(bool &current, Args&... args) {
        string text;
        CurrentStream >> text;
        Error error = getBool(current, text);
        if (error == Error::CorruptedArchive) {
            return Error::CorruptedArchive;
        }
        return Process(args...);
    }

    template<class... Args>
    Error Process(bool &current) {
        string text;
        CurrentStream >> text;
        return getBool(current, text);
    }

    template<class... Args>
    Error Process(uint64_t &current) {
        string text;
        CurrentStream >> text;
        return getInt(current, text);
    }

    template<class... Args>
    Error Process(uint64_t &current, Args&... args) {
        string text;
        CurrentStream >> text;
        Error error = getInt(current, text);
        if (error == Error::CorruptedArchive) {
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
    Error operator()(Args&... args) {
        return TDeserializer::Process(args...);
    }
};

Error TSerializer::TakeBool(const bool current) {
    if (current) {
        CurrentStream << "true" << Separator;
    } else {
        CurrentStream << "false" << Separator;
    }
    return Error::NoError;
}

Error TDeserializer::getBool(bool &current, const string &text) {
    if (text == "true") {
        current = true;
    } else if (text == "false") {
        current =  false;
    } else {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}

Error TDeserializer::getInt(uint64_t &current, const string &text) {
    if (is_number(text)) {
        try {
            current = stoull(text);
        }
        catch (const std::logic_error &exc) {
            cout << "Your argument contsins errors. It is possible connnects with wrong type of argument. Check your arguments list to serializer and try again." << endl;
            cout << exc.what() << endl;
            return Error::CorruptedArchive;
        }   
    } else {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}