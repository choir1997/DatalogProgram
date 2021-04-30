#include "Token.h"
#include "ParseTokens.h"

void Token::makeToken(const string &inputString) {
    ParseTokens parseToken;
    for (size_t i = 0; i < inputString.size(); i++) {

        if (inputString.at(i) == '\n') {
            if (tokenType == COMMENT) {
                tokenLine++;
                continue;
            }
            if (inputString.empty()) {
                continue;
            }
            if (tokenString.empty()) {
                if (i != inputString.size() - 1) {
                    tokenLine++;
                }
            } else if (!tokenString.empty() && i != inputString.size() - 1) {
                tokenString.push_back(inputString.at(i));
                tokenLine++;
                tokenLineForMultiple++;
                continue;
            } else if ((tokenString.at(0) != '#' && tokenString.at(1) != '|') && (tokenString.at(0) != '\'')) {
                continue;
            }
        }

        if (tokenString.empty() && (inputString.at(i) != '\'' && inputString.at(i) != '#')) {
            if (inputString.at(i) == '\n' || inputString.at(i) == '\t' || inputString.at(i) == ' ') {
                continue;
            }
        }

        tokenString.push_back(inputString.at(i));

        if (tokenString == "Queries" && !isalpha(inputString.at(i + 1))) {
            tempString = tokenString;
            tokenString.clear();
            tokenType = QUERIES;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == "Queries" && isalpha(inputString.at(i + 1))) {
            continue;
        } else if (tokenString == "Rules" && !isalpha(inputString.at(i + 1))) {
            tempString = tokenString;
            tokenString.clear();
            tokenType = RULES;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == "Rules" && isalpha(inputString.at(i + 1))) {
            continue;
        } else if (tokenString == "Facts" && !isalpha(inputString.at(i + 1))) {
            tempString = tokenString;
            tokenString.clear();
            tokenType = FACTS;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == "Facts" && isalpha(inputString.at(i + 1))) {
            continue;
        } else if (tokenString == "Schemes" && !isalpha(inputString.at(i + 1))) {
            tempString = tokenString;
            tokenString.clear();
            tokenType = SCHEMES;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == "Schemes" && isalpha(inputString.at(i + 1))) {
            continue;
        } else if (tokenString == ":") {
            if (inputString.at(i + 1) == '-') {
                continue;
            }
            tempString = tokenString;
            tokenString.clear();
            tokenType = COLON;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == ":-") {
            tempString = tokenString;
            tokenString.clear();
            tokenType = COLON_DASH;
            parseToken.getTokenandType(tempString, tokenType, tokenLine);
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if ((tokenString != "Queries" && tokenString != "Rules" && tokenString != "Facts" &&
                    tokenString != "Schemes") && (isalpha(tokenString.at(0)) &&
                    !isalpha(inputString.at(i + 1)) && !isdigit(inputString.at(i + 1)) &&
                    inputString.at(i + 1) != '\'')) {
            tempString = tokenString;
            tokenString.clear();
            tokenType = ID;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == "(") {
            tempString = tokenString;
            tokenString.clear();
            tokenType = LEFT_PAREN;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == "'") {
            continue;
        }
        else if (tokenString.at(0) == '\'') {
            int apostropheCount = 0;
            for (size_t j = 0; j < tokenString.size(); j++) {
                if (tokenString.at(j) == '\'') {
                    apostropheCount++;
                }
            }
            if (apostropheCount % 2 == 0 && inputString.at(i + 1) != '\'') {
                tempString = tokenString;
                tokenString.clear();
                tokenType = STRING;
                if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                    isProgramSuccessful = false;
                    return;
                }
                allTokens.push_back(toStringToken());
                countTokens++;
            }
            else if ((i != inputString.size() - 1) && (inputString.at(i + 1) == '\'') && (apostropheCount % 2 != 0)) {
                continue;
            }
            else if ((i == inputString.size() - 1) && apostropheCount % 2 != 0)  {
                tempString = tokenString;
                tokenString.clear();
                tokenType = UNDEFINED;
                if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                    isProgramSuccessful = false;
                    return;
                }
                allTokens.push_back(toStringToken());
                countTokens++;
            }
            else if (i != inputString.size() - 1 && apostropheCount % 2 != 0 && (inputString.at(i + 1) != '\'')) {
                continue;
            }
        } else if (tokenString == ",") {
            tempString = tokenString;
            tokenString.clear();
            tokenType = COMMA;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == ".") {
            tempString = tokenString;
            tokenString.clear();
            tokenType = PERIOD;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == "?") {
            tempString = tokenString;
            tokenString.clear();
            tokenType = Q_MARK;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == ")") {
            tempString = tokenString;
            tokenString.clear();
            tokenType = RIGHT_PAREN;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == "*") {
            tempString = tokenString;
            tokenString.clear();
            tokenType = MULTIPLY;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == "+") {
            tempString = tokenString;
            tokenString.clear();
            tokenType = ADD;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        } else if (tokenString == "#") {
            continue;
        } else if (tokenString.at(0) == '#') { //TODO: don't include comments in parser
            if (tokenString.at(1) == '|') { //
                if (tokenString.at(tokenString.size() - 2) == '|' &&
                    tokenString.at(tokenString.size() - 1) == '#') {
                    tempString = tokenString;
                    tokenString.clear();
                    tokenType = COMMENT;
                }
                else if (i == inputString.size() - 1) {
                    tempString = tokenString;
                    tokenString.clear();
                    tokenType = UNDEFINED;
                }
                else {
                    continue;
                }
            } else if (inputString.at(i + 1) == '\n' || i + 1 == inputString.size()) {
                tempString = tokenString;
                tokenString.clear();
                tokenType = COMMENT;
            }
        } else if (!isalpha(inputString.at(i)) && tokenString.at(0) != '#' &&
                   tokenString.at(0) != '\'') {
            tempString = tokenString;
            tokenString.clear();
            tokenType = UNDEFINED;
            if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
                isProgramSuccessful = false;
                return;
            }
            allTokens.push_back(toStringToken());
            countTokens++;
        }
    }
    tempString = "";
    tokenType = E_O_F;
    if (!parseToken.getTokenandType(tempString, tokenType, tokenLine)) {
        return;
    }

    if (!inputString.empty()) {
        tokenLine++;
    }
    countTokens++;
    allTokens.push_back(toStringToken());

    if (isProgramSuccessful) {
        //parseToken.toStringDatalog();
        //parseToken.toStringFinalDatalog();
    }
    else if (!isProgramSuccessful) {
        return;
    }
}

