#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "MaxHeap.h"
#include "MaxHeapImp.cpp"

using namespace std;

int main()
{
    MaxHeapImp<int> *v1 = new MaxHeapImp<int>(5,comparar);
};

int comparar(int a, int b){
    return b < a ? a : b;
}