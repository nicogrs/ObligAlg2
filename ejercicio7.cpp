#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/MaxHeapImp.cpp"
#include "tads/MaxHeap.h"

using namespace std;

int comparar(int a, int b){
    return a - b;
}

int main()
{
    int pSistema;
    cin >> pSistema;
    bool res = true;
    int n;
    cin >> n;

    MaxHeap<int>* virus = new MaxHeapImp<int>(n,comparar);

    for (int i = 0; i < n; i++){
        int pot;
        cin >> pot;

        if (pot <= pSistema){
            pSistema += pot;
        }
        else {
            virus->insert(pot);
        }
    }

    while (!virus->isEmpty()){
        int pot = virus->peek();
        virus->removePeek();

        if (pot <= pSistema){
            pSistema += pot;
        }
        else {
            res = false;
        }
    }

    if(res){
        cout << "true" << endl; 
    }else{
        cout << "false" << endl; 
    }

    return 0;
}