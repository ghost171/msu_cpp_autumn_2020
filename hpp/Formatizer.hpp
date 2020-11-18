#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdarg.h>
#include <cassert>

using namespace std;

struct Error
{
    string message_;
    const char *fileName_;
    int line_;
    Error(const string& message, const char *fileName, int line) : message_(message), fileName_(fileName), line_(line) {}
};

string format_value(const string &v);
string format_value(const int &v);
string format_value(const double &v);
void format1(vector<string> &v);

template<class T, class... Args>
void format1(vector<string> &v, const T &input, Args... args);

template<class T, class... Args>
string format(const T &input, Args... args);

#include "Formatizer.tpp"