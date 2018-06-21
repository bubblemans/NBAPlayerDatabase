/***********************************************
 By: Amit Yativ
 
 Additional Contributors: Alvin Lin, Bhag Sandhu, Peter Pang,
 Frank M. Carrano and Tim Henry (general design).
 
 Binary Search Tree Abstract Header File
 ************************************************/

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE
#include "BinaryTree.h"
#include <vector> // To use vector to store search data.

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    
    string (*compare)(ItemType, ItemType);
    //--------------------------------BUILD TREES------------------------------------------------
    BinaryNode<ItemType>* _uniqueKeyTreeInsert(BinaryNode<ItemType> *nodePtr, BinaryNode<ItemType> *newNode, bool &duplicateFound);
    BinaryNode<ItemType>* _secondaryKeyTreeInsert(BinaryNode<ItemType> *nodePtr, BinaryNode<ItemType> *newNode);
    //-------------------------------------------------------------------------------------------
    // internal Unique Key delete node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _deleteUniqueKey(BinaryNode<ItemType>* nodePtr, ItemType &targetKey, bool & success);
    
    // internal Other Key delete node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _deleteOtherKeys(BinaryNode<ItemType>* nodePtr, ItemType targetKey, bool & success, string);
    
    // internal find largest node: find the smallest valued node.
    BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* nodePtr);
    
    // internal find largest node: find the largest valued node.
    BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* nodePtr);
    
    // search for target node in unique key tree, by unique key
    BinaryNode<ItemType>* _uniqueKeyTreeSearch(BinaryNode<ItemType>* nodePtr, ItemType & target,
                                               ItemType &returnedItem, bool &found);
    
    // search for target node in secondary key tree, by unique key
    BinaryNode<ItemType>* _secondaryKeyTreeSearch(BinaryNode<ItemType>* nodePtr, ItemType & target,
                                                  vector<ItemType> &storeAllFound, bool &found);
    
    
public:
    
    // Constructor for compare functions
    BinarySearchTree(string compare(ItemType, ItemType))
    {
        this->compare = compare;
    }
    // Destructor
    ~BinarySearchTree(){this->clear();}
    
    
    //--------------------------------BUILD TREES------------------------------------------------
    bool uniqueKeyTreeInsert    ( ItemType  newEntry);
    void secondaryKeyTreeInsert ( ItemType  newEntry);
    //-------------------------------------------------------------------------------------------
    
    // Delete a node in Unique Key Tree if found in hash search.
    bool deleteUniqueKey(ItemType & anEntry);
    // Delete a node in Other Key Trees.
    bool deleteOtherKeys(ItemType anEntry, string);
    // find a target key
    bool getEntryUniqueTree(ItemType& anEntry, ItemType &returnedItem);
    // find a target key (or keys) using unique key but displaying
    bool getEntrySecondaryTree(ItemType& anEntry, vector<ItemType> &storeAllFound);
    // find smallest node value
    void findSmallest(ItemType &returnedItem);
    // find largest node value
    void findLargest(ItemType &returnedItem);
    // Update the Unique Key Tree
    void updateUniqueKeyTree(ItemType targetItem, ItemType newItem);
    // Update the Secondary Key Tree
    void updateSecondaryKeyTree(ItemType targetItem, ItemType newItem);
    
};

///////////////////////// WRAPPER FUNCTIONS ///////////////////////////

/***************************************************************************/
/********************* I N S E R T  W R A P P E R S ************************/
/***************************************************************************/

/***************************************************************************
 This function is a wrapper for the internal insert function,
 that builds a BST by the unique key.
 @param newEntry - a new item to insert.
 @return true if duplicate is found.
 ***************************************************************************/

template<class ItemType>
bool BinarySearchTree<ItemType>::uniqueKeyTreeInsert( ItemType  newEntry)
{
    bool duplicateFound = false;
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    // Call inner insert function and pass in pointer to root, and new node pointer.
    this->rootPtr = _uniqueKeyTreeInsert(this->rootPtr, newNodePtr, duplicateFound);
    this->count++;
    return duplicateFound;
}

/***************************************************************************
 This function is a wrapper for the internal insert function,
 that builds a BST by the secondary key.
 @param newEntry - a new item to insert.
 ***************************************************************************/

template<class ItemType>
void BinarySearchTree<ItemType>::secondaryKeyTreeInsert( ItemType  newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    // Call inner insert function and pass in pointer to root, and new node pointer.
    this->rootPtr = _secondaryKeyTreeInsert(this->rootPtr, newNodePtr);
}


/***************************************************************************/
/********************* D E L E T E  W R A P P E R S ************************/
/***************************************************************************/

/***************************************************************************
 This function is a wrapper for the internal delete function,
 that deletes a key from the unique key tree.
 @param targetKey - an item to be deleted if found.
 @return true if delete was successful.
 ***************************************************************************/

template<class ItemType>
bool BinarySearchTree<ItemType>::deleteUniqueKey(ItemType & targetKey)
{
    bool isSuccessful = false;
    
    // Call inner delete function and pass in pointer to root, target and flag.
    this->rootPtr = _deleteUniqueKey(this->rootPtr, targetKey, isSuccessful);
    return isSuccessful;
}

