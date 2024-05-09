#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

/*
La forma optima de atacar los virus es atacar siempre al menor.
Si atacando siempre al menor, en algun momento la potencia del sistema es menor que la del virus, es False.

ALTERNATIVA A
-> MinHeap guardando los i virus:

    Leo P
        --O(1)
    Leo N
        --O(1)

    agrego N virus a MinHeap
        Agregar a MinHeap es O(1)_cp, N veces
        --O(N)

    Mientras arbol no este vacio y no haya sido insuficiente la potencia
        Peek, remove peek (O(log N))
        comparo P con Pvirus
            si Pvirus > P
                salgo ---> False
            si no
                P++

        --maximo N veces-> NlogN (NO DA)

ALTERNATIVA B: Array donde guardo cantidad de virus con esa potencia:

    Leo P y N
    Hago array de int de tamaño N, inicializado en 0 en cada indice.
    Recorro cada Pvirus, incremento el valor en la posicion [pvirus] en 1 por cada virus con esa potencia

    Tras leer cada virus, recorro el array desde la posicion 0
        (lo que hice hasta ahora fue ordenar en orden O(N))

    Para cada indice, arrancando de 0, si la potencia del sistema es mayor que el indice, aumento la potencia en el valor de esa posicion (P += potencias[i])
    (equivalente a pelear con esa cantidad de virus de esa potencia )
    
    si el valor en ese indice es 0 sigo
    si encuentro una posicion donde P[i] > Psistema, ya salgo y entrego False (no llego a la potencia)
    Si recorro todo y salgo, entrego True

*/


int main()
{
    // TODO
    return 0;
}