#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;


template <class K, class V>

class Node {
    public:
        K key;
        V value;
        bool entregado;
        Node * next;
        Node(K _key, V _value) : key(_key), value(_value), entregado(false), next(NULL) {};
        Node(K _key, V _value, Node _next) : key(_key), entregado(false), value(_value), next(_next) {};
};

template <class K, class V>

class HashTable {
    private:
        Node<K,V> ** table;
        int N;
        int B;
        int (*hash)(K);
    public:
    HashTable (int _B, int (*_hash)(K)) {
        this->N = 0;
        this->B = _B;
        hash = _hash;
        table = new Node<K,V>*[_B]();
        for (int i = 0; i < B; i++)
        {
            table[i] = NULL;  
        } 
    }

    void insert(K _key, V _value){
        int bucket = this->hash(_key, B) % this->B;
        if(this->table[bucket] == NULL){
            this->table[bucket] = new Node<K,V> (_key, _value);
        }else{
            Node<K ,V> * aux = this ->table[bucket];
            while(aux != NULL){
                if(aux->key == _key){
                    aux->value = _value;
                    return;
                }else if(aux->next == NULL){
                    aux->next = new Node<K,V>(_key, _value);
                }
                aux = aux->next;
            }
        }
    }

    Node <K,V> searchNode(Node <K,V> *_ptrNode, K _key){
        int bucket = this->hash(_key, B) % this->B;
        _ptrNode = this->table[bucket];
        if(_ptrNode == NULL){
            return NULL;
        }else if(_ptrNode->key == _key){
            return * _ptrNode;
        }else{
            searchNode(_ptrNode->next, _key);
        }
        return NULL;
    }
    
    void update(K _key){
        int bucket = this->hash(_key, B) % this->B;
        Node <K,V> * aux = this->table[bucket];
        if(aux != NULL){
        aux->entregado = true;
        }
    }

    void imprimirOrden(K _key){
        int bucket = this->hash(_key, B) % this->B;
        Node <K,V> * aux = this->table[bucket];
        if(aux != NULL){
        cout << aux->value << endl;
        }
    }


};

    int hashModulo(string clave){
        int ret = 0;
        for (int i = 0; i < clave.size(); i++)
        {
            ret += clave[i];
        }
        return ret;
    }

    void procesarEntrada(string entrada){

    }

int main()
{

    int buckets;
    string entrada; 
    cin >> buckets; 
    HashTable<string, string> * t1 = new HashTable<string, string>((2 * buckets), hashModulo);
    for (int i = 0; i < buckets; i++)
    {
        getline(cin, entrada);     
        size_t pos1 = entrada.find(' ');
        size_t pos2 = entrada.find(' ', pos1 + 1);

        string orden =  entrada.substr(0,pos1);
        string id = entrada.substr(pos1 + 1, pos2 - 1);      
        string productos = entrada.substr(pos2 + 1);

        cout << "Orden: " << orden << " ID: " << id << " Productos: " << productos << endl;

/*         if(orden == "A"){
            t1->insert(id,productos);
        }else if(orden == "E"){
            t1->update(id);
        }else if (orden == "Q"){
            t1->imprimirOrden(id);
        } 
    }
    */
}
}