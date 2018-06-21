/** This file is the implementation of hash table
    @author Alvin Lin
    @file HashTable.h */

#include "HashEntry.h"
#include <cmath>
#include <iostream>
#include <fstream>
#ifndef HashTable_h
#define HashTable_h

using namespace std;

template <class KeyType, class ItemType>
class HashTable {
    private:
        int entryCount;
        const static int DEFAULTSIZE = 7841;
        int *listNodeCount = new int[DEFAULTSIZE];
        int hashTableSize;
        HashEntry<KeyType, ItemType> **hashTable = new HashEntry<KeyType, ItemType>*[DEFAULTSIZE];
        int hash(string);
        int badHash(string);
        int findNextPrime(int);
    
    public:
        HashTable(){
            for(int i = 0; i < DEFAULTSIZE; i++) {
                hashTable[i] = NULL;
                listNodeCount[i] = 0;
            }
            hashTableSize = DEFAULTSIZE;
            entryCount = 0;
        }
        ~HashTable();
    
        // basic operation
        bool traverseHash(void visit(ItemType));
        void traverseHashSaveFile(void visit(ItemType  , ofstream &), string);
        bool badInsertEntry(KeyType, ItemType);
        bool insertEntry(KeyType, ItemType);
        bool removeEntry(KeyType);
        bool searchEntry(KeyType, ItemType &);
        void destroyHash();
        bool isEmpty();
        int getCount(){return entryCount;}
        double getLoadFactor();
        int getCollision();
        void update(KeyType, ItemType);
        void reHash();
        void determineHashSize(int);
        void printCollision();
        double getCollisionRate();
};

//////////////////private//////////////////////
/** This function is a hash funciton
    @param key that is the searchkey of the item
    @return an int that is the index of the item */
template <class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::hash(string key) {
   
    long int sum = 0;
    
    
    for (int i = 0; i < key.length() - 1; i++) {
        sum += pow(int(key[i]), i%5);
    }
    
    return sum % this->hashTableSize;
    
}

/** This function is a bad hash funciton
 @param key that is the searchkey of the item
 @return an int that is the index of the item */
template <class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::badHash(string key) {
    
    long int sum = 0;
    
    
    for (int i = 0; i < key.length() - 1; i++) {
        sum += key[i];
    }
    
    return sum % this->hashTableSize;
    
}

/** This function is to find the next prime number
    @param target is the number that starts from
    @return int which is the next prime number */
template <class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::findNextPrime(int target) {
    bool isPrime = false;
    target++;
    
    if (target == 2) {
        return 3;
    }
    if (target == 3) {
        return 5;
    }
    
    while (!isPrime) {
        for (int i = 2; pow(i, 2) < target; i++) {
            if (target % i == 0) {
                target++;
                i = 1;
                isPrime = false;
            }
            else {
                isPrime = true;
            }
        }
    }
    
    return target;
}

//////////////////public//////////////////////

/** This is a destructor */
template <class KeyType, class ItemType>
HashTable<KeyType, ItemType>::~HashTable() {
    this->destroyHash();
}

/** This function is to traverse the entire hash table
    @param visit that is a function pointer
    @return true if the hashing is not empty */
template <class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::traverseHash(void visit(ItemType )) {
    
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

/** This function is to traverse the entire hash table and print
    @param visit that is a function pointer
    @param fileName that is the name of the output file */
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::traverseHashSaveFile(void visit(ItemType , ofstream &), string fileName) {
    
    // if the hash table is empty
    if (isEmpty()) {
        return ;
    }
    
    HashEntry<KeyType, ItemType> *pCur;
    ofstream outfile;
    outfile.open(fileName);
    
    // traverse every element in the table
    for (int i = 0; i < hashTableSize; i++) {
        pCur = hashTable[i];
        
        // traverse every node in the list
        while (pCur != NULL) {
            ItemType item = pCur->getItem();
            visit(item, outfile);
            pCur = pCur->getNext();
        }
    }

    outfile.close();
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
        while (pCur->getNext() != NULL) {
            pCur = pCur->getNext();
        }
        
        // insert                                                                                                                                                               
        HashEntry<KeyType, ItemType> *newEntry = new HashEntry<KeyType, ItemType>(key, item);
        newEntry->setNext(NULL);
        pCur->setNext(newEntry);
    }
    
    listNodeCount[index]++;
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
    listNodeCount[index]--;
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
void HashTable<KeyType, ItemType>::destroyHash() {
    
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
    //delete hashTable;
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
double HashTable<KeyType, ItemType>::getLoadFactor() {
    
    int count = 0;
    
    for (int i = 0; i < hashTableSize; i++) {
        if (hashTable[i] != NULL) {
            count++;
        }
    }
  
    return 100.0 * count / hashTableSize;
}

/** This function is to calculate total collision in the hash table */
template <class KeyType, class ItemType>
int HashTable<KeyType, ItemType>::getCollision() {
    
    int totalCollision = 0;
    HashEntry<KeyType, ItemType> *pCur;
    for (int i = 0; i < hashTableSize; i++) {
        pCur = hashTable[i];
        if (pCur != NULL && pCur->getNext() != NULL) {
            totalCollision += listNodeCount[i] - 1;
        }
    }
    
    return totalCollision;
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
            cout << *item;
            cout << "hehe\n";
            pCur->setItem(item);
            return ;
        }
        pCur = pCur->getNext();
    }
}

