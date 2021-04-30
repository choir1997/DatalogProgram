#ifndef PROJECT1CS236_LEXER_H
#define PROJECT1CS236_LEXER_H
#include "Tokenizer.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Lexer {
private:
    string fileString;
    Tokenizer tokenizerObject;

public:
    explicit Lexer(const string& inputString) {
        fileString = inputString;
        tokenizerObject.runTokenizer(fileString);
    }
    string getAllTokens() {
        return tokenizerObject.getNextToken();
    }
};

#endif //PROJECT1CS236_LEXER_H
