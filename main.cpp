
//Mariel Frank
//Data Structures, Fall 2016
//BTree Spell Check Project
//main.cpp


#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "LinkedList.h"
#include "TreeNode.hpp"
#include "WordObject.hpp"
#include "BTree.hpp"

using std::string;
using std::cout;
using std::endl;
using std::ifstream;

string checkWordValid(string);
void linkedListSpellCheck(LinkedList<WordObject>&, string, int);
void removeFromList(LinkedList<WordObject>&, string);
void bTreeSpellCheck(BTree&, string, int);
void removeFromTree(BTree&, string);

/**********************************************
 *                                            *
 *              Function Main                 *
 *                                            *
 **********************************************/
int main(int argc, const char * argv[]) {
    
    string ErrorMessage = "Not enough command line arguments.\n";
    
    try{
        
        if(argc < 4){
            throw ErrorMessage;
        }
        else{
            string lexiconFileName = argv[1];
            string inputFileName = argv[2];
            string deleteFileName = argv[3];
            
            string line;
            string fileOpenError;
            ifstream dictionaryFile(lexiconFileName.c_str());
            
            //Create a linked list to store lexicon data
            LinkedList<WordObject> lexiconList;
            
            //Create B Tree to store lexicon data, pass mValue
            BTree myLexiconTree(10);
           
           //Attempt to open files
            if(!dictionaryFile){
                dictionaryFile.close();
                fileOpenError = "Dictionary file failed to open\n";
                throw fileOpenError;
            }
            else{
                
                //Read lexicon file into linked list and b tree
                 string word;
                 while(dictionaryFile >> word){
                     
                     word = checkWordValid(word);

                     //Create word object for each word in file
                     WordObject myWord(word);
                     
                     //Insert WordObject into linked list
                     lexiconList.insertFront(word);
                     
                     //Insert WordObject into tree
                     myLexiconTree.insert(myWord);
                 }
                
                //Close file when finished
                dictionaryFile.close();
            }
            
            /**********************************************
             *             Perform  spell check           *
             **********************************************/

            //Perform spell check on linked list
            linkedListSpellCheck(lexiconList, inputFileName, 1);
            
            //Perform spell check on b tree
            bTreeSpellCheck(myLexiconTree, inputFileName, 1);
            
            /**********************************************
             *            Remove items from Tree          *
             *********************************************/
            
            ifstream removeFile(deleteFileName.c_str());
            string fileError = "Remove file failed to open\n";
            
            if(!removeFile){
                removeFile.close();
                throw fileError;
            }
            else{
                
                //Read every word in the input file, compare against dictionary
                string wordToDelete;
                while (removeFile >> wordToDelete){
                    
                    wordToDelete = checkWordValid(wordToDelete);
                    
                    //Check if word is not found in lexicon list
                    if(!lexiconList.find(wordToDelete,0)){
                        //Do nothing, word was not found in lexicon
                    }
                    else{
                        //Delete the word from lexicon list
                        lexiconList.remove(wordToDelete);
                    }
                    
                    //Delete the word from lexicon tree
                    myLexiconTree.remove(wordToDelete);
                }
                
                //Close file when finished
                removeFile.close();
            }

            /**********************************************
             *          Perform  spell check again        *
             **********************************************/
        
            //Perform spell check on new linked list
            linkedListSpellCheck(lexiconList, inputFileName, 2);
             
            //Perform spell check on new b tree
            bTreeSpellCheck(myLexiconTree, inputFileName, 2);
            
        } //End of outer most else block
        
    }catch(string errorMessage){
        cout << errorMessage << endl;
    }
    catch(...){
        cout << "Error in catch all" << endl;
    }
    
    return 0;
}
/**********************************************
 *                                            *
 *        Function to make word valid         *
 *                                            *
 *                                            *
 **********************************************/
string checkWordValid(string myWord){
    
    //Make the word lowercase and remove periods and commas
    const int wordLength = (int)myWord.length();
    
    for(int i=0; i < wordLength; i++){
        
        myWord[i] = std::tolower(myWord[i]);
        
        if((i == wordLength-1) && (myWord[i] == ',' || myWord[i] == '.'
                || myWord[i] == ':' || myWord[i] == '*' ||  myWord[i] == ';')){
            myWord.erase(i);
        }
        
    }

    return myWord;
}
/**********************************************
 *                                            *
 *      Function to perform spell check       *
 *              on linked list                *
 *                                            *
 **********************************************/

void linkedListSpellCheck(LinkedList<WordObject>& lexiconList, string inputFileName, int iterationNum){
    
    ifstream inputFile(inputFileName.c_str());
    string fileError = "Input file failed to open.\n";
    int mispelledCount = 0;
    
    //Variables for timing
    clock_t timeBegin, timeEnd;
    double totalTime = 0.0;
    timeBegin = clock();
    
    if(!inputFile){
        inputFile.close();
        throw fileError;
    }
    else{
        
        //Read every word in the input file, compare against dictionary
        string word;
        while (inputFile >> word){
            
           word = checkWordValid(word);
            
            if(word == ""){
                //Do not check for empty word
            }
            else{
                //Now word is in desired format, try to find it
                //If word is not found
                if(!lexiconList.find(word, iterationNum)){
                    mispelledCount++;
                }
            }
        }
        
        //Close file when finished
        inputFile.close();
    }
    
    //Stop timer and calculate total time for spell check
    timeEnd = clock();
    totalTime = (double)(timeEnd-timeBegin)/CLOCKS_PER_SEC;
    
    //Required output for linked list
    cout << "\nData for Linked List Spell Check " << endl;
    cout << "Mispelled words in input file: " << mispelledCount << endl;
    cout << "Total runtime for spell check: " << totalTime << endl;
    cout << "Word with highest frequency occurence: " << lexiconList.highestOccurence()->wordInfo.getMyWord()
    << ", Occured: " << lexiconList.highestOccurence()->wordInfo.getWordCount() << endl << endl;
    
}

/**********************************************
 *                                            *
 *      Function to perform spell check       *
 *                on B tree                   *
 *                                            *
 **********************************************/

void bTreeSpellCheck(BTree& lexiconTree, string inputFileName, int iterationNum){
    
    ifstream inputFile(inputFileName.c_str());
    string fileError = "File failed to open";
    int mispelledCount = 0;
    
    //Variables for timing
    clock_t timeBegin, timeEnd;
    double totalTime = 0.0;
    timeBegin = clock();
    
    if(!inputFile){
        inputFile.close();
        throw fileError;
    }
    else{
        
        //Read every word in the input file, compare against dictionary
        string word;
        while (inputFile >> word){
            
           word = checkWordValid(word);
            
            if(word == ""){
                //do not check against lexicon
            }
            else{
                //Now word is in desired format, try to find it
                //If word is not found
                if(!lexiconTree.BTreeSearch(word, iterationNum)){
                    //cout << "Word was not found: " << word <<endl;
                    mispelledCount++;
                }
            }
        }
    }
    
    //Stop timer and calculate total time for spell check
    timeEnd = clock();
    totalTime = (double)(timeEnd-timeBegin)/CLOCKS_PER_SEC;
    
    //Required output for linked list
    cout << "\nData for Btree Spell Check " << endl;
    //cout << "Lexicon tree size: " << lexiconList.size() << endl;
    cout << "Mispelled words in input file: " << mispelledCount << endl;
    cout << "Total runtime for spell check: " << totalTime << endl;
    cout << "Word with highest frequency occurence: " << lexiconTree.getHighestOccurance()->getMyWord()
    << ", Occured: " << lexiconTree.getHighestOccurance()->getWordCount() << endl << endl;
    
}
