/** This file is the implementation of hash table
 @author Alvin Lin
 @file HashTable.h */

#include "HashEntry.h"
#include <cmath>
#ifndef HashTable_h
#define HashTable_h

template <class KeyType, class ItemType>
class HashTable {
private:
    HashEntry<KeyType, ItemType> **hashTable;
    int entryCount;
    int hashTableSize;
    int hash(char *);
    
public:
    
    // basic operation
    bool traverseHash(void visit(ItemType)&);
    bool insertEntry(HashEntry *newEntry);
    bool removeEntry(KeyType);
    bool searchEntry(KeyType);
    bool destroyHash();
};

//////////////////private//////////////////////
/** This function is a hash funciton
 @param key that is the searchkey of the item
 @param size that is the size of the hash table
 @return an int that is the index of the item */
template <class KeyType, class ItemType>
int HashTable::hash(char* key) {
    
    long int sum = 0;
    
    while (*key) {
        sum += *key * *key * key;
        key++;
    }
    
    return sum % hashTableSize;
}

//////////////////public//////////////////////
/** This function is to traverse the entire hash table
 @param visit that is a function pointer */
template <class KeyType, class ItemType>
bool HashTable::traverseHash(void visit(ItemType &)) {
    
}

/** This function is to insert a new entry into hash table
 @param key that is the new item's key
 @param item that is new item
 @return true if success */
template <class KeyType, class ItemType>
bool HashTable::insertEntry(KeyType key, ItemType item) {
    
    // call the hash funciton and locate the index
    int index = hash(key);
    hashTable += index;
    HashEntry *pCur = *hashTable;
    
    // check where to insert in the list
    while (pCur != NULL) {
        pCur = pCur->next;
    }
    
    // insert
    HashEntry *newEntry;
    newEntry->setKey(key);
    newEntry->setItem(item);
    pCur = newEntry;
}

/** This function is to delete a entry from the hash table
 @param targetKey that is the target's key
 @return true if success */
template <class KeyType, class ItemType>
bool HashTable::removeEntry(KeyType targetKey) {
    
}

/** This function is to search a target key from the hash table
 @param targetKey
 @return true if found */
template <class KeyType, class ItemType>
bool HashTable::searchEntry(KeyType searchKey) {
    
}

/** This function is to destroy the entire hash table */
template <class KeyType, class ItemType>
bool HashTable::destroyHash() {
    
}

#endif /* HashTable_h */
















