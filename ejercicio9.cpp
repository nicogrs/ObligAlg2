#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

//Resolucion usando memoizacion
/*
Para llegar a la casilla (x-1,y-1):
1) Calculo los primos de 1 al mayor de x o y, guardo en array
2) Hago matriz de X x Y, inicializada en -1, que indica formas de llegar a cada casilla.
3) Iniciando de (x-1,y-1) calculo formas:
    - en una casilla (a,b) es la suma de las formas llegando desde arriba + las formas llegando desde abajo
    - las formas de cada uno de los lados es, sumando cada primo menor a a y b respectivamente, ej:
        --Llegando desde arriba: (b cte)
            /1/  formas(a-1,b) +
            /2/  formas(a-2,b) +
            /3/  formas(a-2,b) +
            /5/  formas(a-5,b) + .....
            /p/  formas(a-p,b) para todo p < a. p > 0.
        --Llegando desde izquierda idem pero simetrico

NOTAS:
    -si a == b, la matriz es simetrica
    -estando en la seccion "cuadrada" de la matriz tambien


*/

int* primosErastotenes(int n){
    //cout << "primos hasta " << n;
    assert(n > 0);

    bool* criba = new bool[n+1](); //cada indice es el numero
    for (int i = 0; i <= n; i++){
        criba[i] = true; //cada numero inicia como primo y se va tachando
    }
    criba[0] = false;
    criba[1] = false;
    
    int cantPrimos = 0;

    for(int i = 2; i <= n; i++){
        if (criba[i]){ //si es primo
            cantPrimos++;

            //cada multiplo de ese primo "lo tacho", no asi al primo
            for (int j = 2*i; j <= n; j += i){
                criba[j] = false;
            }
        }
    }

    //Luego hago un array solo de primos
    //La posicion 0 es la cantidad de primos
    int* primos = new int[cantPrimos+1]();
    int actual = 1;
    primos[0] = cantPrimos;
    for (int i = 0; i <= n; i++){
        if (criba[i]){
            primos[actual] = i;
            actual++;
        }
    }

    delete[] criba;
    return primos;

}

int** initMatriz(int filas, int columnas, int inicial)
{
    int** tab = new int *[filas]();
    for (int f = 0; f < filas; f++)
    {
        tab[f] = new int[columnas]();
        for (int c = 0; c < columnas; c++)
        {
            tab[f][c] = inicial;
        }

    }
    return tab;
}

int formasRec(int** &matriz, int f, int c, int* primos, int cantPrimos){
    
    if (f < 0 || c < 0)
        return 0;

    if (matriz[f][c] != -1)
        return matriz[f][c];
    
    int res = 0;
    int i = 1;
    //caso sobre borde izq, solo "miro para arriba"
    if (c <= 1){
        //recorro cada primo
        while (i <= cantPrimos && f - primos[i] >= 0){
            res += formasRec(matriz, f - primos[i], c, primos, cantPrimos);
            i++;
        }
    }
    else

    //caso sobre fila superior, miro "a la izquierda"
    if (f <= 1){
        i = 1;
        //recorro cada primo
        while (i <= cantPrimos && c - primos[i] >= 0 ){
            res += formasRec(matriz, f, c - primos[i], primos, cantPrimos);
            i++;
        }
    }
    else

    //caso en el medio
    i = 1;
    //recorro cada primo
    while (i <= cantPrimos && (c - primos[i] >= 0 || f - primos[i] >= 0 )){
        res += formasRec(matriz, f - primos[i], c, primos, cantPrimos);
        res += formasRec(matriz, f, c - primos[i], primos, cantPrimos);
        i++;
    }

    matriz[f][c] = res;
    return res;
}


void imprimirMatriz(int ** matriz, int fil, int col)
{
    for (int f = 0; f < fil; f++)
    {   
        cout << "" << endl;
        for (int c = 0; c < col; c++)
        {
            cout << "[ "<< matriz[f][c] << " ]" << " ";
        }
        
    }
}


int main()
{
    int f;
    cin >> f;
    int c;
    cin >> c;

    int * primos = primosErastotenes(max(f,c));
    int cantPrimos = primos[0];


    int ** mat2 = initMatriz(f,c,-1);
    mat2[0][0] = 1;
    mat2[f-1][c-1] = formasRec(mat2, f-1, c-1, primos, cantPrimos);

    int formas = mat2[f-1][c-1];
    if (formas == -1)
        formas = 0;
    
    cout << mat2[f-1][c-1] << endl;
    
    delete[] primos;
    return 0;
}