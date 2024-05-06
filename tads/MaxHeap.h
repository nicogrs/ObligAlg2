#ifndef MAXHEAP_H
#define MAXHEAP_H

template <class T>
class MaxHeap
{
public:

    virtual void insert (T elem) = 0;

    virtual T peek() = 0;
    
    virtual void removePeek() = 0;

    virtual bool isFull() = 0;

    virtual bool isEmpty() = 0;

    virtual T getNext() = 0;
};


#endif