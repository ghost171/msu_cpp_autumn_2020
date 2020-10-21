#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>
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
    using callback = std::function<void (const string&)>;
    callback DigitTockenCallBack;
    callback TextTockenCallBack;
    void Tockenizer();
    void InputStringSet(const string& inputString);
    void Classificate();
    void ReadFromStream(istream& stream);
    void SetTextTokenCallBack(callback F);
    void SetDigitTokenCallBack(callback F);
};