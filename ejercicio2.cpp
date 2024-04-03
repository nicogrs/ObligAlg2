#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

template <class T>

class MaxHeap{
    private:
    T* heap;
    int next;
    int capacity;
    
    int father(int pos) {
        return pos / 2;
    }

    int left(int pos){
        return (i * 2);
    }

    int right(int pos){
        return (i * 2) + 1;
    }



    void heapFloat(int pos){
        if (pos == 1) return;
        int fatherPos = father(pos);
        if(heap[fatherPos] > heap[pos]){
            swap(fatherPos, pos);
            heapFloat(fatherPos);
        }
    }

    void swap(int a, int b){
        T aux = heap[a];
        heap[a] = heap[b];
        heap[b] = aux;
    }

    void sink(int pos){
        int leftPos = left(pos);
        int rightPos = right(pos);
        bool hasLeftChild = leftPos < this->next;
        bool hasRightChild = rightPos < this.next;
        if(!hasLeftChild) return;
        if(!hasRightChild){
            if(this.compareTo)
        }
    }

    public:
    MaxHeap(int _capacity) : this.capacity = _capacity{
        this->next = 1;
        heap = new T[_capacity + 1]();
    }

    void insert (T elem){
        assert(!isFull());
        heap[next] = elem;
        next++;
        heapFloat(next -1)

    }

    T peek () {
        assert(!isEmpty());
        return this->heap[1];

    }
    
    void removePeek () {
        assert(!isEmpty());
        this->heap[1] = this->heap[next-1];
        this->next--;
        sink(1);
    }

    bool isFull(){
        return next > capacity;
    }

    bool isEmpty(){
        return next == 1;
    }

};

int main()
{
return 0;
}