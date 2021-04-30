#ifndef PROJECT1CS236_INTERPRETER_H
#define PROJECT1CS236_INTERPRETER_H
#include "Token.h"
#include <set>
#include <algorithm>


class Interpreter { //TODO: read and evaluate the Queries class
private:
    string nameString;
    string headNameString;
    vector<string> parametersList;
    vector<string> headParametersList;
    vector<TokenType> tokenList;
    set<vector<string>> newRelationSet;
    vector<set<vector<string>>> setList;
    vector<vector<string>> finalVector;
    vector<string> tempLine;
    vector<string> nameList;
    vector<string> schemeNameList;
    vector<vector<string>> schemeParameterList;
    vector<vector<string>> twoPredicates;
    vector<vector<string>> newRelation;
    vector<string> tempTuple;
    int predicateListSize;
    int beforeSizeSet;
    int afterSizeSet;
    size_t firstIndex;
    bool isLastPredicate;
    vector<string> newTuple;
    vector<string> sizeHistoryVector;

public:
    void setSchemeHeaderList(const vector<vector<string>>& headers) {
        schemeParameterList = headers;

    }
    void setSchemeNameList(const vector<string>& names) {
        schemeNameList = names;
    }
    void getCurrentName(const string& name) {
        nameString = name;
        cout << nameString;
    }
    void getParameters(const string& parameter, const TokenType& token) {
        parametersList.push_back(parameter);
        tokenList.push_back(token);
    }
    void clearParameters() {
        cout << "(";
        for (size_t i = 0; i < parametersList.size(); i++) {
            cout << parametersList.at(i);
            if (i != parametersList.size()-1) {
                cout << ",";
            }
        }
        cout << ")?";


        passSetToInterpreter();
        parametersList.clear();
        tokenList.clear();

    }
    void getTupleSet(const set<vector<string>>& set, const vector<string>& names) {


        //TODO: add all sets to a giant SET and name list to assign each set to name

        setList.push_back(set); //TODO: setlist contains all the tuples for the database
        nameList = names; //TODO: namelist contains all names for tuples for database
    }
    void passSetToInterpreter() {
        if (findCorrectTuple() == -1) {
            cout << " No" << endl;
            return;
        }

        compareParametersToSet(setList.at(findCorrectTuple()));


    }

    void compareParametersToSet(const set<vector<string>>& set) { //TODO: get correct set and print out the sets according to parameter list
        for (auto it=set.begin(); it != set.end(); ++it) { //TODO: iterate through one set and then scan each vector in set
            scanOneTuple(*it);
        }
        toStringInterpreter();
        finalVector.clear();
    }
    void scanOneTuple(const vector<string>& tuple) {
        bool foundParameterAlready;
        bool foundError;

        for (size_t i = 0; i < parametersList.size(); i++) {

            foundParameterAlready = foundValueAlready(i);
            if (foundParameterAlready) {
                if (tuple.at(i) != tuple.at(firstIndex)) {
                    foundError = true;
                    break;
                }
                else {
                    foundError = false;
                    continue;
                }
            }

            if (tokenList.at(i) == STRING) {
                if (parametersList.at(i) != tuple.at(i)) {
                    foundError = true;
                    break;
                }
                foundError = false;
                continue;
            }
            foundError = false;
        }

        for (size_t i = 0; i < tokenList.size(); i++) { //TODO: print tuples
            if (!foundError) {
                if (tokenList.at(i) == STRING) { ;
                    continue;
                }
                if (foundValueAlready(i)) {
                    continue;
                }

                tempLine.push_back(parametersList.at(i));
                tempLine.emplace_back("=");
                tempLine.push_back(tuple.at(i));

                if ((i != tokenList.size() - 1 && tokenList.at(i+1) != STRING)) {
                    if (i + 1 != tokenList.size() - 1) {

                        if ((parametersList.at(i) == parametersList.at(i + 1)) &&
                            (parametersList.at(i + 1) == parametersList.at(i + 2))) {
                            continue;
                        }

                    }


                }
            }
            else {
                return;
            }
        }
        finalVector.push_back(tempLine);
        tempLine.clear();
    }
    int findCorrectTuple() { //TODO: find name in name list and return its index to find correct set
        for (size_t i = 0; i < nameList.size(); i++) {
            if (nameString == nameList.at(i)) {
                return i;
            }
        }
        return -1;
    }
    bool foundValueAlready(size_t stoppingIndex) {
        if (stoppingIndex == 0) {
            getFirstParameterIndex(stoppingIndex);
            return false;
        }
        for (size_t i = 0; i < stoppingIndex; i++) {
            if (parametersList.at(i) == parametersList.at(stoppingIndex)) {
                firstIndex = i;
                return true;
            }
            else {
                continue;
            }
        }
        return false;
    }
    size_t getFirstParameterIndex(size_t i) {
        return i;
    }

