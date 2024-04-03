#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "funciones/enteros.cpp"

using namespace std;

template <class T>

class MaxHeap{
    private:
    T* heap;
    int next;
    int capacity;
    int (*compereTo)(T,T);
    
    int father(int pos) {
        return pos / 2;
    }

    int left(int pos){
        return (pos * 2);
    }

    int right(int pos){
        return (pos * 2) + 1;
    }



    void heapFloat(int pos){
        if (pos == 1) return;
        int fatherPos = father(pos);
        if( this->compereTo(heap[fatherPos], heap[pos]) > 0 ){
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
        bool hasRightChild = rightPos < this->next;
        if(!hasLeftChild) return;
        if(!hasRightChild){ 
            if(this->compereTo(this->heap[pos], this->heap[left(pos)]) > 0){
                swap(pos, leftPos);
                sink(leftPos);
            }
        }else {
            int posToCompare = this->compereTo(heap[leftPos], heap[rightPos]) < 0 ? leftPos : rightPos; 
            if (this->compereTo(heap[pos],heap[posToCompare]) > 0){
                swap(pos, posToCompare);
                sink(posToCompare);
            }
        }
    }

    public:
    MaxHeap(int _capacity, int (*_compereTo)(T,T)) : capacity(_capacity) {
        this->next = 1;
        heap = new T[_capacity + 1]();
        this->compereTo = _compereTo;
    }

    void insert (T elem){
        assert(!isFull());
        heap[next] = elem;
        next++;
        heapFloat(next -1);

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

    T getNext(){
        return this->next;
    }

};

int compararPesos(int p1, int p2){
    return p2 - p1;
}

int main()
{   

    int cantidad;
    int entrada;
    //cout << "ingrese la cantida de elementos a ingresar" << endl;
    cin >> cantidad;
    MaxHeap <int> *myHeap = new MaxHeap<int>(cantidad, compararPesos);
    //cout << "ingrese los elementos" << endl;
    for (int i = 0; i < cantidad; i++)
    {
        cin >> entrada;
        myHeap->insert(entrada);
    }
    
    //cout << "imprimiendo todos los elementos" << endl;
    while(!myHeap->isEmpty() && myHeap->getNext() > 2){
        int aux = myHeap->peek();
        if(!(myHeap->getNext() == 2)){
        myHeap->removePeek();
        //cout << aux << " - " << myHeap->peek() << endl;
        int newValue = aux - myHeap->peek();
        myHeap->removePeek();
        if(newValue > 0){
        myHeap->insert(newValue);
        }
        }
    }
     if(myHeap->isEmpty()){
        cout << 0 << endl;
     }else{
        cout << myHeap->peek() << endl;
     }

}