
//Mariel Frank
//Data Structures, Fall 2016
//BTree Spell Check Project
//WordObject.cpp

#include "WordObject.hpp"

//Constructor
WordObject::WordObject(){
    
}

//Constructor with parameters
WordObject::WordObject(string fileWord){
    
    this -> myWord = fileWord;
    this -> countTimesRetrieved = 0;
    
}

//Destructor
WordObject::~WordObject(){
    
}

//Overloaded stream insertion operator
std::ostream& operator<<(std::ostream &os, const WordObject &rhsObj){
    
    os << rhsObj.myWord;
    
    return os;
}
