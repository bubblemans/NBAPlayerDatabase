/** This header file contains the object of entry for hashing
    @author Alvin Lin
    @file Entry.h */

#ifndef Entry_h
#define Entry_h

template <class KeyType, class ItemType>
class Entry {
    private:
        KeyType key;
        ItempType item;
    public:
    
        // constructor
        Entry();
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

/** This function is to check if the left is equal to right
    @param Entry that is right
    @return true if is equal */
template <class KeyType, class ItemType>
bool Entry::operator ==(const Entry<KeyType, ItemType> & right) {
    return item == right.item;
}

/** This function is to check if the left is smaller than right
 @param Entry that is right
 @return true if is smaller */
template <class KeyType, class ItemType>
bool Entry::operator <(const Entry<KeyType, ItemType> & right) {
    return item < right.item;
}

/** This function is to check if the left is bigger than right
 @param Entry that is right
 @return true if is bigger */
template <class KeyType, class ItemType>
bool Entry::operator >(const Entry<KeyType, ItemType> & right) {
    return item > right.item;
}
#endif /* Entry_h */
















