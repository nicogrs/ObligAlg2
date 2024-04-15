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

int *bfs(int nodo, Grafo_LA *g, int *&costo)
{
    int V = g->getV();
    int *visitado = new int[V];
    for (int i = 0; i < V; i++)
    {
        costo[i] = INT_MAX;
        visitado[i] = false;
    }

    ListImp<int> *cola = new ListImp<int>();
    cola->insert(nodo);
    costo[nodo - 1] = 0;
    visitado[nodo - 1] = true;

    while (!cola->isEmpty())
    {
        int v = cola->get(0);
        cola->removeAt(0);

        NodoLista<Arista> *ady = g->adyacentesA(v - 1);
        while (ady != NULL)
        {
            int u = ady->dato.destino;
            if (!visitado[u - 1])
            {
                cola->insert(u);
                costo[u - 1] = costo[v - 1] + 1;
                visitado[u - 1] = true;
            }
            ady = ady->sig;
        }
    }

    return costo;
}

double dijsktra(int origen, Grafo_LA *g)
{
    int *costo = new int[g->getV()]();
    bool *visitado = new bool[g->getV()]();

    for (int i = 0; i < g->getV(); i++)
    {
        costo[i] = INT_MAX;
        visitado[i] = false;
    }

    costo[origen] = 0;

    for (int i = 0; i < g->getV(); i++)
    {
        int v = -1;
        int menorCosto = INT_MAX;
        for (int j = 0; j < g->getV(); j++)
        {
            if (costo[j] < menorCosto && !visitado[j])
            {
                v = j;
                menorCosto = costo[j];
            }
        }

        if (v == -1)
            break;

        visitado[v] = true;

        NodoLista<Arista> *ady = g->adyacentesA(v);
        while (ady != NULL)
        {
            Arista a = ady->dato;
            int u = a.destino;
            int w = a.peso;
            if (!visitado[u] && costo[u] > costo[v] + w)
            {
                costo[u] = costo[v] + w;
            }
            ady = ady->sig;
        }
    }
    int max = 0;
    for (int i = 0; i < g->getV(); i++)
    {
        if (visitado[i])
        {
            max += costo[i];
        }
    }
    return max;
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

    int *visitados = new int[P + 1];
    int estaEn;
    double valor = 100000;
    for (int i = 1; i < P + 1; i++)
    {
        double aux = 0;
        if (apariciones[i] > 1)
        {
            aux = dijsktra(i, grafo);
            if (aux < valor)
            {
                valor = aux;
                estaEn = i;
            }
        }
    }
    cout << "El fugitivo está en: " << estaEn << endl;
}