/***************************************************************************
 This function is a wrapper for the internal delete function,
 that deletes a key from the other trees.
 @param targetKey - an item to be deleted if found.
 @return true if delete was successful.
 ***************************************************************************/

template<class ItemType>
bool BinarySearchTree<ItemType>::deleteOtherKeys(ItemType targetKey,  string uniqueKey)
{
    bool isSuccessful = false;
    // Call inner delete function and pass in pointer to root, target and flag.
    this->rootPtr = _deleteOtherKeys(this->rootPtr, targetKey, isSuccessful, uniqueKey);
    if (isSuccessful) {
        this->count--;
    }
    return isSuccessful;
}

/***************************************************************************/
/********************* S E A R C H  W R A P P E R S ************************/
/***************************************************************************/

/***************************************************************************
 This function is a wrapper for the internal search function,
 that searches for a key in the unique tree.
 @param anEntry - an item to be searched.
 @param returnedItem - reference variable to store data of found item.
 @return true if search was successful.
 ***************************************************************************/

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntryUniqueTree(ItemType& anEntry, ItemType &returnedItem)
{
    bool found = false;
    _uniqueKeyTreeSearch(this->rootPtr, anEntry, returnedItem, found);// Call the inner Unique Key Tree search function with
    if (found == false)  // Item was not found, return false.
        return false;    // Return false, search did not find target.
    return true;         // Return true - search found target.
}

/***************************************************************************
 This function is a wrapper for the internal search function,
 that searches for a key in the secondary tree.
 @param anEntry - an item to be searched.
 @param storeAllFound - a reference vector to store data of all found keys.
 @return true if search was successful.
 ***************************************************************************/

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntrySecondaryTree(ItemType& anEntry, vector<ItemType> &storeAllFound)
{
    bool found = false;
    _secondaryKeyTreeSearch(this->rootPtr, anEntry, storeAllFound, found); // Pass in vector to store all results.
    if (found == false)  // Item was not found, return false.
        return false;    // Return false, search did not find target.
    return true;         // Return true - search found target.
}

/***************************************************************************
 This function is a wrapper for the internal search function that
 that searches for the smallest node in the unique key tree.
 @param returnedItem - reference variable to store data of found item.
 ***************************************************************************/

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

/***************************************************************************
 This function is a wrapper for the internal search  function that
 that searches for the largest node in the unique key tree.
 @param returnedItem - reference variable to store data of found item.
 ***************************************************************************/

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


//////////////////////////// PRIVATE INTERNAL FUNCTIONS ////////////////////////////////////////

/***************************************************************************/
/******************** I N S E R T  I N T E R N A L S ***********************/
/***************************************************************************/

/***************************************************************************
 This function is a private internal insert function
 that builds a BST by the unique key.
 @param nodePtr - a BinaryNode pointer to the root of the tree.
 @param newNode - a new BinaryNode to be inserted
 @param duplicateFound - flag that becomes true if duplicate is found.
 @return nodePtr
 ***************************************************************************/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_uniqueKeyTreeInsert(BinaryNode<ItemType>* nodePtr,
                                                                       BinaryNode<ItemType>* newNode, bool &duplicateFound)
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

/***************************************************************************
 This function is a private internal insert function
 that builds a BST by the secondary key.
 @param nodePtr - a BinaryNode pointer to the root of the tree.
 @param newNode - a new BinaryNode to be inserted
 @return nodePtr
 ***************************************************************************/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_secondaryKeyTreeInsert(BinaryNode<ItemType>* nodePtr,
                                                                          BinaryNode<ItemType>* newNode)
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

/***************************************************************************/
/******************** D E L E T E  I N T E R N A L S ***********************/
/***************************************************************************/

/***************************************************************************
 This function is a private internal delete function
 that deletes a key from the unique key tree.
 @param nodePtr - a BinaryNode pointer to the root of the tree.
 @param targetKey - key to be deleted from the tree
 @param success - flag that becomes true if deletion is successful.
 @return nodePtr
 ***************************************************************************/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_deleteUniqueKey(BinaryNode<ItemType>* nodePtr,
                                                                   ItemType &targetKey, bool & success)
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

