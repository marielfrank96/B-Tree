
//Mariel Frank
//Data Structures, Fall 2016
//BTree Spell Check Project
//LinkedList.h

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

template <class T>
class Node
{
    
public:
    
    //Object that holds word
    T wordInfo;
    
    //Self-referential Node
    Node<T>* next;
    
    //Constructor
    Node(T = T(), Node<T>* = NULL);
    
};  //End of Node class definition


//LL class definition
template <class T>
class LinkedList
{
    //Overloaded stream insertion operator
    template <class F>
    friend std::ostream& operator<< (std::ostream&, const LinkedList<F> &rhsObj);
    
private:
    
    //Integer to keep track of list size
    int countNodes;
    
    //Pointer to list head
    Node<T>* head;
    
    //copyList private member function
    void copyList(const LinkedList<T> &listToCopy);
    
public:
    
    //Constructor
    LinkedList();
    
    //Copy constructor
    LinkedList(const LinkedList<T>& otherLL);
    
    //Destructor
    ~LinkedList();
    
    //Overloaded = operator
    const LinkedList& operator=(const LinkedList<T>& rhsObj);
    
    //Insert function used for copylist and =operator
    void insert(T wordObject);
    
    //Build list by inserting into front
    void insertFront(T wordObject);
    
    //Build list by inserting into back
    void insertBack(T wordObject);
    
    //clear function
    void clear();
    
    //size function
    int size() const {return countNodes;};
    
    //Do I want my find to return T/F or the object
    bool find(string, int iterationNum);
    
    //Returns the node with the highest occurance
    Node<T>* highestOccurence();
    
    void remove(string wordToRemove);
    
    Node<T> getHead(){return head;}
    
    void push_back(T value);
    void pop_Back();
    
};  //End of LinkedList class definition


/************************************************************************
 *                                                                      *
 *                     Node Template Class Implementation               *
 *                                                                      *
 ************************************************************************/

/************************************************
 *             Node Constructor                 *
 ************************************************/
template <class T>
Node<T>:: Node(T value, Node<T> *nPtr)
{
    wordInfo = value;
    next = nPtr;
}

/************************************************************************
 *                                                                      *
 *                     LL Template Class Implementation                 *
 *                                                                      *
 ************************************************************************/

/************************************************
 *              LL Constructor                  *
 ************************************************/
template <class T>
LinkedList<T>::LinkedList()
{
    countNodes = 0;
    head = NULL;
    
}


/************************************************
 *              LL Copy Constructor             *
 ************************************************/
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLL)
{
    countNodes = 0;
    head = NULL;
    
    //call copy List function
    this->copyList(otherLL);
    
}

/************************************************
 *            LL copyList function              *
 ************************************************/
template <class T>
void LinkedList<T>::copyList(const LinkedList<T> &myListToCopy)
{
    Node<T>* current = myListToCopy.head;
    
    while(current!= NULL)
    {
        this -> insert(current->wordObject);
        current = current->next;
    }
    
}

/************************************************
 *              LL Destructor                   *
 ************************************************/
template <class T>
LinkedList<T>::~LinkedList()
{
    this -> clear();
}

/************************************************
 *            LL Overloaded = operator          *
 ************************************************/
template <class T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> &myObj)
{
    //Test for self-assignment
    if(this->head!= myObj.head)
    {
        this->clear();
        this->copyList(myObj);
    }
    
    return *this;
}


/************************************************
 *              LL insert()                     *
 ************************************************/
//Currently same code as insert front
template <class T>
void LinkedList<T>::insert(T wordObject)
{
    Node<T>* addMe = NULL;
    
    try
    {
        addMe = new Node<T>(wordObject);
        addMe -> next = head;
        head = addMe;
        
        countNodes++;
    }
    catch(std::bad_alloc bad)
    {
        cout << bad.what();
        throw bad;
    }
    catch(...)
    {
        string errorMessage = "Error in insert()";
        cout << "In catch all for insert()" << endl;
        throw errorMessage;
    }
}

/************************************************
 *              LL insertFront()                *
 ************************************************/
template <class T>
void LinkedList<T>::insertFront(T wordObject)
{
    Node<T>* addMe = NULL;
    
    try
    {
        addMe = new Node<T>(wordObject);
        addMe -> next = head;
        head = addMe;
        
        countNodes++;
    }
    catch(std::bad_alloc bad)
    {
        cout << bad.what();
        throw bad;
    }
    catch(...)
    {
        string errorMessage = "Error in insert()";
        cout << "In catch all for insert()" << endl;
        throw errorMessage;
    }
}

/************************************************
 *              LL insertBack()                 *
 ************************************************/
template <class T>
void LinkedList<T>::insertBack(T wordObject)
{
    cout << "in insert back" << endl;
    Node<T>* current = head;
    
    try
    {
        if(head == NULL){
            head = new Node<T>(wordObject);
        }
        else{
            
            while(current->next != NULL){
                current = current->next;
            }
            
            current -> next = new Node<T>(wordObject, NULL);
        }
        
        cout <<"added node";
        countNodes++;
    }
    catch(std::bad_alloc bad)
    {
        cout << bad.what();
        throw bad;
    }
    catch(...)
    {
        string errorMessage = "Error in insert()";
        cout << "In catch all for insert()" << endl;
        throw errorMessage;
    }
}

