#include <iostream>
#include <string>
#include <vector>
#include <stdarg.h>
#include <cassert>
#include "../hpp/Formatizer.hpp"

using namespace std;

string format_value(const string &v) {
    return v;
}

string format_value(const int &v) {
    return to_string(v);
}

string format_value(const char &v) {
    string ans = "";
    ans += v;
    return ans;
}

string format_value(const double &v) {
    return to_string(v);
}

void format1(vector<string> &v) {
}