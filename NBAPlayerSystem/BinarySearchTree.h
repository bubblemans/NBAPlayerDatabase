// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Amit Yativ, Alvin Lin
// IDE: Code::Blocks xCode

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include <vector>

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    
    string (*compare)(ItemType, ItemType);
    
    // interval insert function
    BinaryNode<ItemType>* _uniqueKeyTreeInsert(BinaryNode<ItemType> *nodePtr, BinaryNode<ItemType> *newNode, bool &duplicateFound);
    BinaryNode<ItemType>* _secondaryKeyTreeInsert(BinaryNode<ItemType> *nodePtr, BinaryNode<ItemType> *newNode);
    
    // interval delete function
    BinaryNode<ItemType>* _deleteUniqueKey(BinaryNode<ItemType>* nodePtr, ItemType &targetKey, bool & success);
    BinaryNode<ItemType>* _deleteOtherKeys(BinaryNode<ItemType>* nodePtr, ItemType targetKey, bool & success);
    
    // interval search function
    BinaryNode<ItemType>* _uniqueKeyTreeSearch(BinaryNode<ItemType>* nodePtr, ItemType & target) const;
    BinaryNode<ItemType>* _secondaryKeyTreeSearch(BinaryNode<ItemType>* nodePtr, ItemType & target, vector<ItemType> &storeAllFound, bool &found);
    
    // find the maximum function
    BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* nodePtr);
    BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* nodePtr);
    
public:
    
    // Constructor for compare functions
    BinarySearchTree(string compare(ItemType, ItemType))
    {
        this->compare = compare;
    }
    // Destructor
    ~BinarySearchTree(){this->clear();}
    
    
    //BUILD TREES
    bool uniqueKeyTreeInsert    (const ItemType & newEntry);
    void secondaryKeyTreeInsert (const ItemType & newEntry);
    
    // Delete a node in Unique Key Tree if found in hash search.
    bool deleteUniqueKey(ItemType & anEntry);
    
    // Delete a node in Other Key Trees.
    bool deleteOtherKeys(ItemType anEntry);
    
    // find a target key
    bool getEntryUniqueTree(ItemType& anEntry, ItemType &returnedItem) const;
    
    // find a target key (or keys) using unique key but displaying
    bool getEntrySecondaryTree(ItemType& anEntry, vector<ItemType> &storeAllFound);
    
    // find smallest node value
    void findSmallest(ItemType &returnedItem);
    
    // find largest node value
    void findLargest(ItemType &returnedItem);
    
    void updateUniqueKeyTree(ItemType targetItem, ItemType newItem);
    void updateSecondaryKeyTree(ItemType targetItem, ItemType newItem);
    
};

///////////////////////// DEFINITIONS ///////////////////////////
/************************************************************************************************/
//-------------------------------------------------------------------------------------------
// Delete in UNIQUE KEY TREE and return target value if deleted successfully

template<class ItemType>
bool BinarySearchTree<ItemType>::deleteUniqueKey(ItemType & targetKey)
{
    bool isSuccessful = false;
    
    // Call inner delete function and pass in pointer to root, target and flag.
    this->rootPtr = _deleteUniqueKey(this->rootPtr, targetKey, isSuccessful);
    return isSuccessful;
}

// Delete in OTHER TREES using returned target value from unique key tree delete.
template<class ItemType>
bool BinarySearchTree<ItemType>::deleteOtherKeys(ItemType targetKey)
{
    bool isSuccessful = false;
    // Call inner delete function and pass in pointer to root, target and flag.
    this->rootPtr = _deleteOtherKeys(this->rootPtr, targetKey, isSuccessful);
    return isSuccessful;
}


//--------------------------------BUILD TREES------------------------------------------------
template<class ItemType>
bool BinarySearchTree<ItemType>::uniqueKeyTreeInsert(const ItemType & newEntry)
{
    bool duplicateFound = false;
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    // Call inner insert function and pass in pointer to root, and new node pointer.        // TREE BY NAME
    this->rootPtr = _uniqueKeyTreeInsert(this->rootPtr, newNodePtr, duplicateFound);
    return duplicateFound;
}

template<class ItemType>
void BinarySearchTree<ItemType>::secondaryKeyTreeInsert(const ItemType & newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    // Call inner insert function and pass in pointer to root, and new node pointer.        // TREE BY BIRTHDATE
    this->rootPtr = _secondaryKeyTreeInsert(this->rootPtr, newNodePtr);
}

