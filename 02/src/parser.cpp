#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <functional>
#include "../hpp/parser.hpp"

using namespace std;

void Parser::InputStringSet(const string& inputString) {
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

void Parser::SetTextTokenCallBack(callback PrintForText) {
    TextTockenCallBack = PrintForText;
}

void Parser::SetDigitTokenCallBack(callback PrintForDigit) {
    DigitTockenCallBack = PrintForDigit;
}

void Parser::Classificate() {
    bool flagForTexts;
    for (auto& word : Tockens) { 
        flagForTexts = false;
        for (auto& letter : word) {
            if (!isdigit(letter)) {
                NumberAndTextClasses.push_back(make_pair(word, TEXT));
                TextTockenCallBack(word);
                flagForTexts = true;
                break;
            }
        }
        if (!flagForTexts) {
            NumberAndTextClasses.push_back(make_pair(word, NUMBER));
        DigitTockenCallBack(word);
        }
    }
}

void Parser::ReadFromStream(istream& stream) {
    getline(stream, InputString);
}

Parser::Parser() : InputString(), Tockens(), TextTockenCallBack(nullptr), DigitTockenCallBack(nullptr) {};

Parser::~Parser() {}