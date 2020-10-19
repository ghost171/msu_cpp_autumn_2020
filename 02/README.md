
# Parser

This is Allocator implemetation. 
## How to execute the project
You can clone this project with command.
```
  git clone https://github.com/ghost171/msu_cpp_autumn_2020/
 ```
And now you have files to start  the project. Now you have to do a make command to execute him:
```
  cd msu_cpp_autumn_2020/01
  make all
```
Now you gather your project. Let's test it.
```
  make test
 ```
## Important variables
There are few important variables.  
InputString is varible that saves input string of user. 
You can use Parser::InputStringSet() to set this value or ReadFromStream() to input it from somt stream.
vector<string> Tockens is variable that saves derived users string on tockens. That is array of strings that was separated by spaces in user's start string.
vector<pair<string, TockenType>> NumberAndTextClasses that is varible saved tockens and marks on type of texts and numbers;
Every tocken accords to type NUMBER or TEXT described in enum.

## Important functions


### Parser::Parser()
There is a constructor. Here we have to prepare our values to work. Start values of this variables isn't important.

  ```Parser::Parser() : InputString(), Tockens() {};```

### Parser::InputStringSet()
In this function we just prepared out start varible to work.
```
void Parser::InputStringSet(string inputString) {
    InputString = inputString;
}
```

### void Parser::Tockenizer()
In this function we devide InputString on tockens to mark them. 

```
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
```

###  void Parser::Classificate(void (*functionForText)(string text), void (*functionForNumber)(string number))
In this function we mark our tockens in NumberAntTextClasses and, also give a user possability to give his own functins to this tockens.
One for numbers and one for texts. That's void (*functionForText)(string text) and  void (*functionForNumber)(string number).
In this functions you can make different doings with this tockens in that functions. 


```
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
```

### void Parser::SetTextTokenCallback(void (*PrintForText)(string number)) and void Parser::SetDigitTokenCallBack(void (*PrintForDigit)(string text))
This functions prepared for user's functions application. This function get the last current tocken as an argument of user's function and execute  user's function.

void Parser::SetTextTokenCallback(void (*PrintForText)(string number)) {
    string text = NumberAndTextClasses.back().first;
    PrintForText(text);
}

void Parser::SetDigitTokenCallBack(void (*PrintForDigit)(string text)) {
    string number = NumberAndTextClasses.back().first;
    PrintForDigit(number);
}

##Tests
My tests located at src/test.cpp. I try to get sum of the numbers and concatenate texts, experimant with spaces and tabs, also try to get a user vector of all numbers and texts.

You can write tests by yourself. For tests you can write functions that do something with tockens.
  