/** This function is to rehash the hash table */
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::reHash() {
    
    // determine the new hash table size
    int newSize = this->findNextPrime(2 * hashTableSize);
    
    // create and assign the new hash table, counter array, and counter
    HashEntry<KeyType, ItemType> **newhashTable = new HashEntry <KeyType, ItemType> *[newSize];
    int *newListNodeCount = new int[newSize];
    for (int i = 0; i < newSize; i++) {
        newhashTable[i] = NULL;
        newListNodeCount[i] = 0;
    }
    entryCount = 0;
    
    // to traverse the old hash table
    HashEntry<KeyType, ItemType> *pCur;
    
    // insert data into new hashtable
    for (int i = 0; i < hashTableSize; i++) {
        
        pCur = hashTable[i];
        
        while (pCur != NULL) {
            
            int index = hash(pCur->getKey());
            
            // check if the whole list is empty
            if (newhashTable[index] == NULL) {
                HashEntry<KeyType, ItemType> *newEntry = new HashEntry<KeyType, ItemType>(pCur->getKey(), pCur->getItem());
                newEntry->setNext(NULL);
                newhashTable[index] = newEntry;
            }
            
            else {
                
                // to traverse a list of the new hash table
                HashEntry<KeyType, ItemType> *pWalk = newhashTable[index];
                
                // check where to insert in the list
                while (pWalk->getNext() != NULL) {
                    pWalk = pWalk->getNext();
                }
                
                // insert
                HashEntry<KeyType, ItemType> *newEntry = new HashEntry<KeyType, ItemType>(pCur->getKey(), pCur->getItem());
                newEntry->setNext(NULL);
                pWalk->setNext(newEntry);
                newListNodeCount[i]++;
            }
            
            entryCount++;
            
            pCur = pCur->getNext();
        }
    }
    int sum= 0;
    for (int i = 0; i <newSize; i++) {
        sum+=listNodeCount[i];
    }
    
    // delete the old hashtable and reaasign the new one
    hashTableSize = newSize;
    delete[] hashTable;
    delete [] listNodeCount;
    this->hashTable = newhashTable;
    this->listNodeCount = newListNodeCount;
}

/** This function is to use the size that the user input to build a hash table
    @param userInputSize that is the user input's size */
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::determineHashSize(int userInputSize) {
    
    int newSize = findNextPrime(userInputSize);
    HashEntry<KeyType, ItemType> **newhashTable = new HashEntry <KeyType, ItemType> *[newSize];
    int *newListNodeCount = new int[newSize];
    for (int i = 0; i < newSize; i++) {
        newhashTable[i] = NULL;
        newListNodeCount[i] = 0;
    }
    
    hashTableSize = newSize;
    delete[] hashTable;
    delete [] listNodeCount;
    this->hashTable = newhashTable;
    this->listNodeCount = newListNodeCount;
}

/** This function is to print out all the collision */
template <class KeyType, class ItemType>
void HashTable<KeyType, ItemType>::printCollision() {
    HashEntry<KeyType, ItemType> *pCur;
    for (int i = 0; i < hashTableSize; i++) {
        pCur = hashTable[i];
        while (pCur != NULL) {
            if (pCur->getNext() != NULL) {
                pCur = pCur->getNext();
            }
            while (pCur != NULL) {
                cout << pCur->getItem();
                pCur = pCur->getNext();
            }
            cout << "------------------------\n";
        }
    }
}

/** This function is to use bad hash function insert */
template <class KeyType, class ItemType>
bool HashTable<KeyType, ItemType>::badInsertEntry(KeyType key, ItemType item) {
    
    // call the hash funciton and locate the index
    int index = badHash(key);
    
    // check if the whole list is empty
    if (hashTable[index] == NULL) {
        HashEntry<KeyType, ItemType> *newEntry = new HashEntry<KeyType, ItemType>(key, item);
        newEntry->setNext(NULL);
        hashTable[index] = newEntry;
    }
    
    else {
        HashEntry<KeyType, ItemType> *pCur = hashTable[index];
        
        // check where to insert in the list
        while (pCur->getNext() != NULL) {
            pCur = pCur->getNext();
        }
        
        // insert
        HashEntry<KeyType, ItemType> *newEntry = new HashEntry<KeyType, ItemType>(key, item);
        newEntry->setNext(NULL);
        pCur->setNext(newEntry);
        listNodeCount[index]++;
    }
    
    entryCount++;
    
    return true;
}

/** This function is to get collision rate */
template <class KeyType, class ItemType>
double HashTable<KeyType, ItemType>::getCollisionRate() {

    return 100.0 * this->getCollision() / this->getCount();
}

#endif /* HashTable_h */
















