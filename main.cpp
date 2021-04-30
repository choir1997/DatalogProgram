#include <iostream>
#include <fstream>
#include <string>
#include "Token.h"
#include "Tokenizer.h"
#include "Lexer.h"

using namespace std;

int main(int argc, char *argv[]) {
    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 2;
    }
 
    string fileString;
    ParseTokens parseObject;

 //TODO: main will instantiate lexer object
    while (in.peek() != EOF) {
        char getChar = in.get();
        fileString.push_back(getChar);
    }

    Lexer lexerObject(fileString);



    return 0;
}
