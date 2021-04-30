#ifndef PROJECT1CS236_TOKENIZER_H
#define PROJECT1CS236_TOKENIZER_H
#include <iostream>
#include <vector>
#include "Token.h"
#include "ParseTokens.h"

using namespace std;

class Tokenizer {
private:
    string fileToken;
    Token newToken;

public:
    Tokenizer() {
        fileToken = "";
    }

    void runTokenizer(const string& inputString) {
        newToken.makeToken(inputString);
    }

    string getNextToken() const {
        return newToken.toStringAllTokens();
    }

};


#endif //PROJECT1CS236_TOKENIZER_H
