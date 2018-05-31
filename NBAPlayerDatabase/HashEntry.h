/** This header file is the hash cell of hash table
    @author Alvin Lin
    @file HashEntry.h */

#include "Entry.h"
#ifndef HashEntry_h
#define HashEntry_h

template <class KeyType, class ItemType>
class HashEntry: public Entry<KeyType, ItemType> {
    private:
        HashEntry *next;
    public:
        
        // constructor
        HashEntry();
        HashEntry(KeyType k, ItemType i){this->key = k; this->item = i;}
        HashEntry(KeyType k, ItemType i, HashEntry *n){this->key = k; this->item = i; next = n;}
        
        // getter and setter
        void setNext(HashEntry *n){next = n;}
        HashEntry *getNext(){return next;}
}

#endif /* HashEntry_h */