    void toStringInterpreter() { //TODO: PRINTS QUERY
        if (finalVector.empty()) {
            cout << " No" << endl;
            return;
        }
        else {cout << " Yes(" << finalVector.size() << ")" << endl;}

        for (size_t i = 0; i < finalVector.size(); i++) {
            printVectorLine(finalVector.at(i));
            cout << endl;
        }

    }

    void printVectorLine(vector<string> vector) { //TODO: PRINTS EACH VALUE
        for (size_t i = 0; i < vector.size(); i++) {
            cout << vector.at(i);
            if (i != vector.size() - 1 && (vector.at(i).find("'") != string::npos)) {
                cout << ", ";
            }
        }
    }

    void joinPredicates(const vector<string>& predicate) { //TODO: join two predicates and pass it to getNewRelation()
        int indexRelation1;
        int indexRelation2;
        vector<string> tempPredicate;
        vector<string> tupleString;

        twoPredicates.push_back(predicate);

        if (twoPredicates.size() == 2) {
            //combine headers
            for (size_t i = 0; i < twoPredicates.size(); i++) {
                for (size_t j = 0; j < twoPredicates.at(i).size(); j++) {
                    if (j == twoPredicates.at(i).size() - 1) {
                        continue;
                    }
                    if (i == 0 && j == 0) {
                        nameString = twoPredicates[i][j];
                        indexRelation1 = findCorrectTuple();
                        nameString = headNameString;
                    }
                    if (i == 1 && j == 0) {
                        nameString = twoPredicates[i][j];
                        indexRelation2 = findCorrectTuple();
                        nameString = headNameString;
                    }
                    if (twoPredicates[i][j+1] == "," || twoPredicates[i][j+1] == ")") {
                        parametersList.push_back(twoPredicates[i][j]); //TODO: GET HEADERS TO SET HEADERS IN NEW RELATION
                    }
                }
            }

            newRelation.push_back(parametersList); //TODO: ADD HEADERS TO NEW RELATION

            for (auto it=setList.at(indexRelation1).begin(); it != setList.at(indexRelation1).end(); ++it) { //TODO: iterate through one set and then scan each vector in set
                for (auto it2=setList.at(indexRelation2).begin(); it2 != setList.at(indexRelation2).end(); ++it2) {
                    scanTupleForJoin(*it);
                    scanTupleForJoin(*it2);
                    newRelation.push_back(tempTuple);

                    tupleString = tempTuple;

                    for (size_t i = 0; i < tupleString.size(); i++) {
                        if (foundValueAlready(i)) {
                            if (tupleString.at(firstIndex) != tupleString.at(i)) {
                                newRelation.pop_back();
                                break;
                            } else {
                                tempTuple.erase(tempTuple.begin() + i);
                                newRelation.pop_back();
                                newRelation.push_back(tempTuple);
                            }
                        }
                        if (parametersList.at(i).find("'") != string::npos) {
                            if (tempTuple.at(i).find("'") != string::npos) {
                                if (tempTuple.at(i) != parametersList.at(i)) {
                                    newRelation.pop_back();
                                    break;
                                }
                            }
                        }
                    }
                    tempTuple.clear();
                }
            }

            for (size_t i = 0; i < parametersList.size(); i++) {
                if (foundValueAlready(i)) {
                    newRelation.at(0).erase(newRelation.at(0).begin() + i);
                }
            }

            if (getPredicateListSize() > 2 && !isLastPredicate) {
                deleteTemporarySet(); // TODO: CHECK IF THERE IS ALREADY A TEMPORARY SET IN SETLIST
                tempPredicate.emplace_back("t");
                tempPredicate.emplace_back("(");
                nameList.emplace_back("t");
                for (size_t k = 0; k < newRelation.at(0).size(); k++) {
                    tempPredicate.push_back(newRelation.at(0).at(k));
                    if (k == newRelation.at(0).size() - 1) {
                        tempPredicate.push_back(")");
                        continue;
                    }
                    tempPredicate.push_back(",");

                }

                convertNewRelationToSet();
                setList.push_back(newRelationSet);
                twoPredicates.clear();
                newRelation.clear();
                newRelationSet.clear();
                return joinPredicates(tempPredicate); //TODO: CALL JOIN FUNCTION AGAIN WITH NEW RELATION
                //END NEW CODE
            }
            if (isLastPredicate) {
                deleteTemporarySet();
            }

            twoPredicates.clear();
            projectNewRelationColumns();
        }
        else {
            parametersList.clear();
            return;
        }
         //TODO: CLEAR TWO PREDICATES FOR NEXT TWO PARAMETERS
    }