/************************************************
 *                 LL Find()                    *
 ************************************************/
template <class T>
bool LinkedList<T>::find(string wordToFind, int iterationNum){
    
    bool wordFound = false;
    
    try{
        
        Node<T>* current = head;
        Node<T>* trailCurrent = head;
        Node<T>* addMe = NULL;
        
        
        //Step through list and compare word to each word in each node
        for(int i = 0; i< this->size(); i++){
            
            if(wordToFind == current-> wordInfo.getMyWord()){
                
                wordFound = true;
                
                //Only increment the iteration count on first spell check
                if(iterationNum == 1){
                    current -> wordInfo.incrementCount();
                }
                
                /*****************************************
                 *                                       *
                 *      Move Node to front of list       *
                 *                                       *
                 *****************************************/
                
                //If node to move is at front, do nothing
                if( current == head){
                    //Do nothing
                }
                
                //else node is in middle of list
                else{
                    
                    addMe = current;
                    trailCurrent-> next = current->next;
                    addMe -> next = head;
                    head = addMe;
                    
                }
                
                return wordFound;
            }
            
            else{
                
                trailCurrent = current;
                current = current -> next;
            }
        }   //end of for loop
        
        
    }catch(...){
        
    }
    
    return wordFound;
}

/************************************************
 *            LL Remove word                    *
 ************************************************/
template <class T>
void LinkedList<T>::remove(string wordToRemove){
    
    try{
        
        Node<T>* current = head;
        
        //If head is null, do nothing
        if(head == NULL){}
        
        //Word being deleted should be at front of the list
        else {
            
            head = current->next;
            delete current;
            countNodes--;
            
        }
    }catch(...){
        
    }
}

/************************************************
 *              LL Clear()                      *
 ************************************************/
template <class T>
void LinkedList<T>::clear()
{
    try
    {
        Node<T>* current = head;
        
        while(current!= NULL)
        {
            head = head-> next;
            delete current;
            current = head;
        }
        
        head = NULL;
        current = NULL;
        countNodes = 0;
        
    }   //end of try block
    
    catch(...)
    {
        string errorMessage = "Error in clear()";
        cout << "In clear() catch all" << endl;
        throw errorMessage;
    }
}
/************************************************
 *          LL Highest Occurance                *
 ************************************************/
template <class T>
Node<T>* LinkedList<T>::highestOccurence(){
    
    Node<T>* highest = head;
    Node<T>* current = head;
    
    //Determines which node in the list has been accessed most frewquently
    //Iterate through list and keep track of node with highest wordCount variable
    while(current->next!= NULL){
        
        if(current->wordInfo.getWordCount() > highest->wordInfo.getWordCount()){
            highest = current;
        }
        current = current -> next;
    }
    
    return highest;
}

/************************************************
 *         Overloaded << Operator               *
 ************************************************/
template <class F>
std::ostream& operator<< (std::ostream& os, const LinkedList<F> &rhsObj)
{
    if (rhsObj.head == NULL)
    {
        os << "List is empty" << endl;
        return os;
    }
    
    Node<F>* current = rhsObj.head;
    
    while(current!= NULL)
    {
        
        os << current -> wordInfo;
        current = current->next;
    }
    
    return os;
}   //End of overloaded stream insertion operator

/************************************************
 *          LinkedList pushback(T)              *
 ************************************************/
//Node added to end of the list
template <class T>
void LinkedList<T>::push_back(T value)
{
    try{
        
        if (head == NULL)
            head = new Node<T>(value);
        
        else
        {
            //The list is not empty
            //Use current pointer to traverse list
            Node<T> *current = head;
            
            while(current -> next!= NULL)
            {
                current = current -> next;
            }   //End of while statment
            
            //current now points to last node
            //create a new Node and put it after last node
            current -> next = new Node<T>(value, NULL);
            
        }   //End of else statement
        
        countNodes++;
        
    }   //End of try block
    
    catch(std::bad_alloc bad)
    {
        cout<< bad.what()<< endl;
        //rethrow bad
        throw bad;
    }
    catch(...)
    {
        cout << " In catch all block\n"<< endl;
        std::string error = "Catch all error from push_back";
        throw error;
    }
    
}   //End of push_back function

/************************************************
 *            LinkedList popback()              *
 ************************************************/
//pop_back function removes the last list object and deallocates memory
template <class T>
void LinkedList<T>::pop_Back()
{
    try
    {
        if(head == NULL)
        {
            //do nothing
        }
        
        else if(head->next==NULL)
        {
            delete head;
            head = NULL;
            countNodes--;
        }
        
        else
        {
            Node<T>* current = head->next;
            Node<T>* trailCurrent = head;
            
            while(current->next!= NULL)
            {
                trailCurrent = current;
                current = current-> next;
                
            }   //End of while loop
            
            delete current;
            current = trailCurrent;
            trailCurrent->next = NULL;
            countNodes--;
        }
        
    }   //End of try block
    
    catch(...)
    {
        string errorMessage = "error in pop_back()";
        cout << "In pop_back() catch all" << endl;
        throw errorMessage;
    }   //end of catch block
    
}   //End of LL pop_back function


#endif /* LinkedList_h */

