#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads\ListImp.cpp"

using namespace std;

template <class T>
class NodoLista
{
public:
    T dato;
    NodoLista *sig;
    NodoLista(T _dato, NodoLista *_sig) : dato(_dato), sig(_sig){};
    NodoLista(T _dato) : dato(_dato), sig(NULL){};
};

class Arista
{
public:
    int destino;
    int peso;
    Arista(int _destino, int _peso = 1) : destino(_destino), peso(_peso) {}
};

class Grafo_LA
{
private:
    NodoLista<Arista> **grafo;
    int V;
    bool esDirigido;

public:
    Grafo_LA(int _V, bool _esDirigido)
    {
        this->V = _V;
        this->esDirigido = _esDirigido;
        grafo = new NodoLista<Arista> *[_V];
        for (int i = 0; i < _V; i++)
        {
            grafo[i] = NULL;
        }
    }

    int getV()
    {
        return this->V;
    }

    void agregarArista(int origen, int destino, int peso = 1)
    {
        Arista a(destino, peso);
        grafo[origen] = new NodoLista<Arista>(a, grafo[origen]);
        if (!this->esDirigido)
        {
            Arista a(origen, peso);
            grafo[destino] = new NodoLista<Arista>(a, grafo[destino]);
        }
    }

    NodoLista<Arista> *adyacentesA(int origen)
    {
        NodoLista<Arista> *ret = NULL;
        NodoLista<Arista> *ptr = grafo[origen];
        while (ptr != NULL)
        {
            Arista a(ptr->dato.destino, ptr->dato.peso);
            ret = new NodoLista<Arista>(a, ret);
            ptr = ptr->sig;
        }
        return ret;
    }
};

int *bfs(int nodo, Grafo_LA *g, int *&encolados)
{
    int V = g->getV();
    ListImp<int> *cola = new ListImp<int>();
    cola->insert(nodo);
    encolados[nodo] = 0;

    while (!cola->isEmpty())
    {
        int cont = 0;
        int v = cola->get(0);
        cola->removeAt(0);

        NodoLista<Arista> *ady = g->adyacentesA(v);
        while (ady != NULL)
        {
            int u = ady->dato.destino;
            cont++;
            if (encolados[u] == -1)
            {
                cout << "estoy en " << u << endl;
                cola->insert(u);
                encolados[u] = cont;
            }
            ady = ady->sig;
        }
    }

    return encolados;
}

int main()
{
    int P, L;
    cin >> P >> L;
    Grafo_LA *grafo = new Grafo_LA(P + 1, false);
    int *apariciones = new int[P + 1];
    for (int i = 1; i < P + 1; i++)
    {
        apariciones[i] = 0;
    }
    for (int i = 0; i < L; i++)
    {
        int entrada;
        int destino;
        cin >> entrada;
        cin >> destino;
        apariciones[entrada] += 1;
        while (destino != 0)
        {
            apariciones[destino] += 1;
            grafo->agregarArista(entrada, destino);
            entrada = destino;
            cin >> destino;
        }
    }

    int *visitados = new int[P+1]();
    for (int i = 0; i < grafo->getV(); i++)
    {
        visitados[i] = -1;
    }

    int estaEn;
    double valor = INT_MAX;
    for (int i = 1; i < P + 1; i++)
    {
       if(apariciones[i] > 1){
        bfs(i,grafo,visitados); 
       }
       int aux = 0;
       for (int i = 1; i < P + 1; i++)
       {
        aux += visitados[i];
       }

       if((aux / P) < valor){
        valor = (aux / P);
        estaEn = i;
       }
    }
    cout << "El fugitivo está en: " << estaEn << endl;
}