    void clearNewRelation() {
        newRelation.clear();
    }

    void setPredicateListSize(const int& size) {
        predicateListSize = size;
    }
    int getPredicateListSize() {
        return predicateListSize;
    }

    void joinOnePredicate(const vector<string>& predicate) {
        int indexRelation1;
        for (size_t i = 0; i < predicate.size(); i++) {
            if (i == predicate.size() - 1) {
                continue;
            }
            if (i == 0) {
                nameString = predicate.at(i);
                indexRelation1 = findCorrectTuple();
                nameString = headNameString;
            }
            if (predicate.at(i+1) == "," || predicate.at(i+1) == ")") {
                parametersList.push_back(predicate.at(i)); //TODO: GET HEADERS TO SET HEADERS IN NEW RELATION
            }
        }
        newRelation.push_back(parametersList);

        for (auto it=setList.at(indexRelation1).begin(); it != setList.at(indexRelation1).end(); ++it) {
            scanTupleForJoin(*it);
            newRelation.push_back(tempTuple);
            tempTuple.clear();
        }
        projectNewRelationColumns();
    }

    void deleteTemporarySet() {
        for (size_t i = 0; i < nameList.size(); i++) {
            if (nameList.at(i) == "t") {
                setList.pop_back();
                nameList.pop_back();
                return;
            }
        }
    }

    void convertNewRelationToSet() {
        newRelationSet.clear();
        for (size_t i = 1; i < newRelation.size(); i++) {
            newRelationSet.insert(newRelation.at(i));
        }
    }
    void convertSetToVector() {
        newRelation.clear();
        newRelation.assign(newRelationSet.begin(), newRelationSet.end());
    }

    void scanTupleForJoin(const vector<string>& tuple) {
        for (size_t i = 0; i < tuple.size(); i++) {
            tempTuple.push_back(tuple.at(i));
        }
    }



    void getAndParseHeadPredicate(const vector<string>& headPredicate) {
        for (size_t i = 0; i < headPredicate.size(); i++) {
            if (i == headPredicate.size() - 1) {
                continue;
            }
            if (i == 0) {
                headNameString = headPredicate.at(i);
                nameString = headNameString;

            }
            if (headPredicate.at(i+1) == "," || headPredicate.at(i+1) == ")") {
                headParametersList.push_back(headPredicate.at(i)); //TODO: MAKE SURE TO CLEAR PARAMETER LIST WHEN DONE

            }
        }

    }

