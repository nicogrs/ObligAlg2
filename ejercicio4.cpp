#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads\ListImp.cpp"

using namespace std;

template <class T>
class NodoLista {
    public:
        T dato;
        NodoLista * sig;
        NodoLista(T _dato, NodoLista * _sig) : dato(_dato), sig(_sig) {};
        NodoLista(T _dato) : dato(_dato), sig(NULL) {};
};

class Arista {
    public:
        int destino;
        int peso;
        Arista(int _destino, int _peso = 1) : destino(_destino), peso(_peso) {}
};

class Grafo_LA {
    private:
        NodoLista<Arista> ** grafo;
        int V;
        bool esDirigido;
    
    public:
        Grafo_LA(int _V, bool _esDirigido) {
            this->V =  _V;
            this->esDirigido = _esDirigido;
            grafo = new NodoLista<Arista>*[_V];
            for (int i = 0; i < _V; i++)
            {
                grafo[i] = NULL;
            }
        }

        int getV() {
            return this->V;
        }

        void agregarArista(int origen, int destino, int peso = 1) {
            Arista a(destino, peso);
            grafo[origen] = new NodoLista<Arista>(a, grafo[origen]);
            if(!this->esDirigido) {
                Arista a(origen, peso);
                grafo[destino] = new NodoLista<Arista>(a, grafo[destino]);
            }
        }

        NodoLista<Arista> * adyacentesA(int origen) {
            NodoLista<Arista> * ret = NULL;
            NodoLista<Arista> * ptr =  grafo[origen];
            while(ptr != NULL) {
                Arista a(ptr->dato.destino, ptr->dato.peso);
                ret = new NodoLista<Arista>(a, ret);
                ptr = ptr->sig;
            }
            return ret;
        }
};

    bool *bfs(int nodo, Grafo_LA *g, bool *&
     encolados)
    {
        int V = g->getV();
        ListImp<int> *cola = new ListImp<int>();
        cola->insert(nodo);
        encolados[nodo-1] = true;

        while (!cola->isEmpty())
        {
            int v = cola->get(0);
            cola->removeAt(0);

            NodoLista<Arista> *ady = g->adyacentesA(v-1);
            while (ady != NULL)
            {
                int u = ady->dato.destino;
                if (!encolados[u-1])
                {
                    cola->insert(u);
                    encolados[u-1] = true;
                }
                ady = ady->sig;
            }
        }
   
        return encolados;
    }

int main()
{
    int cantVertices;
    int cantAristas;
    int cantDestinos;
    cin >> cantVertices;
    Grafo_LA *grafo = new Grafo_LA(cantVertices, true);
    cin >> cantAristas;
    for (int i = 0; i < cantAristas; i++)
    {
        int origen, destino;
        cin >> origen >> destino;
        grafo->agregarArista(origen-1, destino);
    }
    cin >> cantDestinos;
    int *destinosDeseados = new int[cantDestinos];
    for (int i = 0; i < cantDestinos; i++)
    {
        int destino;
        cin >> destino;
        destinosDeseados[i] = destino;
    }
    bool *visitados = new bool[cantVertices]();
    for (int i = 0; i < grafo->getV(); i++)
    {
        visitados[i] = false;
    }
    bfs(1, grafo, visitados);
    
    for (int i = 0; i < cantDestinos; i++)
    {
        int valor = destinosDeseados[i];
        if(visitados[valor - 1]){
            cout << valor << " si" << endl;
        }else{
            cout << valor << " no" << endl;
        }
    }
    

}

// grafo->imprimirDestinos(destinosDeseados,cantDestinos,1);

/*     bool *bfs(int origen)
    {
        bool *alcanzable = new bool[V];
        for (int i = 0; i < V; i++)
        {
            alcanzable[i] = false;
        }

        ListImp<int> cola;
        cola.insert(origen);

        while (!cola.isEmpty())
        {
            int actual = cola.get(0);
            cola.removeAt(0);

            NodoLista<Arista> *ptr = grafo[actual - 1];
            while (ptr != nullptr)
            {
                int vecino = ptr->dato.destino;
                if (!alcanzable[vecino - 1])
                {
                    alcanzable[vecino - 1] = true;
                    cola.insert(vecino);
                }
                ptr = ptr->sig;
            }
        }

        return alcanzable;
    }

    void verificarAlcanzabilidad(int *destinos, int D)
    {
        bool *alcanzableDesdeOrigen = bfs(1);

        for (int i = 0; i < D; i++)
        {
            int destino = destinos[i];
            if (alcanzableDesdeOrigen[destino - 1])
            {
                cout << destino << " si" << endl;
            }
            else
            {
                cout << destino << " no" << endl;
            }
        }

        delete[] alcanzableDesdeOrigen;
    }
};

int main()
{
    int V, E, D;
    cin >> V >> E;

    Grafo_LA grafo(V,true);

    for (int i = 0; i < E; i++)
    {
        int v, w;
        cin >> v >> w;
        grafo.agregarArista(v, w);
    }

    cin >> D;
    int *destinosDeseados = new int[D];
    for (int i = 0; i < D; i++)
    {
        cin >> destinosDeseados[i];
    }

    grafo.verificarAlcanzabilidad(destinosDeseados, D); */