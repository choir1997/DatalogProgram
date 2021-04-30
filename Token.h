#ifndef PROJECT1CS236_TOKEN_H
#define PROJECT1CS236_TOKEN_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

enum TokenType{COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES,
        FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, E_O_F};

using namespace std;

class Token {
private:
    string tokenString;
    string tempString;
    TokenType tokenType = COMMA;
    int tokenLine = 1;
    int tokenLineForMultiple = 0;
    int countTokens = 0;
    vector<string> allTokens;
    bool isProgramSuccessful = true;
    TokenType errorToken;
    string errorTokenString;

public:
    void makeToken(const string& inputString);

    string toStringAllTokens() const;

    string toStringToken() const;

    void setErrorToken(const TokenType& error, const string& string, const int& line ) {
        tokenType = error;
        tempString = string;
        tokenLine = line;
        cout << "Failure!" << endl;
        cout << toStringToken() << endl;
    }
    void programSuccess();
};

#endif //PROJECT1CS236_TOKEN_H
