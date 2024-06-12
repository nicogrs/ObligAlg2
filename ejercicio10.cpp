#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

struct Posicion
{
    int fila;
    int columna;
};

int cantCasilleros = 0;
int N;

bool esSolucion()
{
    return cantCasilleros == (N * N);
}

void aplicarMovimiento(bool **visitados, Posicion nueva){
    visitados[nueva.fila][nueva.columna] = true;
    cantCasilleros++;
}

void removerMovimiento(bool **visitados, Posicion nueva){
    visitados[nueva.fila][nueva.columna] = false;
    cantCasilleros--;
}

bool puedoAplicarMovimiento(bool **visitados, Posicion nueva){
    return nueva.fila >= 0 && nueva.columna >= 0 && nueva.fila < N && nueva.columna < N && !visitados[nueva.fila][nueva.columna];
}


void caballoEnum(Posicion actual, bool **visitados, bool &exito)
{
    if (!exito)
    {
        if (esSolucion())
        {
            exito = true;
            return;
        }
        else
        {
            int dFila[8] = {-1, -2, -2, -1, 1, 2, 2, 1};
            int dColu[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
            for (int i = 0; i < 8; i++)
            {
                Posicion nueva = {actual.fila + dFila[i], actual.columna + dColu[i]};
                if (puedoAplicarMovimiento(visitados, nueva))
                {
                    aplicarMovimiento(visitados, nueva);
                    caballoEnum(nueva, visitados, exito);
                    if(exito) return;
                    removerMovimiento(visitados, nueva);
                }
            }
        }
    }
}

int main()
{
    cin >> N;
    int fi;
    int ci;
    cin >> fi;
    cin >> ci;
    Posicion inicial = {fi, ci};
    bool **visitados = new bool *[N];
    for(int i = 0; i < N; i++){
        visitados[i] = new bool[N]();
    }
    bool exito = false;
    aplicarMovimiento(visitados,inicial);
    caballoEnum(inicial,visitados,exito);
    if(exito){
        cout << "SI"<< endl;
    }else{
        cout << "NO" << endl;
    }
}