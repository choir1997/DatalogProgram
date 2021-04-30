//
// Created by choir on 4/5/2021.
//

#ifndef PROJECT1CS236_RELATIONS_H
#define PROJECT1CS236_RELATIONS_H
#include <set>
#include "Token.h"
#include "Interpreter.h"

class Relations {
private:
    vector<vector<string>> tupleList;
    set<vector<string>> finalTupleList;
    set<vector<string>> tempTupleList;
    vector<vector<string>> totalHeaderList;
    vector<string> headerList;
    vector<string> nameList;
    vector<string> tupleNameList;
    string nameString;
    vector<string> oneTuple;
    Interpreter interpreterObject;
    set<vector<string>> overallList;
    vector<vector<string>> overallListVector;
    vector<vector<TokenType>> overallListTokens;
    vector<string> oneFactTuple;
    vector<string> tempVector;
    vector<TokenType> oneFactTupleTokens;
    vector<TokenType> tempVectorTokens;
    vector<vector<string>> rulesList;
    vector<string> tempRules;
    vector<string> headPredicate;
    vector<vector<string>> predicatesList;
    vector<string> onePredicate;
    vector<string> schemeNameList;
    bool setChanged = false;

public:
    void getFactsValues(const string& factsTuples, const TokenType& token) { //TODO: adds individual values to each vector
        interpreterObject.setSchemeHeaderList(totalHeaderList);
        interpreterObject.setSchemeNameList(schemeNameList);
        tempVector.push_back(factsTuples);
        tempVectorTokens.push_back(token);
        if (token == PERIOD) {
            oneFactTupleTokens = tempVectorTokens;
            oneFactTuple = tempVector;
            tempVectorTokens.clear();
            tempVector.clear();
            addFactVectorsToSet();
        }

    }
    void addFactVectorsToSet() { //TODO: will get overall SET
        overallList.insert(oneFactTuple);
        overallListTokens.push_back(oneFactTupleTokens);
    }
    void parseFactsSet() {
        overallListVector.assign(overallList.begin(), overallList.end());
        for (size_t i = 0; i < overallListVector.size(); i++) {
            parseOneTuple(overallListVector.at(i));
        }
    }
    void parseOneTuple(const vector<string>& string) {
        for (size_t i = 0; i < string.size(); i++) {
            if (string.at(i) != "(" && string.at(i) != ")" && string.at(i) != "," && string.at(i) != "." && i != 0) {
                setTuple(string.at(i));
            }
            if (i == 0) {
                getCurrentName(string.at(i));
            }

            if (string.at(i) == ".") {
                clearTuple();
            }
        }
    }
    void setTuple(const string& ID) { //TODO: will set ONE tuple
        oneTuple.push_back(ID);
    }
    void clearTuple() { //TODO: will clear each Tuple
        tupleList.push_back(oneTuple);
        oneTuple.clear();
    }

    void runThroughNameList() { //TODO: will print all the Tuples in sets with names
        for (size_t i = 0; i < tupleNameList.size(); i++) {

            tempTupleList.insert(tupleList.at(i));

            if (i != tupleNameList.size() - 1 && (tupleNameList.at(i) != tupleNameList.at(i + 1))) { //TODO: get individual SETS
                for (size_t j = i+1; j < tupleNameList.size(); j++) {
                    if (tupleNameList.at(i) == tupleNameList.at(j)) {

                    }
                }
                nameList.push_back(tupleNameList.at(i));
                finalTupleList = tempTupleList;
                tempTupleList.clear();
                nameString = tupleNameList.at(i);
                //cout << "NAME: " << nameString << endl;
                toStringTupleList();

                continue;//TODO: set current name
            }
            else if (i == tupleNameList.size() - 1) {
                nameList.push_back(tupleNameList.at(i));
                finalTupleList = tempTupleList;
                tempTupleList.clear();
                nameString = tupleNameList.at(i);
                //cout << "NAME: " << nameString << endl;
                toStringTupleList();
                continue;
            }
        }
    }

