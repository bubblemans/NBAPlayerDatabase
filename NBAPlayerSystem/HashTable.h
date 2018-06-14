/** This file is the implementation of hash table
    @author Alvin Lin
    @file HashTable.h */

#include "HashEntry.h"
#include <cmath>
#include <iostream>
#ifndef HashTable_h
#define HashTable_h

using namespace std;

template <class KeyType, class ItemType>
class HashTable {
    private:
        int entryCount;
        const static int DEFAULTSIZE = 18013;
        int hashTableSize;
        HashEntry<KeyType, ItemType> *hashTable[DEFAULTSIZE];
        int hash(string);
    
    public:
        HashTable(){
            for(int i = 0; i < DEFAULTSIZE; i++) {
                hashTable[i] = 0;
            }
            hashTableSize = DEFAULTSIZE;
            entryCount = 0;
        }
        HashTable(int size) {
            hashTableSize = size;
        }
        ~HashTable();
        // basic operation
        bool traverseHash(void visit(ItemType&));
        bool insertEntry(KeyType, ItemType);
        bool removeEntry(KeyType);
        bool searchEntry(KeyType, ItemType&);
        bool destroyHash();
        bool isEmpty();
        int getCount(){return entryCount;}
        int getLoadFactor();
        void reHash();
        void update(KeyType, ItemType);
};

//////////////////private//////////////////////
/** This function is a hash funciton
    @param key that is the searchkey of the item
    @return an int that is the index of the item */
template <class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::hash(string key) {
    
    long int sum = 0;
    
    for (int i = 0; i < key.length(); i++) {
        sum += pow(key[i], 3);
    }
    
    return sum % this->hashTableSize;
}

//////////////////public//////////////////////

/** This is a destructor */
template <class KeyType, class ItemType>
HashTable<KeyType, ItemType>::~HashTable() {
    
}

/** This function is to traverse the entire hash table
    @param visit that is a function pointer
    @return true if the hashing is not empty */
template <class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::traverseHash(void visit(ItemType &)) {
    
    // if the hash table is empty
    if (isEmpty()) {
        return false;
    }
    
    HashEntry<KeyType, ItemType> *pCur;
    
    // traverse every element in the table
    for (int i = 0; i < hashTableSize; i++) {
        pCur = hashTable[i];
        
        // traverse every node in the list
        while (pCur != NULL) {
            ItemType item = pCur->getItem();
            visit(item);
            pCur = pCur->getNext();
        }
    }
    return true;
}

/** This function is to insert a new entry into hash table
    @param key that is the new item's key
    @param item that is new item
    @return true if success */
template <class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::insertEntry(KeyType key, ItemType item) {
    
    // call the hash funciton and locate the index
    int index = hash(key);
    
    // check if the whole list is empty
    if (hashTable[index] == NULL) {
        HashEntry<KeyType, ItemType> *newEntry = new HashEntry<KeyType, ItemType>(key, item);
        newEntry->setNext(NULL);
        hashTable[index] = newEntry;
    }
    
    else {
        HashEntry<KeyType, ItemType> *pCur = hashTable[index];
        
        // check where to insert in the list
        while (pCur->getNext()!= NULL) {
            pCur = pCur->getNext();
        }
        
        // insert                                                                                                                                                               
        HashEntry<KeyType, ItemType> *newEntry = new HashEntry<KeyType, ItemType>(key, item);
        newEntry->setNext(NULL);
        pCur->setNext(newEntry);
    }
    
    entryCount++;
    
    return true;
}

/** This function is to delete a entry from the hash table
    @param targetKey that is the target's key
    @return true if success */
template <class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::removeEntry(KeyType targetKey) {
    
    // call the hash funciton and locate the index
    int index = hash(targetKey);
    
    // if not found
    if (hashTable[index] == NULL) {
        return false;
    }
    
    HashEntry<KeyType, ItemType> *pCur = hashTable[index];
    HashEntry<KeyType, ItemType> *pPre = NULL;
    
    // make sure not to access NULL and find the target
    while (pCur != NULL && pCur->getKey() != targetKey) {
        
        pPre = pCur;
        pCur = pCur ->getNext();
    }
    
    // check if the target is found
    if (pCur == NULL) {
        return false;
    }
    
    // check if the target is the first node
    if (pPre != NULL) {
        pPre->setNext(pCur->getNext());
    }
    else {
        hashTable[index] = pCur->getNext();
    }
    
    // delete the target
    delete pCur;
    entryCount--;
    return true;
}

/** This function is to search a target key from the hash table
    @param searchKey that is the key we are looking for
    @return true if found */
template <class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::searchEntry(KeyType searchKey, ItemType &returnedItem) {
    
    // call the hash funciton and locate the index
    int index = hash(searchKey);
    
    // if not found
    if (hashTable[index] == NULL) {
        return false;
    }
    
    HashEntry<KeyType,ItemType> *pCur = hashTable[index];
    
    // traverse the list
    while (pCur != NULL) {
        
        // check if found
        if (pCur->getKey() == searchKey) {
            returnedItem = pCur->getItem();
            return true;
        }
        pCur = pCur->getNext();
    }
    return false;
}

/** This function is to destroy the entire hash table */
template <class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::destroyHash() {
    
    // if the hash table is empty
    if (!isEmpty()) {
        
        HashEntry<KeyType, ItemType> *pCur;
        
        // traverse every element in the table
        for (int i = 0; i < hashTableSize; i++) {
            pCur = hashTable[i];
            
            // traverse every node in the list
            while (pCur != NULL) {
                HashEntry<KeyType, ItemType> *pNext = pCur->getNext();
                delete pCur;
                pCur = pNext;
            }
        }
    }
}

/** This function is to check the hash table is empty
    @return true if it's empty */
template <class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::isEmpty() {
    
    // traverse the table
    for (int i = 0; i < hashTableSize; i++) {
        if (hashTable[i] != NULL) {
            return false;
        }
    }
    
    return true;
}

/** This function is to calculate the load factor of the hashing
    @return the percentage of load factor */
template <class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::getLoadFactor() {
    
}

/** This function is to rehash the hash table */
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::reHash() {
    
    // determine the new hash table size
    int newSize = 0;
    HashEntry<KeyType, ItemType> **newhashTable = new HashEntry <KeyType, ItemType> *[newSize];
   
    // insert data into new hashtable
    
    // delete the old hashtable and reaasign the new one
    delete hashTable;
    this->hashTable = newhashTable;
}

/** This function is to update some info of the object
    @param key that is te search key
    @param item that is the updated item */
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::update(KeyType key, ItemType item) {

    // call the hash funciton and locate the index
    int index = hash(key);
    
    HashEntry<KeyType,ItemType> *pCur = hashTable[index];
    
    // traverse the list
    while (pCur != NULL) {
        
        // check if found
        if (pCur->getKey() == key) {
            pCur->setItem(item);
            return ;
        }
        pCur = pCur->getNext();
    }
}

#endif /* HashTable_h */
