    void projectNewRelationColumns() {
        bool foundValue;
        int columnIndex = 0;

        for (size_t i = 0; i < newRelation.at(0).size(); i++) {
            for (size_t j = 0; j < headParametersList.size(); j++ ) {
                if (newRelation.at(0).at(i) == headParametersList.at(j)) {
                    foundValue = true;
                    break;
                }
                foundValue = false;
            }
            if (!foundValue) {
                columnIndex = i;
                for (size_t k = 0; k < newRelation.size(); k++) {
                    newRelation.at(k).erase(newRelation.at(k).begin() + columnIndex);

                }
            }
            else {
                continue;
            }
        }

        for (size_t i = 0; i < newRelation.at(0).size(); i++) {
            for (size_t j = 0; j < headParametersList.size(); j++ ) {
                if (newRelation.at(0).at(i) == headParametersList.at(j)) {
                    if (i != j) { //TODO: SWAP COLUMNS
                        for (size_t k = 0; k < newRelation.size(); k++) {
                            for (size_t l = 0; l < newRelation.at(0).size(); l++) {
                                swap(newRelation[k][i], newRelation[k][j]);
                                break;
                            }
                        }
                    }
                }
            }
        }

        if (findCorrectTuple() == -1) {
            for (size_t k = 0; k < newRelation.size(); k++) {
                updateTuple(newRelation.at(k));
                newRelation.at(k) = newTuple;
            }
            insertToSet();
            convertSetToVector();
            setSizeHistoryVector("true");

            for (size_t k = 0; k < newRelation.size(); k++) {
                printOneTupleRelation(newRelation.at(k));
                cout << endl;
            }
        }
        else {
            int tupleCount = 0;
            tupleCount++;
            setSizeHistoryVector("false");
            convertNewRelationToSet();
            convertSetToVector();
            for (size_t k = 0; k < newRelation.size(); k++) {
                updateTuple(newRelation.at(k));
                newRelation.at(k) = newTuple;
            }
            for (size_t k = 0; k < newRelation.size(); k++) {
                beforeSizeSet = setList.at(findCorrectTuple()).size();
                setList.at(findCorrectTuple()).insert(newRelation.at(k)); //TODO: INSERTING NEW RELATION INTO DATABASE
                afterSizeSet = setList.at(findCorrectTuple()).size();
                if (beforeSizeSet != afterSizeSet) {
                    setSizeHistoryVector("true");
                    printOneTupleRelation(newRelation.at(k));
                    cout << endl;
                }
            }
        }

        toStringSetList();
        newRelation.clear();


        headParametersList.clear();
        parametersList.clear();
    }

    void clearSizeHistoryVector() {
        sizeHistoryVector.clear();
    }

    void setSizeHistoryVector(const string& value) {
        sizeHistoryVector.push_back(value);
    }

    vector<string> getSizeHistoryVector() {
        return sizeHistoryVector;
    }

    void setLastPredicate(bool value) {
        isLastPredicate = value;
    }

    void toStringSetList() { //TODO: GET NEW DATABASE
        //cout << "NEW DATABASE: " << endl;
        for (size_t i = 0; i < setList.size(); i++) {
            //cout << "NAME: " << nameList.at(i) << endl;
            for (auto it=setList.at(i).begin(); it != setList.at(i).end(); ++it) { //TODO: iterate through one set and then scan each vector in set
                //printOneTupleRelation(*it);
                //cout << endl;
            }
            //cout << endl;
        }

    }

    void insertToSet() {
        convertNewRelationToSet();
        beforeSizeSet = setList.size();
        //cout << "NEW RELATION SET SIZE: " << newRelationSet.size() << endl;
        setList.push_back(newRelationSet);
        nameList.push_back(nameString);
        afterSizeSet = setList.size();
    }


    void printOneTupleRelation(vector<string> tuple) {
        for (size_t i = 0; i < schemeParameterList.at(findCorrectSetSchemes()).size(); i++) {
            cout << schemeParameterList.at(findCorrectSetSchemes()).at(i) << "=" << tuple.at(i);
            if (i != schemeParameterList.at(findCorrectSetSchemes()).size() - 1) {
                cout << ", ";
            }
        }
    }

    void updateTuple(vector<string> tuple) {
        size_t difference = 0;
        if (tuple.size() > schemeParameterList.at(findCorrectSetSchemes()).size()) {
            difference = tuple.size() - schemeParameterList.at(findCorrectSetSchemes()).size();
            for (size_t i = 0; i < difference; i++) {
               tuple.pop_back();
               newTuple = tuple;
            }
        }
        else {
            newTuple = tuple;
            return;
        }
    }

    int findCorrectSetSchemes() { //TODO: find name in name list and return its index to find correct set
        for (size_t i = 0; i < schemeNameList.size(); i++) {
            if (nameString == schemeNameList.at(i)) {
                return i;
            }
        }
        return -1;
    }





};


#endif //PROJECT1CS236_INTERPRETER_H
