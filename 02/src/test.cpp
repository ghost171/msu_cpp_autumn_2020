#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include "../hpp/parser.hpp"
#include "../hpp/test.hpp"

using namespace std;

void SumNumbers(const string& number) {
    sum += stoi(number);
}

void ConcatTexts(const string& text) {
    concat += text;
}

void PrintNumber(const string& number) {
    cout << number << " ";
}

void PrintText(const string& text) {
    cout << text << " ";
}

void ReturnLastNumber(const string& number) {
    lastNumber = number;
}

void ReturnLastText(const string& text) {
    lastText = text;
}

void ReturnNumbers(const string& number) {
    numbers.push_back(number);
}

void ReturnTexts(const string& text) {
    texts.push_back(text);
}

void test1() {
    Parser myParser;
    myParser.InputStringSet("12 mother 23 sdsd 12and thefather13");
    myParser.Tockenizer();
    myParser.SetDigitTokenCallBack(SumNumbers);
    myParser.SetTextTokenCallBack(ConcatTexts);
    myParser.Classificate();
    assert(sum == 35 && concat == "mothersdsd12andthefather13");
}

void test2() {
    Parser myParser;
    myParser.InputStringSet("");
    myParser.Tockenizer();
} 

void test3() {
    Parser myParser;
    myParser.InputStringSet("         1234");
    myParser.Tockenizer();
    myParser.SetDigitTokenCallBack(ReturnLastNumber);
    myParser.Classificate();
    assert(lastNumber == "1234");
}

void test4() {
    Parser myParser;
    myParser.InputStringSet("1235");
    myParser.Tockenizer();
    myParser.SetDigitTokenCallBack(ReturnLastNumber);
    myParser.Classificate();
    assert(texts.empty() && lastNumber == "1235");
}

void test5() {
    Parser myParser;
    lastNumber = "";
    myParser.InputStringSet("           ");
    myParser.Tockenizer();
    myParser.Classificate();

    assert(lastNumber == "" && lastText == "");
}

void test6() {
    Parser myParser;
    myParser.InputStringSet("1236             ");
    myParser.Tockenizer();
    myParser.SetDigitTokenCallBack(ReturnLastNumber);
    myParser.Classificate();
    assert(lastNumber == "1236" && lastText == "");
}

void test7() {
    Parser myParser;
    myParser.InputStringSet("           1234            mama        123412          mila12        12ramu         .             ");
    myParser.Tockenizer();
    myParser.SetDigitTokenCallBack(ReturnNumbers);
    myParser.SetTextTokenCallBack(ReturnTexts);
    myParser.Classificate();
    assert(numbers[0] == "1234" && numbers[1] == "123412" && texts[0] == "mama" && texts[1] == "mila12" && texts[2] == "12ramu" && texts[3] == ".");
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
    cout << "test5 ";
    test5();
    cout << "OK" << endl;
    cout << "test6 ";
    test6();
    cout << "OK" << endl;
    cout << "test7 ";
    test7();
    cout << "OK" << endl;
    cout << "All test has been done." << endl;
    return 0;
}