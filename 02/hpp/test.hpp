#include <iostream>
#include <string>
#include <cassert>
#include <vector>

string concat = "";
int sum = 0;
string lastNumber;
string lastText;
vector<string> numbers;
vector<string> texts;

void SumNumbers(const string& number);
void ConcatTexts(const string& text);
void PrintNumber(const string& number);
void PrintText(const string& text);
void ReturnLastNumber(const string& number);
void ReturnLastText(const string& text);
void ReturnNumbers(const string& number);
void ReturnTexts(const string& text);
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();