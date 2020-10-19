#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include "../hpp/parser.hpp"

using namespace std;

void Parser::InputStringSet(string inputString) {
    InputString = inputString;
}

void Parser::Tockenizer() {
    if (InputString == "") {
        cout << "Once, you have to push some string to InputString." << endl;
        return;
    }
    int k = 0;
    while (isspace(InputString[k])) {
        k++;
    }
    string word = "";
    for (int i = k; i < InputString.size(); i++) {
        if (std::isspace(InputString[i]) || i == InputString.size() - 1) {
            if (!isspace(InputString[i])) {
                word += InputString[i];
            }
            Tockens.push_back(word);
            word = "";
        } else {
            word += InputString[i];
        }
        while(isspace(InputString[i + 1]) && isspace(InputString[i]) && i < InputString.size()) {
            i++;
        }
    }
}

void Parser::SetTextTokenCallback(void (*PrintForText)(string number)) {
    string text = NumberAndTextClasses.back().first;
    PrintForText(text);
}

void Parser::SetDigitTokenCallBack(void (*PrintForDigit)(string text)) {
    string number = NumberAndTextClasses.back().first;
    PrintForDigit(number);
}

void Parser::Classificate(void (*functionForText)(string text), void (*functionForNumber)(string number)) {
    for (auto word : Tockens) {
        try {
            for (auto letter : word) {
                if (!isdigit(letter)) {
                    NumberAndTextClasses.push_back(make_pair(word, TEXT));
                    SetTextTokenCallback(functionForText);
                    throw 1;
                }
            }
        }
        catch(int a) {
            continue;
        }
        NumberAndTextClasses.push_back(make_pair(word, NUMBER));
        SetDigitTokenCallBack(functionForNumber);
    }
}

void Parser::ReadFromStream(istream& stream) {
    getline(stream, InputString);
}

Parser::Parser() : InputString(), Tockens() {};

Parser::~Parser() {}