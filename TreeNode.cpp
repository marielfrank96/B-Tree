
//Mariel Frank
//Data Structures, Fall 2016
//BTree Spell Check Project
//TreeNode.cpp

#include "TreeNode.hpp"

/************************************************
 *             TreeNode Constructor             *
 ************************************************/
TreeNode::TreeNode(){
    
    mValue = 10;
    isLeaf = true;
    numberOfKeys = 0;
    numberOfChildren = 0;
}

/************************************************
 *             TreeNode Destructor              *
 ************************************************/
TreeNode::~TreeNode(){
    
}

/************************************************
 *            TreeNode InsertNonFull            *
 ************************************************/
void TreeNode::insertNonFull(WordObject myWord){
    
    int i = this->numberOfKeys;
    
    if (this->isLeaf){

        int k;
        //Iterate through list to find insertion point for key
        for(k = 0; k < numberOfKeys; k++ ){
            
            //If the word is already in the tree, do not insert again
            if(myWord.getMyWord().compare(keyArray[k].getMyWord()) == 0){
                k = -1;
                break;
            }
    
            if(myWord.getMyWord().compare(keyArray[k].getMyWord()) > 0){
                //continue through loop
            }
            else
                break;
        }
        
        if(k == -1){
            //word is already in tree, do not insert
        }
        else{
            //Move keys to make room for insertion
            while( i > k ){
                keyArray[i] = keyArray[i-1];
                i--;
            }
            //Insert new key
            keyArray[k] = myWord;
            numberOfKeys++;
        }
    }
    else{
        
        //Node is not a leaf
        
        int k;
        
        for(k = 0; k < this->numberOfKeys; k++){
            //Continue to increment until key is larger than key to insert
            if(myWord.getMyWord().compare(this->keyArray[k].getMyWord())> 0){
                //continue increment
            }
            else
                break;
        }
        
        //Make sure the found child is not full before continuing with insert
        if(childArray[k]->numberOfKeys == (mValue-1)){
    
            //Child has full key array, need to split
            splitChild(this, this->childArray[k], k);
            //Now insert into non full child
            childArray[k+1] -> insertNonFull(myWord);
        }
        else{
            childArray[k] -> insertNonFull(myWord);
        }
    }
}

/************************************************
 *                Split Function                *
 ************************************************/
void TreeNode::splitChild(TreeNode* parentNode,TreeNode* childNode, int key){
    
    //Create a new node
    TreeNode* newNode = new TreeNode();
    newNode ->isLeaf = childNode->isLeaf;
    
    int i;
    for(i = 0; i < ((mValue-1)/2); i++){
        //Move half of values from original child node to new node
        newNode->keyArray[i] = childNode->keyArray[i+((mValue)/2)];
        newNode->numberOfKeys++;
        
        //remove value copied from child array
        childNode->keyArray[i+ ((mValue)/2)].setMyWord("");
        childNode->keyArray[i+ ((mValue)/2)].setWordCount(0);
        childNode->numberOfKeys--;
    }
    
    //If child node is not a leaf, copy children accordingly from child to new node
    if(!(childNode->isLeaf)){
        
        int j;
        for(j= 0; j< (mValue/2); j++){
            
            //copy children to new array
            newNode->childArray[j] = childNode->childArray[j+(mValue/2)];
            
            //If a child is copied from childnode to newnode, decrement/increment
            if(!(childNode -> childArray[j+(mValue/2)] == NULL)){
                newNode->numberOfChildren++;
                childNode->numberOfChildren--;
            }
            
            //Remove the children that were copied
            childNode->childArray[j+(mValue/2)]= NULL;
        }
    }
    
    //Make room for new key in parent
    for(int j = parentNode->numberOfKeys-1; j> key; j--){
        parentNode->keyArray[j+1] = parentNode->keyArray[j];
    }
    
    //move children accordingly
    int k;
    for(k = parentNode->numberOfKeys; k > key+1; k-- ){
        parentNode ->childArray[k+1] = parentNode->childArray[k];
    }
    
    //copy middle key of child node to parent
    parentNode->keyArray[key] = childNode->keyArray[((mValue-1)/2)];
    parentNode->numberOfKeys++;
    
    //remove key from child node
    childNode->keyArray[((mValue-1)/2)].setMyWord("");
    childNode->keyArray[((mValue-1)/2)].setWordCount(0);
    childNode->numberOfKeys--;
    
    //Insert new node as child of parent
    parentNode->childArray[key+1] = newNode;
    parentNode->numberOfChildren++;
    
}

/************************************************
 *             Traverse Function                *
 *       Used for testing tree structure        *
 ************************************************/
