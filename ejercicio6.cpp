#include <cassert>
#include <string>
#include <iostream>
#include <limits>
//#include "tads/MaxHeap.h"
#include "funciones/strings.cpp"

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



class Calle
{
public:
    int origen;
    int destino;
    int id;
    int distancia;
    int flujo;
    int estado;
    Calle(int _origen, int _destino, int _id, int _distancia, int _flujo, int _estado) : origen(_origen), destino(_destino), id(_id), distancia(_distancia), flujo(_flujo), estado(_estado) {}
    Calle() {}

};


/*
CompareTo para usar en *MaxHeap*
Si el resultado es +, b es mas prioritaria que a
*/
int compararCalles(Calle a, Calle b){

    int comp = a.distancia - b.distancia;
    //si comp > 0, a tiene mas distancia -> b es mas prioritaria

    if (comp == 0){
        comp = a.estado - b.estado;
    }

    if (comp == 0){
        comp = b.flujo - a.flujo;
    }

    if (comp == 0){
        comp = a.id - b.id;
    }

    return comp;

}


int promedio(int total, int n){
    int res = total/n;
    if (total % n >= n/2)
        res += 1;
    
    return res;
}

class Kruskal
{
    private:
        MaxHeap<Calle>* calles;
        int v;
        int e;
        int* padre;
        int* altura;

    public:
        int cant = 0;
        int distanciaTotal = 0;
        int estadoTotal = 0;

        Kruskal(MaxHeap<Calle>* _calles, int _v, int _e) : calles(_calles), v(_v), e(_e) {
            padre = new int[v + 1]();
            altura = new int[v + 1]();
            for (int i = 0; i <= v; i++){
                padre[i] = -1;
                altura[i] = 0;
            }
        }

        void imprimirCalle(Calle c){
            cout << c.origen << " ";
            cout << c.destino << " ";
            cout << c.id << " ";
            cout << c.distancia << " ";
            cout << c.flujo << " ";
            cout << c.estado << " ";

            cout << endl;

        }

        void procesarAristas(){
            while (!calles->isEmpty() && cant < v - 1){
                Calle actual = calles->peek();
                calles->removePeek();

                //si el origen y el destino tienen distinto padre, agrego
                if (buscar(actual.destino) != buscar(actual.origen)){
                    distanciaTotal += actual.distancia;
                    estadoTotal += actual.estado;
                    cant++;
                    unir(actual.destino,actual.origen);
                    imprimirCalle(actual);
                }
            }

            cout << "Distancia total a reparar: " << distanciaTotal << endl;
            cout << "Estado promedio de las calles reparadas: " << promedio(estadoTotal,cant) << endl;
        }

    int buscar(int i){
        if (padre[i] == -1){
            return i;
        }

        //path compression
        padre[i] = buscar(padre[i]);
        return padre[i];
    }

    void unir(int x, int y){
        int xPadre = buscar(x);
        int yPadre = buscar(y);

        if (xPadre == yPadre){
            return;
        }
        
        //union by rank
        if (altura[xPadre] < altura[yPadre]){
            padre[xPadre] = yPadre;
        } else if (altura[xPadre] > altura[yPadre]) {
            padre[yPadre] = xPadre;
        } else {
            padre[yPadre] = xPadre;
            altura[xPadre]++;
        }

    }
        
};

int main()
{
    int cantBarrios;
    cin >> cantBarrios;
    int cantCalles;
    cin >> cantCalles;

    MaxHeap<Calle> *heap = new MaxHeap<Calle>(cantCalles, compararCalles);
   
    for (int i = 0; i < cantCalles; i++){

        int origen;
        cin >> origen;
        int destino;
        cin >> destino;
        int id;
        cin >> id;
        int distancia;
        cin >> distancia;
        int flujo;
        cin >> flujo;
        int estado;
        cin >> estado;
        
        Calle* nueva = new Calle(origen,destino,id,distancia,flujo,estado);
        heap->insert(*nueva);
    }


    Kruskal* k = new Kruskal(heap,cantBarrios,cantCalles);
    
    k->procesarAristas();

    return 0;
}