string Token::toStringAllTokens() const {
    ostringstream outputString;
    for (size_t i = 0; i < allTokens.size(); i++) {
        outputString << allTokens.at(i) << endl;
    }
    stringstream ss;
    ss << countTokens;
    string numberString = ss.str();
    outputString << "Total Tokens = " << numberString << endl;
    return outputString.str();
}

string Token::toStringToken() const {
    ostringstream outputString;

    switch (tokenType) {
        case QUERIES:
            outputString << "(QUERIES," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case COMMA:
            outputString << "(COMMA," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case PERIOD:
            outputString << "(PERIOD," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case Q_MARK:
            outputString << "(Q_MARK," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case LEFT_PAREN:
            outputString << "(LEFT_PAREN," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case RIGHT_PAREN:
            outputString << "(RIGHT_PAREN," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case COLON:
            outputString << "(COLON," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case COLON_DASH:
            outputString << "(COLON_DASH," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case MULTIPLY:
            outputString << "(MULTIPLY," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case ADD:
            outputString << "(ADD," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case SCHEMES:
            outputString << "(SCHEMES," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case FACTS:
            outputString << "(FACTS," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case RULES:
            outputString << "(RULES," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case ID:
            outputString << "(ID," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
        case STRING:
            if (tempString.find('\n') == string::npos) {
                outputString << "(STRING," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            }
            else if (tempString.find('\n') != string::npos) {
                outputString << "(STRING," << "\"" << tempString << "\"" << "," << tokenLine - tokenLineForMultiple << ")";
            }
            return outputString.str();
        case COMMENT:
            if (tempString.find('\n') == string::npos) {
                outputString << "(COMMENT," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            }
            else if (tempString.find('\n') != string::npos) {
                outputString << "(COMMENT," << "\"" << tempString << "\"" << "," << tokenLine - tokenLineForMultiple << ")";
            }
            return outputString.str();
        case UNDEFINED:
            if (tempString.find('\n') == string::npos) {
                outputString << "(UNDEFINED," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            }
            else if (tempString.find('\n') != string::npos) {
                int lineCount = 0;
                for (size_t i = 0; i < tempString.size(); i++) {
                    if (tempString.at(i) == '\n') {
                        lineCount++;
                    }
                }
                outputString << "(UNDEFINED," << "\"" << tempString << "\"" << "," << (tokenLine - lineCount) + 1 << ")";
            }
            return outputString.str();
        case E_O_F:
            outputString << "(EOF," << "\"" << tempString << "\"" << "," << tokenLine << ")";
            return outputString.str();
    }

    return outputString.str();
}
