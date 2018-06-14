// Binary Tree Abstract Base Class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Amit Yativ
// IDE: Code::Blocks

#ifndef _BINARY_TREE
#define _BINARY_TREE
#include <iostream>
#include "Queue.h"      // To utilize queue.
#include "Stack.h"      // To utilize stack.
#include "BinaryNode.h"
#include <vector>


using std::cout;
using std::endl;

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree(){}
	BinaryTree & operator = (const BinaryTree & sourceTree);

	// common functions for all binary trees
 	bool isEmpty() const	      {return count == 0;}
	int size() const	          {return count;}
	void clear()			      {destroyTree(rootPtr); rootPtr = 0; count = 0;}

	// Depth-First Traversals
	void preOrder(void visit(ItemType &))       const{_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &))        const{_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &))      const{_postorder(visit, rootPtr);}
    void breadthFirst(void visit(ItemType&))    const{_breadthFirst(visit, rootPtr);}
    void printIndented(void visit(ItemType &),
                       int &keepTrack)          const{_printIndented(visit, rootPtr, keepTrack);}

    //-------------------------------------------------------------------------------------------------------
    // Depth-First Traversals (Iterative).
    void iterativePreOrder(void visit(ItemType &))    const{_iterativePreOrder(visit, rootPtr);}
    void iterativeInOrder(void visit(ItemType &))     const{_iterativeInOrder(visit, rootPtr);}
    void iterativePostOrder(void visit(ItemType &))   const{_iterativePostOrder(visit, rootPtr);}
    //-------------------------------------------------------------------------------------------------------

	// abstract functions to be implemented by derived class
	virtual bool uniqueKeyTreeInsert    (const ItemType & newData) = 0;
	virtual void secondaryKeyTreeInsert (const ItemType & newData) = 0;

	virtual bool deleteUniqueKey       (ItemType & targetKey) = 0;
	virtual bool deleteOtherKeys       (ItemType targetKey) = 0;
	virtual bool getEntryUniqueTree    (ItemType & anEntry, ItemType & returnedItem) const = 0;
	virtual bool getEntrySecondaryTree (ItemType & anEntry, vector<ItemType> &storeAllFound) = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder     (void visit(ItemType &), BinaryNode<ItemType> *nodePtr)                 const;
	void _inorder      (void visit(ItemType &), BinaryNode<ItemType> *nodePtr)                 const;
	void _postorder    (void visit(ItemType &), BinaryNode<ItemType> *nodePtr)                 const;
	void _breadthFirst (void visit(ItemType &), BinaryNode<ItemType> *nodePtr)                 const;
    void _printIndented(void visit(ItemType &), BinaryNode<ItemType> *nodePtr, int &keepTrack) const;

    //-------------------------------------------------------------------------------------------------------
    // Depth-First Traversals (Iterative).
    void _iterativePreOrder  (void visit(ItemType &), BinaryNode<ItemType> *nodePtr) const;
    void _iterativeInOrder   (void visit(ItemType &), BinaryNode<ItemType> *nodePtr) const;
    void _iterativePostOrder (void visit(ItemType &), BinaryNode<ItemType> *nodePtr) const;
    //-------------------------------------------------------------------------------------------------------
};

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
   // Destroy the tree recursively.
   if (nodePtr != NULL)
   {
      this->destroyTree(nodePtr->getLeftPtr());
      this->destroyTree(nodePtr->getRightPtr());
      delete nodePtr;
   }
}

template<class ItemType>
void BinaryTree<ItemType>::_iterativePreOrder(void visit(ItemType &), BinaryNode<ItemType> *nodePtr) const
{
    // Display the pre-order traversal of the tree, iteratively.

    // If the root does not exist, return.
    if (nodePtr == NULL)
    {
        return;
    }
    ItemType *item = new ItemType;                                          // Create item to store data.
    Stack<BinaryNode<ItemType>*> *stack = new Stack<BinaryNode<ItemType>*>; // Create empty stack.

    stack->push(nodePtr);                        // push node pointer into stack.

    while (!stack->isEmpty())                    // Loop while stack is not empty.
    {
        stack->pop(nodePtr);                     // Pop node pointer out of stack.
        *item = nodePtr->getItem();              // Store item inside node pointer.
        visit(*item);                            // Display the item.

        if (nodePtr->getRightPtr())              // If right pointer not NULL.
        {
            stack->push(nodePtr->getRightPtr()); // Push right pointer.
        }
        if (nodePtr->getLeftPtr())               // If left pointer not NULL.
        {
            stack->push(nodePtr->getLeftPtr());  // Push left pointer.
        }
    }
    delete stack;                                // Delete dynamically allocated stack of nodes.
    delete item;                                 // Delete dynamically allocated item.
}

