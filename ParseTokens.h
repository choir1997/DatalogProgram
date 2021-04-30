#ifndef PROJECT1CS236_PARSETOKENS_H
#define PROJECT1CS236_PARSETOKENS_H
#include "Token.h"
#include "Predicate.h"
#include "Relations.h"
#include <set>

class ParseTokens {
private:
    string currentTokenString;
    TokenType tokenType;
    Token tokenObject;
    vector<string> datalogString;
    vector<string> finalDatalogString;
    set<string> domainList;
    TokenType grammarCategory;
    Predicate predicateObject;
    Relations relationsObject;
    int schemeCount = 0;
    int factCount = 0;
    int ruleCount = 0;
    int queryCount = 0;
    int domainCount = 0;
    int tokenLineNumber = 0;
    int schemeCountCategory = 0;
    int factCountCategory = 0;
    int ruleCountCategory = 0;
    int queryCountCategory = 0;
public:
    bool getTokenandType(const string& token, const TokenType& type, const int& tokenLine) {
        currentTokenString = token;
        tokenType = type;
        tokenLineNumber = tokenLine;
        return datalogProgram();
    }
    bool datalogProgram() {
        if (tokenType == SCHEMES &&
            ruleCountCategory == 0 && factCountCategory == 0 && queryCountCategory ==0) { //TODO: ADD EACH CATEGORY TO ANOTHER VECTOR TO CHECK ORDER OF S, F, S, Q and make sure S and Q are there
            grammarCategory = SCHEMES;
            datalogString.push_back(currentTokenString);
            schemeCountCategory++;
            return true;
        }
        if (grammarCategory == SCHEMES && tokenType != FACTS && tokenType != QUERIES && tokenType != RULES) {

            if (tokenType == COLON) {
                if (currentTokenString != "\n") {
                    datalogString.push_back(currentTokenString);
                    datalogString.emplace_back("\n");
                    datalogString.emplace_back("  ");
                }
                return true;
            }
            if (currentTokenString != "\n") {
                datalogString.push_back(currentTokenString);
            }

            if (predicateObject.schemeGrammar(tokenType, currentTokenString, tokenLineNumber) == 1) {

                if (tokenType == RIGHT_PAREN) {
                    if (currentTokenString != "\n") {
                        datalogString.emplace_back("\n");
                        datalogString.emplace_back("  ");
                        schemeCount++;
                    }
                }
                return true;
            }
            else {
                return false;
            }
        }
        else if (tokenType == FACTS && ruleCountCategory == 0 && schemeCountCategory == 1 && queryCountCategory ==0
                && schemeCount != 0) {
            grammarCategory = FACTS;
            predicateObject.schemeGrammar(tokenType, currentTokenString, tokenLineNumber);
            datalogString.emplace_back("\n");
            datalogString.push_back(currentTokenString);
            factCountCategory++;
            return true;
        }
        else if (grammarCategory == FACTS && tokenType != SCHEMES && tokenType != QUERIES && tokenType != RULES) {
            if (tokenType == COLON) {
                if (currentTokenString != "\n") {
                    datalogString.push_back(currentTokenString);
                    datalogString.emplace_back("\n");
                    datalogString.emplace_back("  ");
                }
                return true;
            }

            if (tokenType == STRING) {
                domainList.insert(currentTokenString);
            }
            if (currentTokenString != "\n") {
                datalogString.push_back(currentTokenString);
            }
            if (predicateObject.factsGrammar(tokenType, currentTokenString, tokenLineNumber)) {

                if (tokenType == PERIOD) {
                    if (currentTokenString != "\n") {
                        datalogString.emplace_back("\n");
                        datalogString.emplace_back("  ");
                        factCount++;
                    }
                }
            }
            else {
                return false;
            }
        }
        else if (tokenType == RULES && schemeCountCategory == 1 && factCountCategory == 1 && queryCountCategory ==0) {

            predicateObject.factsGrammar(tokenType, currentTokenString, tokenLineNumber);
            grammarCategory = RULES;
            datalogString.emplace_back("\n");
            datalogString.push_back(currentTokenString);
            ruleCountCategory++;
            return true;
        }
        else if (grammarCategory == RULES && tokenType != SCHEMES && tokenType != FACTS && tokenType != QUERIES) {
            if (tokenType == COLON) {
                if (currentTokenString != "\n") {
                    datalogString.push_back(currentTokenString);
                    datalogString.emplace_back("\n");
                    datalogString.emplace_back("  ");
                }
                return true;
            }
            if (currentTokenString != "\n") {
                datalogString.push_back(currentTokenString);
            }
            if (predicateObject.rulesGrammar(tokenType, currentTokenString, tokenLineNumber)) {
                if (tokenType == PERIOD) {
                    if (currentTokenString != "\n") {
                        datalogString.emplace_back("\n");
                        datalogString.emplace_back("  ");
                        ruleCount++;
                    }
                }
            }
            else {
                return false;
            }
        }
        else if (tokenType == QUERIES && schemeCountCategory == 1 && factCountCategory == 1 && ruleCountCategory ==1) {
            predicateObject.rulesGrammar(tokenType, currentTokenString, tokenLineNumber);
            grammarCategory = QUERIES;
            datalogString.emplace_back("\n");
            datalogString.push_back(currentTokenString);
            queryCountCategory++;
            return true;
        }
        else if (grammarCategory == QUERIES && tokenType != SCHEMES && tokenType != FACTS && tokenType != RULES) {
            if (tokenType == COLON) {
                if (currentTokenString != "\n") {
                    datalogString.push_back(currentTokenString);
                    datalogString.emplace_back("\n");
                    datalogString.emplace_back("  ");
                }
                return true;
            }
            if (currentTokenString != "\n") {
                datalogString.push_back(currentTokenString);
            }
            if (predicateObject.queriesGrammar(tokenType, currentTokenString, tokenLineNumber)) {
                if (tokenType == Q_MARK) {
                    if (currentTokenString != "\n") {
                        datalogString.emplace_back("\n");
                        datalogString.emplace_back("  ");
                        queryCount++;
                    }
                }
                return true;
            }
            else {
                return false;
            }
        }
        else {
            tokenObject.setErrorToken(tokenType, currentTokenString, tokenLineNumber);
            return false;
        }

        return true;
    }
    void toStringDatalog() {
        cout << "Success!" << endl;
        stringstream ss;
        ss << schemeCount;
        string intString = ss.str();
        stringstream facts;
        facts << factCount;
        string factString = facts.str();
        stringstream query;
        query << queryCount;
        string queryString = query.str();
        stringstream rules;
        rules << ruleCount;
        string ruleString = rules. str();

        for (size_t i = 0; i < datalogString.size(); i++) {
            finalDatalogString.push_back(datalogString.at(i));
            if (datalogString.at(i) == "Schemes" || datalogString.at(i) == "Facts" || datalogString.at(i) == "Rules" || datalogString.at(i) == "Queries") {
                finalDatalogString.emplace_back("(");
                if (datalogString.at(i) == "Schemes") {
                    finalDatalogString.push_back(intString);
                }
                else if (datalogString.at(i) == "Facts") {
                    finalDatalogString.push_back(factString);
                }
                else if (datalogString.at(i) == "Rules") {
                    finalDatalogString.push_back(ruleString);
                }
                else if (datalogString.at(i) == "Queries") {
                    finalDatalogString.push_back(queryString);
                }
                finalDatalogString.emplace_back(")");
            }
        }

    }
    void toStringFinalDatalog() {
        for (size_t i = 0; i < finalDatalogString.size(); i++) {
            cout << finalDatalogString.at(i);
        }
        for (auto it=domainList.begin(); it != domainList.end(); ++it) {
            domainCount++;
        }
        stringstream domain;
        domain << domainCount;
        string domainString = domain.str();
        cout << "\nDomain(" << domainString << "):" << endl;
        for (auto it=domainList.begin(); it != domainList.end(); ++it) {
            cout << *it << endl;
        }
    }


};


#endif