void TreeNode::traverse(){
    
    cout<<"Printing root" << endl;
        
    for (int i =0; i<numberOfKeys; i++){
        cout << this->keyArray[i]<< " | ";
    }
    
    for(int i = 0; i< this->numberOfChildren; i++){
        
        cout << endl << "Printing child " << i << " of root" << endl;
        
        for(int j=0; j< this->childArray[i]->numberOfKeys; j++){
            cout << this->childArray[i]->keyArray[j]<< " | ";
        }
            
        cout << "Has children: " << childArray[i]->numberOfChildren<< endl;
        for(int k = 0; k < this->childArray[i]->numberOfChildren; k++){
         
            cout << endl << "Printing child " << k << " of child " << i << endl;
                
            for(int l =0; l< this->childArray[i]->childArray[k]->numberOfKeys; l++){
                cout << this->childArray[i] ->childArray[k]->keyArray[l] << " | ";
            }
        }
    }
}

/**********************************************************
 *              Sequential Search Function                *
 **********************************************************/
WordObject* TreeNode::search(TreeNode* root, string word, int iteration){
    
    int i = 0;
    WordObject* found = NULL;
    
    //Find first key greater than or equal to the word
    while ((i < root -> numberOfKeys) && (word.compare(root->keyArray[i].getMyWord())) > 0){
        i++;
    }
    
    //If the search key and the key in the array are equal
    if(word.compare(root->keyArray[i].getMyWord()) == 0){
        found = &root->keyArray[i];
        //Only increment word count on first iteration
        if(iteration == 1){
            root -> keyArray[i].incrementCount();
        }
        return found;
    }
    //If node is leaf, found holds value for whether key exists in tree
    if (root -> isLeaf){
        return found;
    }
    else{
        //Continue to iterate down tree
        return search(root->childArray[i], word, iteration);
    }
}

/************************************************
 *                Remove Function               *
 ************************************************/
void TreeNode::remove(string word){
  
    int index=0;
    //Find first key greater than or equal to the word
    while ((index < this->numberOfKeys) && (word.compare(this->keyArray[index].getMyWord())) > 0){
        index++;
    }
    
    //If the key to be removed is in this node
    if(index < this->numberOfKeys && (this->keyArray[index].getMyWord().compare(word)) == 0){
        
        //If the node is a leaf node, remove from leaf node
        if(this->isLeaf){
            
            for(int i = index+1; i < numberOfKeys; i++){
                
                this->keyArray[i-1] = this->keyArray[i];
            }
            
            //Decrement the number of keys in the node
            this->numberOfKeys--;
        }
        //Else, it is an inner node, remove from inner node
        else{
            removeFromInnerNode(index);
        }
    }
    //Else, need to keep iterating to find key
    else{
        
        if(this->isLeaf){
            //Word is not in the tree, do nothing
            return;
        }
        
        //Check that the next child node has enough keys
        if(this->childArray[index]->numberOfKeys < (mValue/2)){
            
            //Need to borrow keys from sibling nodes
            //Check if left siblind has enough keys
            if(index!= 0 && this->childArray[index-1]->numberOfKeys >= (mValue/2)){
                borrowPre(index);
            }
            //Check if right sibling has enough keys
            else if(index!= this->numberOfKeys && this->childArray[index+1]->numberOfKeys>= (mValue/2)){
                borrowNext(index);
            }
            else{
                //If neither siblings has enough keys, merge the child nodes
                if(index!= this->numberOfKeys){
                    mergeNodes(index);
                }
                else{
                    mergeNodes(index-1);
                }
            }
        }
        
        if(index >numberOfKeys){
            this->childArray[index-1]->remove(word);
        }
        else{
            this-> childArray[index]->remove(word);
        }
    }
}
/************************************************
 *       Remove From Inner Node Function        *
 ************************************************/
void TreeNode:: removeFromInnerNode(int index){
    
    //If the correct child array has enough keys, swap key in parent with key in child
    if(this->childArray[index]->getNumOfKeys() >= mValue/2){
        
        //Pointer used to move index to remove to a leaf node
        TreeNode* current = this->childArray[index];
        
        //Iterate down to leaf
        while(!(current->isLeaf)){
            current= current->getChildArray(numberOfKeys);
        }
        
        WordObject holder = current -> keyArray[numberOfKeys-1];
        this->keyArray[index] = holder;
        this->childArray[index]->remove(holder.getMyWord());
    }
    //If the left child doesnt have enough keys,
    //check if the right child has enough keys to swap
    else if(this->childArray[index+1]->numberOfKeys >= mValue/2){
        
        TreeNode* current = this->childArray[index+1];
        
        while(!current->isLeaf){
            current = current->childArray[0];
        }
        
        WordObject holder = current->keyArray[0];
        this->keyArray[index] = holder;
        this->childArray[index+1]->remove(holder.getMyWord());
    }
    else{
        //Neither children have enough keys,
        //need to merge children then move key to be removed down
        mergeNodes(index);
        //Remove the node
        this->childArray[index]->remove(this->keyArray[index].getMyWord());
    }
}

