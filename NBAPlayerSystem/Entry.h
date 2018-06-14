
/** This header file contains the object of entry for hashing
    @author Alvin Lin
    @file Entry.h */

#ifndef Entry_h
#define Entry_h

template <class KeyType, class ItemType>
class Entry {
    protected:
        KeyType key;
        ItemType item;
    public:
    
        // constructor
        Entry(){;}
        Entry(KeyType k, ItemType i){key = k; item = i;}
    
        // setter and getter
        void setKey(KeyType k){key = k;}
        void setItem(ItemType i) {item = i;}
        KeyType getKey(){return key;}
        ItemType getItem(){return item;}
    
        // overloaded operator
        bool operator ==(const Entry<KeyType, ItemType>& right);
        bool operator <(const Entry<KeyType, ItemType>& right);
        bool operator >(const Entry<KeyType, ItemType>& right);
};
#endif /* Entry_h */
















