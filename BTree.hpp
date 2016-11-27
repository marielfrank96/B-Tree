
//Mariel Frank
//Data Structures, Fall 2016
//BTree Spell Check Project
//BTree.hpp

#ifndef BTree_hpp
#define BTree_hpp

#include <stdio.h>
#include <iostream>
#include <string>

#include "TreeNode.hpp"
#include "WordObject.hpp"
#include "LinkedList.h"

using std::string;
using std::cout;
using std::endl;
using std::ifstream;

class BTree{
    
    friend std::ostream& operator << (std::ostream&, const BTree &rhsObj);
    
private:
    
    int mValue;
    
    TreeNode* root;

    WordObject* highestOccurance;
    
    int totalKeys;
    int treeHeight;
    
public:
    
    //Default constructor
    BTree();
    
    //Constructor with parameter
    BTree(int mValue);
    
    //Destructor
    ~BTree();
    
    TreeNode* getRoot(){return root;}
    
    WordObject* getHighestOccurance(){return highestOccurance;}
    
    //Insert WordObject into tree function
    void insert(WordObject newWord);
    
    //Search for word in tree
    bool BTreeSearch(string myWord, int iteration);
    
    //Remove WordObject from tree function
    void remove(string wordToRemove);
    
    TreeNode* find(string wordToRemove);
    
    const void BTreeTraverse();
    
    int getTotalKeys(){return totalKeys;}
    
    void clearTree(TreeNode* root, LinkedList<TreeNode*>& queueList);
};

#endif /* BTree_hpp */