/***************************************************************************
 This function is a private internal delete function
 that deletes a key from the other trees.
 @param nodePtr - a BinaryNode pointer to the root of the tree.
 @param target - key to be deleted from the tree
 @param success - flag that becomes if deletion is successful.
 @return nodePtr
 ***************************************************************************/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_deleteOtherKeys(BinaryNode<ItemType>* nodePtr,
                                                                   ItemType target, bool & success, string uniqueKey)
{
    // check if want to remvoe from a empty tree
    if (nodePtr == NULL)
    {
        return nodePtr;
    }
    
    // check if the target is in the left hand side
    if (this->compare(target, nodePtr->getItem()) == "Smaller")
    {
        nodePtr->setLeftPtr(_deleteOtherKeys(nodePtr->getLeftPtr(), target, success, uniqueKey));
    }
    
    // check if the target is in the right hand side
    else if (this->compare(target, nodePtr->getItem()) == "Larger")
    {
        nodePtr->setRightPtr(_deleteOtherKeys(nodePtr->getRightPtr(), target, success, uniqueKey));
    }
    
    // the root is the target
    else {
        
        // the other key is found and check if the unique key matches
        if (uniqueKey == nodePtr->getItem()->getName()) {
            if (nodePtr->getLeftPtr() == NULL)
            {
                target = nodePtr->getItem();
                BinaryNode<ItemType> *tempNode = nodePtr->getRightPtr();
                delete nodePtr;
                nodePtr = 0;
                success = true;
                return tempNode;
            }
            else if (nodePtr->getRightPtr() == NULL)
            {
                target = nodePtr->getItem();
                BinaryNode<ItemType> *tempNode = nodePtr->getLeftPtr();
                delete nodePtr;
                nodePtr = 0;
                success = true;
                return tempNode;
            }
            else
            {
                target = nodePtr->getItem();
                BinaryNode<ItemType> *largestOnLeft = _findLargest(nodePtr->getLeftPtr());
                nodePtr->setItem(largestOnLeft->getItem());
                //target = largestOnLeft->getItem();
                ItemType temp = largestOnLeft->getItem();
                nodePtr->setLeftPtr(_deleteOtherKeys(nodePtr->getLeftPtr(), temp, success, uniqueKey));
            }
        }
        
        // the unique key doesn't match
        else {
            nodePtr->setRightPtr(_deleteOtherKeys(nodePtr->getRightPtr(), target, success, uniqueKey));
        }
    }
    
    
    return nodePtr;
}

/***************************************************************************/
/******************** S E A R C H  I N T E R N A L S ***********************/
/***************************************************************************/

/***********************************************************************************
 This function is a private internal search function
 that searches for a key in the unique key tree.
 @param nodePtr - a BinaryNode pointer to the root of the tree.
 @param targetKey - key to be searched in the tree
 @return nodePtr
 ************************************************************************************/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_uniqueKeyTreeSearch(BinaryNode<ItemType>* nodePtr,
                                                                       ItemType & targetKey, ItemType &returnedItem, bool &found)
{
    if (nodePtr == NULL)
    {
        return nodePtr;
    }
    if (this->compare(targetKey, nodePtr->getItem()) == "Smaller")
    {
        return _uniqueKeyTreeSearch(nodePtr->getLeftPtr(), targetKey, returnedItem, found);
    }
    else if (this->compare(targetKey, nodePtr->getItem()) == "Larger")
    {
        return _uniqueKeyTreeSearch(nodePtr->getRightPtr(), targetKey, returnedItem, found);
    }
    found = true;
    returnedItem = nodePtr->getItem();
    return nodePtr;
}

/***********************************************************************************
 This function is a private internal search function
 that searches for a key in the secondary key tree.
 @param nodePtr - a BinaryNode pointer to the root of the tree.
 @param targetKey - key to be searched in the tree
 @param storeAllFound - a reference vector to store data of all found keys.
 @param found - flag that becomes true if key is found.
 @return nodePtr
 ************************************************************************************/

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_secondaryKeyTreeSearch(BinaryNode<ItemType>* nodePtr, ItemType & targetKey,
                                                                          vector<ItemType> &storeAllFound, bool &found)
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

/***************************************************************************
 This function is a private internal search function that
 that searches for the smallest node in the unique key tree.
 @param nodePtr - a BinaryNode pointer to the root of the tree.
 ***************************************************************************/

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

/***************************************************************************
 This function is a private internal search function that
 that searches for the largest node in the unique key tree.
 @param nodePtr - a BinaryNode pointer to the root of the tree.
 ***************************************************************************/

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

/***************************************************************************/
/******************** U P D A T E  I N T E R N A L S ***********************/
/***************************************************************************/

/***************************************************************************
 This function updates info in a specific node of the unique key tree
 @param targetItem - node that needs updating
 @param newItem - the new data
 ***************************************************************************/

template <class ItemType>
void BinarySearchTree<ItemType>::updateUniqueKeyTree(ItemType targetItem, ItemType newItem)
{
    ItemType *returnedItem = new ItemType;
    bool flag = false;
    BinaryNode<ItemType> *pCur = this->rootPtr;
    pCur = _uniqueKeyTreeSearch(pCur, targetItem, *returnedItem, flag);
    pCur->setItem(newItem);
}

/***************************************************************************
 This function updates info in a specific node of the secondary key tree
 @param targetItem - node that needs updatingI
 @param newItem - the new data
 ***************************************************************************/

template <class ItemType>
void BinarySearchTree<ItemType>::updateSecondaryKeyTree(ItemType targetItem, ItemType newItem)
{
    vector<ItemType> storeAllFound;
    bool flag = false;
    BinaryNode<ItemType> *pCur = this->rootPtr;
    pCur = _secondaryKeyTreeSearch(pCur, targetItem, storeAllFound, flag);
    pCur->setItem(newItem);
}

#endif
