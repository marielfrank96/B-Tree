
//Mariel Frank
//Data Structures, Fall 2016
//BTree Spell Check Project
//WordObject.hpp

#ifndef WordObject_hpp
#define WordObject_hpp

#include <stdio.h>
#include <iostream>

using std::string;
using std::endl;
using std::cout;

class WordObject {
    
    //Overloaded stream insertion operator
    friend std::ostream& operator<<(std::ostream &os, const WordObject &rhsObj);
    
private:
    
    //Data member
    string myWord;
    
    //How many times was word retrieved
    int countTimesRetrieved;
    
public:
    
    WordObject();
    
    ~WordObject();
    
    WordObject(string);
    
    string getMyWord() const {return myWord;}
    void setMyWord(string word){myWord = word;}
    
    int getWordCount() const {return countTimesRetrieved;}
    void setWordCount(int value){countTimesRetrieved=0;}
    void incrementCount() {countTimesRetrieved++;}
    
};
#endif /* WordObject_hpp */
