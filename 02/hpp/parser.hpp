#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>

using namespace std;

enum TockenType {
    NUMBER,
    TEXT
};

class Parser {
private:
    string InputString;
    vector<string> Tockens;
    vector<pair<string, TockenType>> NumberAndTextClasses;
public:
    Parser();
    ~Parser();    
    void Tockenizer();
    void InputStringSet(string inputString);
    void Classificate(void (*functionForText)(string number), void (*functionForNumber)(string number));
    void ReadFromStream(istream& stream);
    void SetDigitTokenCallBack(void (*PrintForDigit)(string digit));
    void SetTextTokenCallback(void (*PrintForText)(string text));
};