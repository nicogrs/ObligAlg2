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

    IMPORTANTE:
        El array va de 0 a n-1, pero hay que hacer una transformacion:
        el indice del array tiene que guardar los valores siguientes a la potencia inicial del virus, porque representa los valores que puede
        llegar a obtener potencia.

        Ejemplo
            potencia inicial = 5
            n = 10
            el sistema puede tener 5 - 15 de potencia: valores mayores no alcanza porque no le dan los n
            valores menores tampoco porque arranca en el inicial
            cualquier valor menor al inicial lo ingreso en la posicion 0, porque automaticamente el virus "lo vence"
            si llego a leer algun valor de virus Mayor a (potencia inicial + n), ya salgo y entrego false porque nunca voy a alcanzar

*/


int main()
{
    int potInicial;
    cin >> potInicial;
    int potencia = potInicial;
    int n;
    cin >> n;

    int potMax = potInicial + n - 1; //no puedo vencer un virus con potencia > potMax

    int* virus = new int[n];

    for (int i = 0; i < n; i++){
        int potV;
        cin >> potV;
        if (potV > potMax){
            cout << "false";
            return 0;
        }
        else {
            // potInicial < potV <= potMax
            int indice = potV - potInicial;
            if (indice < 0){ //potencia de virus <= a potencia inicial, siempre se puede vencer
                indice = 0;
            }
            virus[indice]++;
        }
    }   

    for(int i = 0; i < n; i++){
        int potReal = potInicial + i;
        if (potReal > potencia){
            //la potencia del virus fue muy grande
            cout << "false";
            return 0;
        }
        else {
            potencia += potReal*virus[i]; //por cada virus de esa potencia, sumo esa potencia
        }
    }

    cout << "true";

    return 0;
}