template<class ItemType>
void BinaryTree<ItemType>::_iterativeInOrder(void visit(ItemType &), BinaryNode<ItemType> *nodePtr) const
{
    // Display the in-order traversal of the tree, iteratively.

    // If the root does not exist, return.
    if (nodePtr == NULL)
    {
        return;
    }
    ItemType *item = new ItemType;                                          // Create item to store data.
    Stack<BinaryNode<ItemType>*> *stack = new Stack<BinaryNode<ItemType>*>; // Create empty stack.

    // Loop while stack is not empty or node pointer isn't NULL.
    while (!stack->isEmpty() || nodePtr != NULL)
    {
        if (nodePtr != NULL)                   // If the node pointer is not NULL.
        {
            stack->push(nodePtr);              // Push the root to the stack.
            nodePtr = nodePtr->getLeftPtr();   // Set the node to its left child.
        }
        else                                   // If the node is NULL, that means we have reached
                                               // the left-most node.
        {
            stack->pop(nodePtr);               // Pop that node from the stack.
            *item = nodePtr->getItem();        // Store the data.
            visit(*item);                      // Display the data.
            nodePtr = nodePtr->getRightPtr();  // Set the node to its right child.
        }
    }
    delete stack;                              // Delete dynamically allocated stack of nodes.
    delete item;                               // Delete dynamically allocated item.
}

template<class ItemType>
void BinaryTree<ItemType>::_iterativePostOrder(void visit(ItemType &), BinaryNode<ItemType> *nodePtr) const
{
    // Display the post-order traversal of the tree, iteratively.

    // If the root does not exist, return.
    if (nodePtr == NULL)
    {
        return;
    }
    ItemType *item = new ItemType;                                                // Create item to store data.
    Stack<BinaryNode<ItemType>*> *stack = new Stack<BinaryNode<ItemType>*>;       // Create empty stack.
    Stack<ItemType> *helperStack = new Stack<ItemType>;                           // Create helper stack.
    stack->push(nodePtr);                        // Push root to stack.
    while (!stack->isEmpty())                    // Loop while stack not empty.
    {
        stack->pop(nodePtr);                     // Pop node pointer.
        helperStack->push(nodePtr->getItem());   // Push the item in that node pointer to helper stack.

        if (nodePtr->getLeftPtr())               // If left child exists
        {
            stack->push(nodePtr->getLeftPtr());  // Push the left child into stack.
        }
        if (nodePtr->getRightPtr())              // If the right child exists.
        {
            stack->push(nodePtr->getRightPtr()); // Push the right child into stack.
        }
    }
    while (!helperStack->isEmpty())              // Loop while helper stack not empty.
    {
        helperStack->pop(*item);                 // Pop item and store.
        visit(*item);                            // Display item data.
    }
    delete stack;                                // Delete dynamically allocated stack of nodes.
    delete helperStack;                          // Delete dynamically allocated stack of ItemTypes.
    delete item;
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    // Display the in-order traversal of the tree,recursively.
    if (nodePtr)
    {
        ItemType item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    // Display the pre-order traversal of the tree,recursively.
	if (nodePtr)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    // Display the post-order traversal of the tree,recursively.
    if (nodePtr)
    {
        ItemType item = nodePtr->getItem();
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        visit(item);
    }
}

template<class ItemType>
void BinaryTree<ItemType>::_breadthFirst(void visit(ItemType &), BinaryNode<ItemType> *nodePtr) const
{
    // Display the breadth-first traversal of the tree, recursively using a queue.
    ItemType item;
    Queue<BinaryNode<ItemType>*> *queue = new Queue<BinaryNode<ItemType>*>; // Declare a Queue.

    if (nodePtr == NULL)
    {
        return;
    }
    queue->enqueue(nodePtr);            // Enqueue node pointer into queue.

    while (!queue->isEmpty())           // Loop while queue is not empty.
    {
        queue->queueFront(nodePtr);     // Set the front of the queue to node pointer.
        queue->dequeue(nodePtr);        // Dequeue node pointer.

        item = nodePtr->getItem();

        visit(item);                    // Display the Toy ID.

        if (nodePtr->getLeftPtr() != NULL)
        {
            queue->enqueue(nodePtr->getLeftPtr());  // Enqueue node left child.
        }
        if (nodePtr->getRightPtr() != NULL)
        {
            queue->enqueue(nodePtr->getRightPtr()); // Enqueue node right child.
        }
    }
    delete queue;

}

template<class ItemType>
void BinaryTree<ItemType>::_printIndented(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int &keepTrack) const
{
    if (nodePtr == NULL)
    {
        return;
    }
    ItemType theItem = nodePtr->getItem(); // Declare and initialize an item to the root's item.

    int indent = 0;             // Counter for the indentation.

    // Loop while the indentation is less than the level tracker.
    while (indent++ < keepTrack)
        cout << '\t';           // Display the indentation.

    keepTrack++;                // Increment the level tracker.
    cout << keepTrack << ".  ";  // Display the tracker with a period after.
    visit(theItem);
    cout << endl; // Skip a line.

    // Recursively call the indentation function with visit function, right and
    // left tree pointers and tracker as parameters.
    _printIndented(visit, nodePtr->getRightPtr(), keepTrack); // Recursion - right side
    _printIndented(visit, nodePtr->getLeftPtr(), keepTrack);  // Recursion - left side

    //Reset tracker.
    keepTrack--;
}

#endif

