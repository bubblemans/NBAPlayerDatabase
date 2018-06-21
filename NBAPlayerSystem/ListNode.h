/** This file is for implementation of linked list node
    @file ListNode.h
    @author Alvin Lin */

#ifndef ListNode_h
#define ListNode_h

template <class T>
class ListNode{
    private:
        T object;
        ListNode<T> *forw;
        ListNode<T> *back;
    public:
        void setObject(T m){object = m;};
        void setForw(ListNode<T> *f){forw = f;}
        void setBack(ListNode<T> *b){back = b;}
        T getObject(){return object;}
        ListNode<T> *getForw(){return forw;}
        ListNode<T> *getBack(){return back;}
};

#endif /* ListNode_h */
