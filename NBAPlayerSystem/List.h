/** This file is for implementation of linked list
    @file List.h
    @author Alvin Lin */
#ifndef List_h
#define List_h

#include "ListNode.h"

template <class T>
class List
{
    private:
        string (*compare)(T, T);
        ListNode<T> *head;
        int count;          // to keep track of the number of items in the list
    
    public:
        List(string compare(T, T));     // Constructor
        ~List();    // Destructor
    
        //Basic Linked List Operation
        int getCount() {return count;}
        ListNode<T> *getHead(){return head;}
        void traverseForw() const;
        void traverseBack() const;
        bool insertNode(T);
        bool deleteNode(T);
        bool searchNode(T &) const;
};

//**************************************************
// Constructor
// This function allocates and initializes a sentinel node
//      A sentinel (or dummy) node is an extra node added before the first data record.
//      This convention simplifies and accelerates some list-manipulation algorithms,
//      by making sure that all links can be safely dereferenced and that every list
//      (even one that contains no data elements) always has a "first" node.
//**************************************************
template <class T>
List<T>::List(string compare(T, T)) 
{
    head = new ListNode<T>;
    head -> setForw(head);
    head -> setBack(head);
    T object = NULL;
    head -> setObject(object);
    count = 0;
    this->compare = compare;
}

/** Display the list forward.*/
template <class T>
void List<T>::traverseForw() const
{
    // Display data in each node
    ListNode<T> *pCur; // Skip the sentinel node.
    pCur = head -> getForw();
    
    while (pCur != head)
    {
        cout << pCur -> getObject();
        pCur = pCur -> getForw();
    }
}

/** Display the list backward.*/
template <class T>
void List<T>::traverseBack() const
{
    ListNode<T> *pCur;
    pCur = head -> getBack();
    
    while (pCur != head)
    {
        cout << pCur -> getObject();
        pCur = pCur -> getBack();
    }
}

//**************************************************
// The insertNode function inserts a node with
// mountain copied to its value member.
//**************************************************
template <class T>
bool List<T>::insertNode(T input)
{
    
    ListNode<T> *newNode = nullptr;              // A pointer to a new node
    ListNode<T> *pCur;   // A pointer used to traverse the list
    ListNode<T> *pPre;          // A pointer to the previous node
    
    pCur = head -> getForw();
    pPre = head;
    
    // Find location: skip all nodes whose name is less than input's name
    while (pCur != head && this->compare(pCur -> getObject(), input) == "Smaller") {
        pPre = pCur;
        pCur = pCur -> getForw();
    }
  /*
    // If duplicate, return false.
    if (this->compare(pCur->getObject(), input) == "Neither") {
        return false;
    }
    */
    // Allocate a new node and store input there.
    newNode = new ListNode<T>;
    newNode -> setObject(input);
    
    // Insert the new node between pPre and pCur
    pPre -> setForw(newNode);
    pCur -> setBack(newNode);
    newNode ->setBack(pPre);
    newNode -> setForw(pCur);
    count++;
    return true;
}

//**************************************************
// The deleteNode function searches if the target
// is inside the list.
// The node, if found, will be
// deleted from the list and from memory.
//**************************************************
template <class T>
bool List<T>::deleteNode(T target)
{
    ListNode<T> *pCur;
    ListNode<T> *pPre;
    
    pCur = head -> getForw();
    pPre = head;
    
    cout << pPre -> getObject().getName() << endl;
    
    // Find node containing the target: Skip all nodes whose gpa is less than the target
    while ((pCur != head) && this->compare(pCur->getObject(), target) == "Smaller") {
        pPre = pCur;
        pCur = pCur -> getForw();
    }
    
    if ((pCur != NULL) && this->compare(pCur->getObject(), target) == "Neither") {
        pPre -> setForw(pCur -> getForw());
        pCur -> getForw() -> setBack(pPre);
        delete pCur;
        count--;
        return true;
    }
    
    return false;
}

//**************************************************
// This function is to search if the target is
// inside the list. The node's date will return true
// , if the target is found.
//**************************************************
template <class T>
bool List<T>::searchNode(T &target) const
{
    ListNode<T> *pCur;
    ListNode<T> *pPre = head;
    
    pCur = head -> getForw();
    pPre = head;
    
    while ((pCur != NULL) && (this->compare(pCur -> getObject(), target) == "Smaller"))
    {
        pPre = pCur;
        pCur = pCur -> getForw();
    }
    
    if ((pCur != NULL) && (pCur -> getObject()) == target){
        return true;
    }
    return false;
}


//**************************************************
// Destructor                                      *
// This function deletes every node in the list,   *
// and it prevents memory leaks.                   *
//**************************************************
template <class T>
List<T>::~List(){
    ListNode<T> *pCur;   // To traverse the list
    ListNode<T> *pNext;  // To point to the next node
    
    // Position nodePtr at the head of the list.
    pCur = head -> getForw();
    
    // While pCur is not at the end of the list...
    while (pCur != head)
    {
        // Save a pointer to the next node.
        pNext = pCur -> getForw();
        
        // Delete the current node.
        //cout << "DEBUG - Destructor: Now deleting " << pCur -> getObject().getName() << endl;
        delete pCur;
        
        // Position pCur at the next node.
        pCur = pNext;
    }
    
    cout << "DEBUG - Destructor: Now deleting the sentinel node\n";
    delete head; // delete the sentinel node
}

#endif /* List_h */