/************************************************
 *              Merge Nodes Function            *
 ************************************************/
void TreeNode::mergeNodes(int index){
    
    //Create pointers to two nodes to be merged
    TreeNode* child = this->childArray[index];
    TreeNode* rightChild = this->childArray[index+1];
    
    //Move key from root of subtree to left child
    child->keyArray[(mValue/2)-1] = this->keyArray[index];
    
    //Move keys from left child to right child
    for( int i =0; i < rightChild-> numberOfKeys; i++){
        child->keyArray[i+(mValue/2)] = rightChild->keyArray[i];
    }
    //If children are not leaves, move their children accordingly
    if(!child->isLeaf){
        for(int i =0; i <= rightChild->numberOfKeys; i++){
            child->childArray[i+(mValue/2)] = rightChild->childArray[i];
        }
    }
    //Shift keys in root to account for key that was moved to child
    for(int i = index+1; i< this->numberOfKeys; i++){
        this->keyArray[i-1] = this->keyArray[i];
    }
    //Shift keys in child node
    for(int i = index+2; i<=numberOfKeys; i++){
        this->childArray[i-1] = this->childArray[i];
    }
    //Increment number of children
    child->numberOfKeys = child->numberOfKeys+ rightChild->numberOfKeys + 1;
    
    //Decrement children and keys in root of subtree
    this ->numberOfChildren--;
    this ->numberOfKeys--;
    
    //Delete right child
    delete rightChild;
}

/************************************************
 *        Borrow from next node Function        *
 ************************************************/
void TreeNode::borrowNext(int index){
   
    TreeNode* child = this->childArray[index];
    TreeNode* rightChild = this->childArray[index+1];
    
    //Move key from root of subtree to left child
    child->keyArray[child->numberOfKeys] = this->keyArray[index];
    
    //If the children are not leaves, move the children accordingly
    if(!(child->isLeaf)){
        child->childArray[child->numberOfChildren] = rightChild->childArray[0];
        
        //Increment number of children
        child->numberOfChildren++;
    }
    
    //Move key from right child to root
    this->keyArray[index] = rightChild->keyArray[0];
    
    //Shift keys from right child to remove key that was moved to root
    for(int i = 0; i< rightChild->numberOfKeys-1; i++){
        rightChild->keyArray[i] = rightChild->keyArray[i+1];
    }
    //If right child is inner node, move children to accomodate for deleted key
    if(!rightChild->isLeaf){
        
        for(int i =0; i< rightChild->numberOfChildren-1; i++){
            rightChild->childArray[i] = rightChild->childArray[i+1];
        }
        //Decrement number of children
        rightChild->numberOfChildren--;
    }
    
    rightChild->numberOfKeys--;
    child->numberOfKeys++;
}

/************************************************
 *      Borrow from previous node Function      *
 ************************************************/
void TreeNode::borrowPre(int index){
    
    TreeNode* child = this->childArray[index];
    TreeNode* leftChild = this->childArray[index-1];
    
    //Shift keys in child to make room for borrowed key
    for(int i = child->numberOfKeys; i> 0; i--){
        child->keyArray[i] = child->keyArray[i-1];
    }
    //Shift the children over accordingly
    if(!(child->isLeaf)){
        for(int i = child->numberOfKeys+1; i> 0; i--){
            child->childArray[i] = child->childArray[i-1];
        }
    }
    //Move key from root of subtree to child
    child->keyArray[0] = this->keyArray[index-1];
    //Increment number of keys in child
    child->numberOfKeys++;
    
    //Move the largest child of the right node to the smallest child of the left node
    if(!child->isLeaf){
        
        child->childArray[0] = leftChild->childArray[leftChild->numberOfKeys];
        
        //Decrement and increment children
        child->numberOfChildren++;
        leftChild->numberOfChildren--;
    }
    //Move key from left child to root to fill space of key moved from root to right child
    this->keyArray[index-1] = leftChild->keyArray[leftChild->numberOfKeys-1];
    //Decrement left child number of keys
    leftChild->numberOfKeys--;
    
}
