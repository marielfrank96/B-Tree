
//Mariel Frank
//Data Structures, Fall 2016
//BTree Spell Check Project
//TreeNode.hpp

#ifndef TreeNode_hpp
#define TreeNode_hpp

#include <stdio.h>
#include <iostream>
#include <string>

#include "WordObject.hpp"

using std::string;
using std::cout;
using std::endl;
using std::ifstream;

class TreeNode{
    
private:
    
    int mValue;
    
    WordObject keyArray[9];
    TreeNode* childArray[10];
    
    int numberOfChildren;
    int numberOfKeys;
    
    //Variable = false if node has children
    bool isLeaf;
    
public:
    
    //Constructor
    TreeNode();
        
    //Destructor
    ~TreeNode();
    
    //Get and set children functions
    int getNumOfChildren(){return numberOfChildren;}
    void incrementNumChildren(){numberOfChildren++;}
    TreeNode* getChildArray(int i){return childArray[i];}
    void setChildArray(int i, TreeNode* node){childArray[i] = node;}
    
    //Get and set key functions
    int getNumOfKeys(){return numberOfKeys;}
    void incrementNumKeys(){numberOfKeys++;}
    
    //Set and Get whether node is leaf
    bool getIsLeaf(){return isLeaf;}
    void setIsLeaf(bool value){isLeaf = value;}
    
    //Insert word object into nonfull tree
    void insertNonFull(WordObject myWord);
    
    //Split child function
    void splitChild(TreeNode* parent,TreeNode* child, int key);
    
    //Search tree for word
    WordObject* search(TreeNode* root, string word, int iteration);
    
    //Traverse tree to print
    void traverse();
    
    //Remove key from subtree of node
    void remove(string word);
    
    //Remove from nonleaf
    void removeFromInnerNode(int index);
    
    //merge nodes
    void mergeNodes(int index);
    
    //Borrow from previous or next node
    void borrowPre(int index);
    void borrowNext(int index);
};

#endif /* TreeNode_hpp */