/************************************************************************************************/

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntryUniqueTree(ItemType& anEntry, ItemType &returnedItem) const
{
    BinaryNode<ItemType> *tempNode; // Create a temporary node pointer.
    tempNode = this->rootPtr;       // Initialize it to the root pointer.
    tempNode = _uniqueKeyTreeSearch(tempNode, anEntry);// Call the inner Unique Key Tree search function with
    // temporary node pointer and target as parameters.
    if (tempNode == NULL)                   // Item was not found, return false.
        return false;                       // Return false, search did not find target.
    
    returnedItem = tempNode->getItem();     // Item was found - set its data to reference parameter.
    return true;                            // Return true - search found target.
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntrySecondaryTree(ItemType& anEntry, vector<ItemType> &storeAllFound)
{
    bool found;
    BinaryNode<ItemType> *tempNode;
    tempNode = this->rootPtr;
    _secondaryKeyTreeSearch(tempNode, anEntry, storeAllFound, found);
    if (found == false)
        return false;
    return true;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_secondaryKeyTreeSearch(BinaryNode<ItemType>* nodePtr, ItemType & targetKey, vector<ItemType> &storeAllFound, bool &found)
{
    
    if (nodePtr == NULL)
    {
        return nodePtr;
    }
    
    if (this->compare(targetKey, nodePtr->getItem()) == "Smaller")
    {
        return _secondaryKeyTreeSearch(nodePtr->getLeftPtr(), targetKey, storeAllFound, found);
    }
    
    else if (this->compare(targetKey, nodePtr->getItem()) == "Larger")
    {
        return _secondaryKeyTreeSearch(nodePtr->getRightPtr(), targetKey, storeAllFound, found);
    }
    
    
    found = true;
    storeAllFound.push_back(nodePtr->getItem());
    
    return _secondaryKeyTreeSearch(nodePtr->getRightPtr(), targetKey, storeAllFound, found);
}

template<class ItemType>
void BinarySearchTree<ItemType>::findSmallest(ItemType &returnedItem)
{
    BinaryNode<ItemType> *tempNode; // Create a temporary node pointer.
    tempNode = this->rootPtr;       // Initialize it to the root pointer.
    tempNode = _findSmallest(tempNode); // Call the inner find smallest function with
    if (tempNode == NULL)               // Root is NULL, return.
        return;
    returnedItem = tempNode->getItem(); // Set smallest node data to reference parameter.
}

template<class ItemType>
void BinarySearchTree<ItemType>::findLargest(ItemType &returnedItem)
{
    BinaryNode<ItemType> *tempNode; // Create a temporary node pointer.
    tempNode = this->rootPtr;       // Initialize it to the root pointer.
    tempNode = _findLargest(tempNode);  // Call the inner find largest function with
    if (tempNode == NULL)               // Root is NULL, return.
        return;
    returnedItem = tempNode->getItem(); // Set largest node data to reference parameter.
}
/////////////// private functions //////////////////////////////
//-------------------------------------------------------------------------------------------
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_deleteUniqueKey(BinaryNode<ItemType>* nodePtr, ItemType &targetKey, bool & success)
{
    if (nodePtr == NULL)
    {
        return nodePtr;
    }
    
    if (this->compare(targetKey, nodePtr->getItem()) == "Smaller")
    {
        nodePtr->setLeftPtr(_deleteUniqueKey(nodePtr->getLeftPtr(), targetKey, success));
    }
    else if (this->compare(targetKey, nodePtr->getItem()) == "Larger")
    {
        nodePtr->setRightPtr(_deleteUniqueKey(nodePtr->getRightPtr(), targetKey, success));
    }
    else
    {
        targetKey = nodePtr->getItem();
        if (nodePtr->getLeftPtr() == NULL)
        {
            BinaryNode<ItemType> *tempNode = nodePtr->getRightPtr();
            delete nodePtr;
            success = true;
            return tempNode;
        }
        else if (nodePtr->getRightPtr() == NULL)
        {
            BinaryNode<ItemType> *tempNode = nodePtr->getLeftPtr();
            delete nodePtr;
            success = true;
            return tempNode;
        }
        else
        {
            BinaryNode<ItemType> *largestOnLeft = _findLargest(nodePtr->getLeftPtr());
            nodePtr->setItem(largestOnLeft->getItem());
            ItemType tempKey = largestOnLeft->getItem();
            nodePtr->setLeftPtr(_deleteUniqueKey(nodePtr->getLeftPtr(), tempKey, success));
        }
    }
    return nodePtr;
}

//-------------------------------------------------------------------------------------------
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_deleteOtherKeys(BinaryNode<ItemType>* nodePtr, ItemType targetKey, bool & success)
{
    if (nodePtr == NULL)
    {
        return nodePtr;
    }
    
    if (this->compare(targetKey, nodePtr->getItem()) == "Smaller")
    {
        nodePtr->setLeftPtr(_deleteOtherKeys(nodePtr->getLeftPtr(), targetKey, success));
    }
    
    else if (this->compare(targetKey, nodePtr->getItem()) == "Larger")
    {
        nodePtr->setRightPtr(_deleteOtherKeys(nodePtr->getRightPtr(), targetKey, success));
    }
    
    else {
        // the other key is found and check if the unique key matches
        if (targetKey == nodePtr->getItem()) {
            if (nodePtr->getLeftPtr() == NULL)
            {
                targetKey = nodePtr->getItem();
                BinaryNode<ItemType> *tempNode = nodePtr->getRightPtr();
                delete nodePtr;
                success = true;
                return tempNode;
            }
            else if (nodePtr->getRightPtr() == NULL)
            {
                targetKey = nodePtr->getItem();
                BinaryNode<ItemType> *tempNode = nodePtr->getLeftPtr();
                delete nodePtr;
                success = true;
                return tempNode;
            }
            else
            {
                targetKey = nodePtr->getItem();
                BinaryNode<ItemType> *largestOnLeft = _findLargest(nodePtr->getLeftPtr());
                nodePtr->setItem(largestOnLeft->getItem());
                targetKey = largestOnLeft->getItem();
                nodePtr->setLeftPtr(_deleteOtherKeys(nodePtr->getLeftPtr(), targetKey, success));
            }
        }
        
        // the unique key doesn't match
        else {
            nodePtr->setRightPtr(_deleteOtherKeys(nodePtr->getRightPtr(), targetKey, success));
        }
    }
    
    
    return nodePtr;
}

// SEARCH UNIQUE KEY TREE

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_uniqueKeyTreeSearch(BinaryNode<ItemType>* nodePtr, ItemType & targetKey) const
{
    if (nodePtr == NULL)
    {
        return nodePtr;
    }
    if (this->compare(targetKey, nodePtr->getItem()) == "Smaller")
    {
        return _uniqueKeyTreeSearch(nodePtr->getLeftPtr(), targetKey);
    }
    else if (this->compare(targetKey, nodePtr->getItem()) == "Larger")
    {
        return _uniqueKeyTreeSearch(nodePtr->getRightPtr(), targetKey);
    }
    return nodePtr;
}

// SEARCH SECONDARY KEY TREE


//--------------------------------BUILD TREES------------------------------------------------
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_uniqueKeyTreeInsert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode, bool &duplicateFound)
{
    // If root does not exist.
    if (nodePtr == NULL)
    {
        return newNode;
    }
    // If a duplicate exists, do not insert.
    if (this->compare(newNode->getItem(), nodePtr->getItem()) == "Neither")
    {
        duplicateFound = true;
        return newNode;
    }
    // If the new node to be inserted is smaller than current node
    if (this->compare(newNode->getItem(), nodePtr->getItem()) == "Smaller")
    {
        // Recursively call function again with left child pointer.
        nodePtr->setLeftPtr(_uniqueKeyTreeInsert(nodePtr->getLeftPtr(), newNode,duplicateFound));
    }
    else
    {   // Recursively call function again with right child pointer.
        nodePtr->setRightPtr(_uniqueKeyTreeInsert(nodePtr->getRightPtr(), newNode,duplicateFound));
    }
    duplicateFound = false;
    // Return the node.
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_secondaryKeyTreeInsert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode)
{
    // If root does not exist.
    if (nodePtr == NULL)
    {
        return newNode;
    }
    // If the new node to be inserted is smaller than current node
    if (this->compare(newNode->getItem(), nodePtr->getItem()) == "Smaller")
    {
        // Recursively call function again with left child pointer.
        nodePtr->setLeftPtr(_secondaryKeyTreeInsert(nodePtr->getLeftPtr(), newNode));
    }
    else
    {   // Recursively call function again with right child pointer.
        nodePtr->setRightPtr(_secondaryKeyTreeInsert(nodePtr->getRightPtr(), newNode));
        
    }
    // Return the node.
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findSmallest(BinaryNode<ItemType>* nodePtr)
{
    // If root does not exist.
    if (nodePtr == NULL)
    {
        cout << "No tree exists. Root is empty.";
        return nodePtr;
    }
    // If left child is NULL
    if (nodePtr->getLeftPtr() == NULL)
        return nodePtr;
    // Recursively call function again with left child pointer.
    return _findSmallest(nodePtr->getLeftPtr());
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_findLargest(BinaryNode<ItemType>* nodePtr)
{
    // If root does not exist.
    if (nodePtr == NULL)
    {
        cout << "No tree exists. Root is empty.";
        return nodePtr;
    }
    // If right child is NULL
    if (nodePtr->getRightPtr()== NULL)
        return nodePtr;
    // Recursively call function again with right child pointer.
    return _findLargest(nodePtr->getRightPtr());
}

/** This function is to update info in the item
    @param targetItem that is needed to be updated
    @param newItem that is the new info*/
template <class ItemType>
void BinarySearchTree<ItemType>::updateUniqueKeyTree(ItemType targetItem, ItemType newItem){
    
    BinaryNode<ItemType> *pCur = this->rootPtr;
    pCur = _uniqueKeyTreeSearch(pCur, targetItem);
    
    pCur->setItem(newItem);
}

/** This function is to update info in the item
 @param targetItem that is needed to be updated
 @param newItem that is the new info*/
template <class ItemType>
void BinarySearchTree<ItemType>::updateSecondaryKeyTree(ItemType targetItem, ItemType newItem){
    
    BinaryNode<ItemType> *pCur = this->rootPtr;
    pCur = _secondaryKeyTreeSearch(pCur, targetItem);
    
    pCur->setItem(newItem);
}

#endif
