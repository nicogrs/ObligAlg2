#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

template <class K, class V>

class Node
{
public:
    K key;
    V value;
    bool entregado;
    Node *next;
    Node(K _key, V _value) : key(_key), value(_value), entregado(false), next(NULL){};
    Node(K _key, V _value, Node * _next) : key(_key), entregado(false), value(_value), next(_next){};
};

template <class K, class V>

class HashTable
{
private:
    Node<K, V> **table;
    int N;
    int B;
    int (*hash)(K);

public:
    HashTable(int _B, int (*_hash)(K))
    {
        this->N = 0;
        this->B = _B;
        hash = _hash;
        table = new Node<K, V> *[_B]();
        for (int i = 0; i < B; i++)
        {
            table[i] = NULL;
        }
    }

    void insert(K _key, V _value)
    {
        int bucket = this->hash(_key) % this->B;
        if (this->table[bucket] == NULL)
        {
            this->table[bucket] = new Node<K, V>(_key, _value);
            this->N++;
        }
        else
        {
            Node<K, V> *aux = this->table[bucket];
            while (aux != NULL)
            {
                if (aux->key == _key)
                {
                    aux->value = _value;
                    return;
                }
                if (aux->next == NULL)
                {
                    aux->next = new Node<K, V>(_key, _value);
                    this->N++;
                    return;
                }
                aux = aux->next;
            }
        }
    }

    Node<K, V> *searchNode(K _key)
    {
        int bucket = this->hash(_key) % this->B;
        return searchNodeAux(this->table[bucket], _key);
    }

    Node<K, V> *searchNodeAux(Node<K, V> *_ptrNode, K _key)
    {
        if (_ptrNode == NULL)
        {
            return _ptrNode;
        }
        else if (_ptrNode->key == _key)
        {
            return _ptrNode;
        }
        else
        {
            return searchNodeAux(_ptrNode->next, _key);
        }
    }

    void update(K _key)
    {
        int bucket = this->hash(_key) % this->B;
        Node<K, V> *aux = searchNodeAux(this->table[bucket], _key);
        if (aux != NULL)
        {
            aux->entregado = true;
        }
    }

    void imprimirOrden(K _key)
    {
        int bucket = this->hash(_key) % this->B;
        Node<K, V> *aux = searchNodeAux(this->table[bucket], _key);
        if (aux != NULL)
        {
            if (aux->entregado == true)
            {
                cout << "Entregado" << endl;
            }
            else
            {
                cout <<  aux->key << ' ' << aux->value << endl;
            }
        }else{
            cout << "Pedido no encontrado" << endl;
        }
    }
};

int hashModulo(string clave)
{
    int ret = 0;
    for (int i = 0; i < clave.size(); i++)
    {
        ret = 31 * ret + int(clave[i]);
    }
    if(ret < 0) {
        ret = -ret;
    }
    return ret;
}

void procesarEntrada(string entrada)
{
}

int main()
{
    int buckets;
    string entrada;
    cin >> buckets;
    cin.ignore();
    HashTable<string, string> *t1 = new HashTable<string, string>((2 * buckets), hashModulo);
    for (int i = 0; i < buckets; i++)
    {
        getline(cin, entrada);

        size_t pos1 = entrada.find(' ');
        string orden = entrada.substr(0, pos1);
        string id_productos = entrada.substr(pos1 + 1);

        // cout << "Orden: " << orden << " ID: " << id << " Productos: " << productos << endl;

        if (orden == "A")
        {
            size_t pos2 = id_productos.find(' ');
            string productos = id_productos.substr(pos2 + 1);
            id_productos = id_productos.substr(0, pos2);
            t1->insert(id_productos, productos);
        }
        else if (orden == "E")
        {
            t1->update(id_productos);
        }
        else if (orden == "Q")
        {
            t1->imprimirOrden(id_productos);
        }
    }
}