#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "ejercicio2.cpp"
#include "funciones/strings.cpp"

using namespace std;

class Calle
{
public:
    int origen;
    int destino;
    int id;
    int distancia;
    int flujo;
    int estado;
    Calle(int _origen, int _destino, int _id, int _distancia, int _flujo, int _estado) : 
        origen(_origen), destino(_destino), id(_id), distancia(_distancia), flujo(_flujo), estado(_estado) {}

};

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
                    cout << calleToString(actual) << endl;
                }
            }

            cout << "Distancia total a reparar: " << distanciaTotal << endl;
            cout << "Estado promedio de las calles reparadas: " << (estadoTotal/cant) << endl;
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


Calle* stringToCalle(string str){

    string* dato = split(str,' ');

    int _origen = std::stoi(dato[0]);
    int _destino = std::stoi(dato[1]);
    int _idCalle = std::stoi(dato[2]);
    int _distancia = std::stoi(dato[3]);
    int _flujo = std::stoi(dato[4]);
    int _estado = std::stoi(dato[5]);

    Calle* nueva = new Calle(_origen,_destino,_idCalle,_distancia,_flujo,_estado);
    return nueva;
}

string calleToString(Calle c){
    string str = "";

    str += c.origen + " ";
    str += c.destino + " ";
    str += c.id + " ";
    str += c.distancia + " ";
    str += c.flujo + " ";
    str += c.estado;

    return str;
}

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

int buscar(int i){

}

int main()
{
    int cantBarrios;
    cin >> cantBarrios;
    int cantCalles;
    cin >> cantCalles;

    MaxHeap<Calle> *heap = new MaxHeap<Calle>(cantCalles,compararCalles);
    for (int i = 0; i < cantCalles; i++){
        string entrada;
        cin >> entrada;
        Calle* nueva = stringToCalle(entrada);
        heap->insert(*nueva);
    }

    Kruskal* k = new Kruskal(heap,cantBarrios,cantCalles);
    k->procesarAristas();
    
    return 0;
}