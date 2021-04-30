#ifndef PROJECT1CS236_PREDICATE_H
#define PROJECT1CS236_PREDICATE_H
#include "Token.h"
#include "Relations.h"
#include "Interpreter.h"

class Predicate {
private:
    TokenType errorToken;
    TokenType currentToken;
    Token tokenObject;
    string errorTokenString;
    string tokenValue;
    Relations relationsObject;
    Interpreter interpreterObject;
    vector<string> idString;
    vector<string> stringString;
    vector<string> rulesValues;
    vector<string> predicateValues;
    vector<string> predicateValues2;
    vector<string> parameterValues;
    vector<string> expressionValues;
    vector<string> finalExpressionValues;
    vector<TokenType> oneLine;
    vector<string> oneLineString;
    vector<TokenType> rulesString;
    vector<TokenType> newLineForRules;
    vector<string> smallerPredicateValues;
    int tokenLineNumber = 0;

public:
    void toStringRelations() {
        relationsObject.runThroughNameList();
    }
    bool schemeGrammar(const TokenType& token, const string& tokenString, const int& line) {
        tokenValue = tokenString;
        currentToken = token;
        tokenLineNumber = line;
        if (currentToken == FACTS) {
            return checkSchemeGrammar(oneLine);
        }
        else if (currentToken == RIGHT_PAREN) {
            oneLine.push_back(token);
            oneLineString.push_back(tokenValue);
            relationsObject.clearHeaderList();
            return checkSchemeGrammar(oneLine);
        }
        else {
            if (currentToken == ID && oneLineString.empty()) {
                relationsObject.addToSchemeNamesList(tokenValue);
            }
            if (currentToken == ID && !oneLineString.empty()) {
                relationsObject.addToHeaderList(tokenValue);
            }
            oneLine.push_back(token);
            oneLineString.push_back(tokenValue);
            return true;
        }

    }
    bool checkSchemeGrammar(const vector<TokenType>& list) {
        vector<TokenType> idListTokens;
        vector<TokenType> oneSchemeList;
        if (list.empty()) {
            return true;
        }
        for (size_t i = 0; i < list.size(); i++) {
            oneSchemeList.push_back(list.at(i));
            if (list.at(i) == ID && i == 0) {
                continue;
            }
            else if (list.at(i) == LEFT_PAREN && i == 1) {
                continue;
            }
            else if (i == list.size() - 1 && list.at(i) == RIGHT_PAREN && list.at(i-1) == ID) {
                continue;
            }
            else if (list.at(i) == ID && i == 2) {
                continue;
            }
            else if (i >= 3) {
                idListTokens.push_back(list.at(i));
                idString.push_back(oneLineString.at(i));
                if (list.at(i+1) == RIGHT_PAREN) {
                    if (idList(idListTokens)) {
                        continue;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    continue;
                }
            }
            else {
                errorTokenString = oneLineString.at(i);
                errorToken = list.at(i);
                tokenObject.setErrorToken(errorToken, errorTokenString, tokenLineNumber);
                oneLine.clear();
                oneLineString.clear();
                return false;
            }
        }
        oneLine.clear();
        oneLineString.clear();
        return true;
    }
    bool idList(const vector<TokenType>& list) {
        for (size_t i = 0; i < list.size(); i++) {
            if (list.at(i) == COMMA && list.at(i+1) == ID) {
                continue;
            }
            else if (list.at(i) == ID && list.at(i-1) == COMMA) {
                continue;
            }
            else if (i == list.size() - 1 && list.at(i) != ID) {
                errorTokenString = idString.at(i);
                errorToken = list.at(i);
                tokenObject.setErrorToken(errorToken, errorTokenString, tokenLineNumber);
                return false;
            }
            else if (list.at(i) == COMMA && list.size() > 1) {
                continue;
            }
            else {
                errorTokenString = idString.at(i);
                errorToken = list.at(i);
                tokenObject.setErrorToken(errorToken, errorTokenString, tokenLineNumber);
                return false;
            }
        }
        idString.clear();
        return true;
    }
    bool factsGrammar(TokenType token, const string& tokenString, const int& line) {
        tokenValue = tokenString;
        currentToken = token;
        tokenLineNumber = line;
        if (currentToken == RULES) {
            relationsObject.parseFactsSet();
            relationsObject.runThroughNameList();
            return checkFactsGrammar(oneLine);
        }
        else if (currentToken == PERIOD) {
            relationsObject.getFactsValues(tokenValue, currentToken);
            oneLine.push_back(token);
            oneLineString.push_back(tokenValue);
            return checkFactsGrammar(oneLine);
        }

        else {
            relationsObject.getFactsValues(tokenValue, currentToken); //TODO: add values to vector in relations class
            oneLine.push_back(token);
            oneLineString.push_back(tokenValue);
            return true;
        }
    }
    bool checkFactsGrammar(const vector<TokenType>& list) {
        vector<TokenType> stringList;
        if (list.empty()) {
            return true;
        }
        for (size_t i = 0; i < list.size(); i++) {
            if (list.at(i) == ID && i == 0) {
                continue;
            }
            else if (list.at(i) == LEFT_PAREN && i == 1) {
                continue;
            }
            else if (i == list.size() - 1 && list.at(i) == PERIOD) {
                continue;
            }
            else if (list.at(i) == STRING && i == 2) {
                continue;
            }
            else if (i >= 3 && i != list.size() - 1) {
                stringList.push_back(list.at(i));
                stringString.push_back(oneLineString.at(i));
                if (list.at(i+1) == RIGHT_PAREN && list.at(i+2) == PERIOD) {
                    if (checkStringList(stringList)) {
                        continue;
                    }
                    else {
                        return false;
                    }
                }
            }
            else {
                errorTokenString = oneLineString.at(i);
                errorToken = list.at(i);
                tokenObject.setErrorToken(errorToken, errorTokenString, tokenLineNumber);
                oneLine.clear();
                oneLineString.clear();
                return false;
            }
        }
        oneLine.clear();
        oneLineString.clear();
        return true;
    }
    bool checkStringList(const vector<TokenType>& list) {
        for (size_t i = 0; i < list.size(); i++) {
                if (list.at(i) == COMMA && list.at(i+1) == STRING) {
                    continue;
                }
                else if (list.at(i) == STRING && list.at(i-1) == COMMA) {
                    continue;
                }
                else if (i == list.size() - 1 && list.at(i) != STRING) {
                    errorTokenString = stringString.at(i);
                    errorToken = list.at(i);
                    tokenObject.setErrorToken(errorToken, errorTokenString, tokenLineNumber);
                    return false;
                }
                else if (list.at(i) != COMMA && list.at(i) != STRING){
                    errorTokenString = stringString.at(i);
                    errorToken = list.at(i);
                    tokenObject.setErrorToken(errorToken, errorTokenString, tokenLineNumber);
                    return false;
                }
        }
        return true;
    }
    bool rulesGrammar(const TokenType& token, const string& tokenString, const int& line) {
        tokenValue = tokenString;
        currentToken = token;
        tokenLineNumber = line;
        if (currentToken == QUERIES) {
            relationsObject.separateRulesList();
            return checkRulesGrammar(newLineForRules);
        }
        else if (currentToken == PERIOD) {
            relationsObject.getOneRule(tokenValue, currentToken);
            newLineForRules.push_back(token);
            rulesValues.push_back(tokenValue);
            return checkRulesGrammar(newLineForRules);
        }
        else {
            relationsObject.getOneRule(tokenValue, currentToken);
            newLineForRules.push_back(token);
            rulesValues.push_back(tokenValue);
        }

        return true;
    }
    bool checkRulesGrammar(const vector<TokenType>& list) {
        int colonDashCount = 0;
        vector<TokenType> mainList;
        vector<TokenType> headPredicateList;
        vector<TokenType> predicateList;
        vector<TokenType> predicateList1;
        vector<string> valueList;
        vector<string> tempValueList;
        int firstPredicateCount = 0;
        int leftParenCount = 0;
        int rightParenCount = 0;

        if (list.empty()) {
            return true;
        }

        if (rulesValues.empty()) {
            return true;
        }

        for (size_t i = 0; i < list.size(); i++) {
            mainList.push_back(list.at(i));
            tempValueList.push_back(rulesValues.at(i));
            if (list.at(i) == LEFT_PAREN) {
                leftParenCount++;
            }
            if (list.at(i) == RIGHT_PAREN) {
                rightParenCount++;
            }
            if (i == list.size() - 1) {
                break;
            }
            if (list.at(i+1) == COLON_DASH && i != list.size() - 1) {
                headPredicateList = mainList;
                mainList.clear();
                oneLineString = tempValueList;
                tempValueList.clear();
                if (checkHeadPredicate(headPredicateList)) {
                    continue;
                }
                else {
                    return false;
                }
            }
            else if (list.at(i) == COLON_DASH) {
                mainList.clear();
                tempValueList.clear();
                colonDashCount++;
                continue;
            }
            else if (list.at(i) == RIGHT_PAREN && colonDashCount != 0 && (list.at(i+1) == COMMA || list.at(i+1) == PERIOD) && firstPredicateCount == 0) {
                if (leftParenCount != rightParenCount) {
                    continue;
                }
                firstPredicateCount++;
                predicateList = mainList;
                predicateValues = tempValueList;
                smallerPredicateValues = predicateValues;
                tempValueList.clear();
                if (checkPredicateGrammar(predicateList)) {
                    mainList.clear();
                    continue;
                }
                else {
                    return false;
                }
            }
            else if (list.at(i+1) == PERIOD && i != list.size() - 1) {
                predicateList = mainList;
                mainList.clear();
                predicateValues = tempValueList;
                tempValueList.clear();
                if (checkPredicateList(predicateList)) {
                    continue;
                }
                else {
                    return false;
                }
            }

            else {
                continue;
            }
        }
        oneLine.clear();
        oneLineString.clear();
        rulesString.clear();
        rulesValues.clear();
        newLineForRules.clear();
        return true;
    }
    bool checkHeadPredicate(const vector<TokenType>& list) {
        return checkSchemeGrammar(list);
    }
    bool checkPredicateList(const vector<TokenType>& list) {
        vector<TokenType> predicateList;
        int leftParenCount = 0;

        for (size_t i = 0; i < list.size(); i++) {

            if (list.at(i) == COMMA && i == 0) {
                continue;
            }
            if (list.at(i) == LEFT_PAREN) {
                leftParenCount++;
            }
            if (list.at(i) == COMMA && leftParenCount == 0) {
                continue;
            }

            predicateList.push_back(list.at(i));
            predicateValues2.push_back(predicateValues.at(i));

            if (list.at(i) == RIGHT_PAREN && (i == list.size() - 1 || list.at(i+1) == COMMA)) {
                smallerPredicateValues = predicateValues2;
                predicateValues2.clear();
                leftParenCount = 0;
                if (checkPredicateGrammar(predicateList)) {
                    predicateList.clear();
                    continue;
                }
                else {
                    return false;
                }
            }
            else {
                continue;
            }
        }
        predicateValues.clear();

        return true;
    }
    bool queriesGrammar(TokenType token, const string& tokenString, const int& line) {
        tokenValue = tokenString;
        currentToken = token;
        tokenLineNumber = line;

        if (currentToken == E_O_F) {
            return checkQueriesGrammar(oneLine);
        }
        else if (currentToken == Q_MARK) {
            oneLine.push_back(token);
            oneLineString.push_back(tokenValue);
            relationsObject.clearParameters();
            return checkQueriesGrammar(oneLine);
        }
        else {
            if (currentToken == ID && oneLineString.empty()) {
                relationsObject.passCurrentName(tokenValue);
            }
            else if (currentToken == STRING || currentToken == ID) {
                relationsObject.passParameters(tokenValue, currentToken);
            }
            oneLine.push_back(token);
            oneLineString.push_back(tokenValue);
        }
        return true;
    }
    bool checkQueriesGrammar(const vector<TokenType>& list) {
        vector<TokenType> predicateList;
        vector<string> queryString;
        if (list.empty()) {
            return true;
        }
        for (size_t i = 0; i < list.size(); i++) {
            predicateList.push_back(list.at(i));
            queryString.push_back(oneLineString.at(i));
            if (list.at(i) != Q_MARK && i == list.size() - 1) {
                errorTokenString = oneLineString.at(i);
                errorToken = list.at(i);
                tokenObject.setErrorToken(errorToken, errorTokenString, tokenLineNumber);
                oneLine.clear();
                oneLineString.clear();
                return false;
            }
            if (list.at(i+1) == Q_MARK) {
                smallerPredicateValues = queryString;
                if (!checkPredicateGrammar(predicateList)) {
                    return false;
                }
                else {
                    predicateList.clear();
                    return true;
                }
            }
            else if (list.at(i) == Q_MARK) {
                continue;
            }
        }
        return true;
    }

    bool checkPredicateGrammar(const vector<TokenType>& list) {
        vector<TokenType> parameterList;
        for (size_t i = 0; i < list.size(); i++) {
            if (list.at(i) == ID && i == 0) {
                continue;
            }
            else if (list.at(i) == RIGHT_PAREN && i == list.size() - 1) {
                continue;
            }
            else if (list.at(i) == LEFT_PAREN && i == 1) {
                continue;
            }
            else if (i >= 2 && i != list.size() - 1) {
                parameterList.push_back(list.at(i));
                parameterValues.push_back(smallerPredicateValues.at(i));
                if (list.at(i+1) == RIGHT_PAREN && i == list.size() - 2) {
                    if (checkParameterGrammar(parameterList)) {
                        continue;
                    }
                    else {
                        return false;
                    }
                }
            }
            else {
                errorTokenString = oneLineString.at(i);
                errorToken = list.at(i);
                tokenObject.setErrorToken(errorToken, errorTokenString, tokenLineNumber);
                oneLine.clear();
                oneLineString.clear();
                return false;
            }
        }
        oneLine.clear();
        oneLineString.clear();

        return true;
    }
    bool checkParameterGrammar(const vector<TokenType>& list) {
        bool isExpressionToken = false;
        vector<TokenType> expressionList;
        for (size_t i = 0; i < list.size(); i++) {
            if ((list.at(i) == STRING || list.at(i) == ID) && !isExpressionToken) {
                if (i == list.size() - 1) {
                    break;
                }
                if (list.at(i+1) == COMMA) {
                    continue;
                }
                else if (list.at(i+1) != COMMA && list.size() > 1) {
                    return false;
                }
            }
            if (list.at(i) == COMMA) {
                continue;
            }
            else if (list.at(i) == LEFT_PAREN) {
                expressionList.push_back(list.at(i));
                expressionValues.push_back(parameterValues.at(i));
                isExpressionToken = true;
            }
            else if (list.at(i) != STRING && list.at(i) != ID && list.at(i) != LEFT_PAREN && list.at(i) != COMMA && !isExpressionToken) {
                return false;
            }
            else {
                if (isExpressionToken) {
                    expressionList.push_back(list.at(i));
                    expressionValues.push_back(parameterValues.at(i));
                }
                if (list.at(i) == RIGHT_PAREN && i == list.size() - 1) {
                    if (checkExpressionGrammar(expressionList)) {
                        continue;
                    }
                    else {
                        return false;
                    }
                }
                continue;
            }
        }
        parameterValues.clear();
        return true;
    }
    bool checkExpressionGrammar(vector<TokenType> expressionList) {
        int leftParenCount = 0;
        int rightParenCount = 0;
        int noOperatorCount = 0;
        vector<TokenType> tempParameterList;
        vector<TokenType> finalParameterList;
        vector<TokenType> tempTokenString;
        TokenType tokenError;
        string tokenErrorString;

        for (size_t i = 0; i < expressionList.size(); i++) {
            if (expressionList.at(i) == RIGHT_PAREN && i == expressionList.size() - 1) {
                continue;
            }
            if (noOperatorCount > 0) {
                if (((expressionList.at(i+1) == RIGHT_PAREN) && (i + 1 == expressionList.size() - 1)) && (expressionList.at(i) != STRING && expressionList.at(i) != ID)) {
                    continue;
                }
                tokenErrorString = expressionValues.at(i);
                tokenError = expressionList.at(i);
                tokenObject.setErrorToken(tokenError, tokenErrorString, tokenLineNumber);
                finalExpressionValues.clear();
                expressionValues.clear();
                return false;
            }

            if (expressionList.at(i) == LEFT_PAREN && i == 0) {
                leftParenCount++;
                continue;
            }
            else if (expressionList.at(i) == ADD || expressionList.at(i) == MULTIPLY) {
                continue;
            }
            tempParameterList.push_back(expressionList.at(i));
            finalExpressionValues.push_back(expressionValues.at(i));

            if (expressionList.at(i) == STRING || expressionList.at(i) == ID || expressionList.at(i) == LEFT_PAREN
               || expressionList.at(i) == RIGHT_PAREN) {
                if (expressionList.at(i) == RIGHT_PAREN && i == expressionList.size() - 1) {
                    break;
                }
                else if (expressionList.at(i) == RIGHT_PAREN) {
                    rightParenCount++;
                    if (rightParenCount != leftParenCount) {
                        if (expressionList.at(i+1) != ADD && expressionList.at(i+1) != MULTIPLY) {
                            noOperatorCount++;
                            continue;
                        }
                    }
                    else {
                        continue;
                    }
                }
                if (expressionList.at(i) == LEFT_PAREN) {
                    leftParenCount++;
                    continue;
                }
                if (((expressionList.at(i+1) != ADD && expressionList.at(i+1) != MULTIPLY) && (expressionList.at(i) != ADD && expressionList.at(i) != MULTIPLY))
                && expressionList.at(i+1) != RIGHT_PAREN) {
                    noOperatorCount++;
                    continue;
                }

            }
        }
        expressionValues.clear();
        return true;
    }
};


#endif //PROJECT1CS236_PREDICATE_H