    void toStringTupleList() { //TODO: should print one set for EACH name
        interpreterObject.getTupleSet(finalTupleList, nameList);
        for (auto it=finalTupleList.begin(); it != finalTupleList.end(); ++it) {
            printOneTuple(*it);
        }
    }
    void printOneTuple(const vector<string>& tuple) { //TODO: continuation of toStringTupleList
        //traverseHeaderList(totalHeaderList.at(findAndMatchName()), tuple);
    }
    void traverseHeaderList(const vector<string>& headers, const vector<string>& tuple) { //TODO: continuation of printOneTuple
        for (size_t i = 0; i < headers.size(); i++) {
            cout << headers.at(i) << "=" << tuple.at(i);
            if (i != headers.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    size_t findAndMatchName() {
        for (size_t i = 0; i < schemeNameList.size(); i++) {
            if (nameString == schemeNameList.at(i)) {
                return i;
            }
        }
        return 1;
    }
    void addToHeaderList(const string& header) {
        headerList.push_back(header);
    }
    void clearHeaderList() {
        totalHeaderList.push_back(headerList);
        headerList.clear();
    }
    void addToSchemeNamesList(const string& name) {
        schemeNameList.push_back(name);
    }
    void getCurrentName(const string& name) { //TODO: all names of TUPLE
        tupleNameList.push_back(name);
    }

    void toStringNameList() {
        for (size_t i = 0; i < nameList.size(); i++) {
            cout << nameList.at(i) << endl;
        }
    }
    void toStringHeaderList() {
        for (auto it=totalHeaderList.begin(); it != totalHeaderList.end(); ++it) {
            printOneHeader(*it);
        }
        cout << endl;
    }
    void printOneHeader(const vector<string>& header) {
        for (size_t i = 0; i < header.size(); i++) {
            cout << header.at(i);
            if (i != header.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }

    void passCurrentName(const string& name) { //TODO: all names of TUPLE
        interpreterObject.getCurrentName(name);
    }

    void passParameters(const string& parameter, const TokenType& token) {
        interpreterObject.getParameters(parameter, token);
    }
    void clearParameters() {
        interpreterObject.clearParameters();
    }

    void getOneRule(const string& value, const TokenType& token) { //TODO: SET LIST OF RULES FROM INPUT
        tempRules.push_back(value);
        if (token == PERIOD) {
            rulesList.push_back(tempRules);
            tempRules.clear();
        }
    }
    void separateRulesList() { //TODO: Go through every Rules vector and parse
        int ruleCycleCount = 0;
        cout << "Rule Evaluation" << endl;
        for (size_t j = 0; j < 30; j++) {
            for (size_t i = 0; i < rulesList.size(); i++) {
                parseOneRule(rulesList.at(i));
                predicatesList.clear();
                headPredicate.clear(); //TODO: clear headPredicate after each RULE iteration
            }
            cout << endl;
            ruleCycleCount++;
            for (size_t i = 0; i < interpreterObject.getSizeHistoryVector().size(); i++) {
                if (interpreterObject.getSizeHistoryVector().at(i) == "true") {
                    setChanged = true;
                    break;
                }
                else if ((i == interpreterObject.getSizeHistoryVector().size() - 1) && interpreterObject.getSizeHistoryVector().at(i) == "false") {
                    setChanged = false;
                    break;
                }
            }
            if (!setChanged) {
                break;
            }
            interpreterObject.clearSizeHistoryVector();

        }
        cout << "Schemes populated after " << ruleCycleCount << " passes through the Rules." << endl;
        cout << endl;
        cout << "Query Evaluation" << endl;
    }
    void parseOneRule(const vector<string>& rule) { //TODO: PARSE EVERY RULE and separate into head predicate and predicate list
        bool passedColonDash = false;
        for (size_t i = 0; i < rule.size(); i++) {

            cout << rule.at(i);//TODO: printing ALL rules from input

            if (rule.at(i) == ":-") {
                passedColonDash = true;
                continue;
            }

            if (!passedColonDash) {
                headPredicate.push_back(rule.at(i));
            }
            else {
                if (rule.at(i) == "." || rule.at(i-1) == ")") {
                    predicatesList.push_back(onePredicate);
                    onePredicate.clear();
                    continue;
                }
                onePredicate.push_back(rule.at(i));
            }
        }
        cout << endl;
        getHeadPredicate();
    }
    void getHeadPredicate() {

        interpreterObject.getAndParseHeadPredicate(headPredicate); //TODO: PASS HEAD PREDICATE TO INTERPRETER

        for (size_t i = 0; i < predicatesList.size(); i++) { //TODO: get tail predicates (FOR JOINING) and call JOIN function in Interpreter
            //printOnePredicate(predicatesList.at(i));
            if (predicatesList.size() == 1) {
                interpreterObject.joinOnePredicate(predicatesList.at(i));
                continue;
            }

            //TODO: MAKE FUNCTION FOR ONE PREDICATE
            if (i == predicatesList.size() - 1) {
                interpreterObject.setLastPredicate(true);
            }
            else {
                interpreterObject.setLastPredicate(false);
            }
            interpreterObject.setPredicateListSize(predicatesList.size());
            interpreterObject.joinPredicates(predicatesList.at(i));
            cout << " ";
        }
    }
    void printOnePredicate(const vector<string>& predicate) { //TODO: PRINTING ONLY ONE PREDICATE
        for (size_t i = 0; i < predicate.size(); i++) {
            cout << predicate.at(i);
        }
    }


};


#endif //PROJECT1CS236_RELATIONS_H
