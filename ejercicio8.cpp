#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int triosDAC(int* arr, int i, int f){
    
    int largo = f - i + 1;
    int resto = largo % 3;
    
    //casos base
    assert(resto != 0 && largo > 0);

    if (largo < 3){
        return arr[i];
    }


    //divide inicial (resto >= 0)
    int medio = largo/2 + i;
    
    int corte = medio - 2;
    int anterior;

    //veo donde hay un corte
    do {
        anterior = corte;
        corte++;
    } while (arr[corte] == arr[anterior]);

    if (corte % 3 == 0){
        return triosDAC(arr,corte,f);
    }
    else { 
        return triosDAC(arr,i,anterior);
    }
        

}



int main()
{
    int n;
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    cout << triosDAC(arr, 0, n-1);
    return 0;
}