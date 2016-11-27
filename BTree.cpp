
//Mariel Frank
//Data Structures, Fall 2016
//BTree Spell Check Project
//BTree.cpp

#include "BTree.hpp"

//Default constructor
BTree::BTree(){
    
}

//Constructor with mValue paramter
BTree::BTree(int m){
    
    cout << "m value = " << m << endl;
    
    this -> mValue = m;
    this -> treeHeight = 0;
    this -> root = NULL;
    this -> totalKeys = 0;
    
}

//Destructor
BTree::~BTree(){
    
    //Deallocate memory by pushing onto linked list and clearing list
    LinkedList<TreeNode*> queueList;
    this-> clearTree(this->root, queueList);
    queueList.clear();
    
}

//BTree insert function
void BTree::insert(WordObject newWord){
    
    try{
        
        //Case 1: ROOT IS NULL, NEED TO CREATE A ROOT
        if(root == NULL){
                    
            //Create a node for the tree and make that the tree root
            TreeNode* newNode = new TreeNode();
            
            //Set tree root to that node
            this -> root = newNode;
            //No children so root is also leaf
            newNode->setIsLeaf(true);
            
            //Update the height of the tree from zero to one
            this -> treeHeight++;
            
            //Need to push newWord onto arraylist of newNode
            newNode->insertNonFull(newWord);
            this->highestOccurance = &newWord;
            totalKeys++;
        }
        
        //Case 2: TREE IS NOT EMPTY
        else{
            
            //If the root is full
            if(root -> getNumOfKeys() == mValue-1){
                
                TreeNode* newNode = new TreeNode();
                newNode->setChildArray(0, root);
                newNode->incrementNumChildren();
                newNode->setIsLeaf(false);
                this->treeHeight++;
                
                if(root -> getNumOfChildren() == 0){
                    root->setIsLeaf(true);
                }
                else{
                    root ->setIsLeaf (false);
                }
                
                //Now split the old root
                newNode-> splitChild(newNode, root, 0);
                
                //Reassign root to new node once it has been passed into the function
                root = newNode;
                root ->setIsLeaf(false);
                
                root ->insertNonFull(newWord);
                totalKeys++;
                
            }
            
            else{
                //The root is not full, insert non full
                root -> insertNonFull(newWord);
                totalKeys++;
            }
        }
        
    } //End of Try block
    catch(string ErrorMessage){
        cout << ErrorMessage;
    }
    catch(...){
        cout << "Error in Catch all" << endl;
    }
    
}

/************************************************
 *         BTreeSearch remove function          *
 *                                              *
 ************************************************/
void BTree::remove(string wordToRemove){
    
    if(root == NULL){
        //Tree is empty, cannot remove
        return;
    }
    
    //Call TreeNode remove function, beginning with tree root
    root->remove(wordToRemove);
    
    //If all keys have been removed from root
    if(root->getNumOfKeys() == 0){
        
        //Keep pointer to old root so that memory can be freed
        TreeNode* rootptr = root;
        
        //If the root is a leaf node, the tree is now empty
        if(this->root->getIsLeaf()){
            this->root = NULL;
        }
        else{
            //Elevate child 0 of the root to the new root node
            //Root should only have one child if there are no keys
            this->root = root-> getChildArray(0);
            //Tree height decreases by one
            treeHeight--;
        }
        
        //Delete memory allocated to old root
        delete rootptr;
    }
    
    //Decrement the BTree variable that keeps track of total number of keys
    this->totalKeys--;
}

/************************************************
 *            BTreeSearch function              *
 ************************************************/
bool BTree::BTreeSearch(string myWord, int iteration){
    
    bool isFound;
    WordObject* wordFound;
    
    //If the root is null, the tree is empty and the key is not in the tree
    if(root == NULL)
        return false;
    
    else{
        //Begin search from root
        wordFound = root -> search(root, myWord, iteration);
        
        if (wordFound == NULL) {
            isFound = false;
        }
        else{
            
            isFound = true;
            
            //check if you need to update most frequent member variable
            if(this->highestOccurance == NULL){
                this->highestOccurance = wordFound;
            }
            else if(wordFound->getWordCount() > this->highestOccurance->getWordCount()){
                this->highestOccurance = wordFound;
            }
        }
    }
    
    return isFound;
}
/************************************************
 *                  Print function              *
 ************************************************/
const void BTree:: BTreeTraverse(){
    
    if(this->root == NULL){
        cout << "Tree is empty" << endl;
    }
    
    else{
        cout << "Tree Height is " << treeHeight << endl;
        //cout << "Tree has " << totalKeys << " total keys" << endl;
        cout << "Root has " << root->getNumOfChildren() << " children" << endl;
        cout << "Root has " << root ->getNumOfKeys() << " keys" << endl << endl;
        
        //Call TreeNode traverse function
        this->root->traverse();
    }
    
    cout << "" << endl << endl;
}

/************************************************
 *                Clear function                *
 ************************************************/
void BTree::clearTree(TreeNode* tmpRoot, LinkedList<TreeNode*>& queueList){
    
    if(tmpRoot == NULL){
        return;
    }
    else{
        
        queueList.push_back(tmpRoot);
        
        for(int i = 0; i < tmpRoot->getNumOfChildren(); i++){
            clearTree(tmpRoot->getChildArray(i), queueList);
        }
    }
}
