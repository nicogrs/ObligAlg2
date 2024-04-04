#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/ListImp.cpp"

using namespace std;

template <class T>

class AVL
{
private:
    class AVLNode
    {
    public:
        T element;
        AVLNode *left;
        AVLNode *right;
        int height;
        AVLNode(T element) : element(element), left(NULL), right(NULL), height(1) {}
    };

    AVLNode *root; // root of the tree


    int height(AVLNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return node->height;
    }

    AVLNode *rightRotate(AVLNode *y)
    {
        AVLNode *x = y->left;
        AVLNode *T2 = x->right;
        // Perform rotation
        x->right = y;
        y->left = T2;
        // Update heights
        y->height = std::max(height(y->left),
                             height(y->right)) +
                    1;
        x->height = std::max(height(x->left),
                             height(x->right)) +
                    1;
        // Return new root
        return x;
    }

    // A utility function to left
    // rotate subtree rooted with x
    AVLNode *leftRotate(AVLNode *x)
    {
        AVLNode *y = x->right;
        AVLNode *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = std::max(height(x->left),
                             height(x->right)) +
                    1;
        y->height = std::max(height(y->left),
                             height(y->right)) +
                    1;

        // Return new root
        return y;
    }

    // Get Balance factor of node N
    int getBalance(AVLNode *node)
    {
        if (node == NULL)
            return 0;
        return height(node->right) - height(node->left);
    }

    // Recursive function to insert a element
    // in the subtree rooted with node and
    // returns the new root of the subtree.
    AVLNode *insert(AVLNode *node, T element)
    {
        /* 1. Perform the normal BST insertion */
        if (node == NULL)
            return new AVLNode(element);
        if (element < node->element)
            node->left = insert(node->left, element);
        else if (element > node->element)
            node->right = insert(node->right, element);
        else // Equal elements are not allowed in BST
            return node;

        /* 2. Update height of this ancestor AVLnode */
        node->height = 1 + std::max(height(node->left),
                                    height(node->right));

        /* 3. Get the balance factor of this ancestor
            node to check whether this node became
            unbalanced */
        int balance = getBalance(node);

        // If this node becomes unbalanced, then
        // there are 4 cases

        // Left Left Case
        if (balance < -1 && element < node->left->element)
            return rightRotate(node);

        // Right Right Case
        if (balance > 1 && element > node->right->element)
            return leftRotate(node);

        // Left Right Case
        if (balance < -1 && element > node->left->element)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance > 1 && element < node->right->element)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        /* return the (unchanged) node pointer */
        return node;
    }
    void inOrder(AVLNode *node, void (*each)(T))
    {
        if (node == NULL)
        {
            return;
        }
        inOrder(node->left, each);
        each(node->element);
        inOrder(node->right, each);
    }

    bool contains(AVLNode *node, T value) {
    if (node == nullptr)
        return false;
    if (node->element == value)
        return true;
    if (value < node->element)
        return contains(node->left, value);
    else
        return contains(node->right, value);
}

public:

    AVL() : root(NULL) {}

    void insert(T element)
    {
        root = insert(root, element);
    }

    bool contains(T element)
    {
        return contains(root, element);
    }

    void inOrder(void (*each)(T))
    {
        inOrder(root, each);
    }

    void buscarPares(AVLNode * a1, AVL<T> * a2, int K, ListImp<T> &pares)
    {
        if (a1 == NULL)
        {
            return;
        }
        buscarPares(a1->left, a2, K, pares);
        int complemento = K - a1->element;
        if (a2->contains(complemento))
        {
        //    cout << a1->element << endl;
            pares.insert(a1->element);
        }
        buscarPares(a1->right, a2, K, pares);
    }

        void buscar(AVL<T> * a2, int K, ListImp<T> &pares)
    {
        buscarPares(this->root,a2,K,pares);
    }

};

int main()
{
    AVL<int> *a1 = new AVL<int>();
    AVL<int> *a2 = new AVL<int>();
    ListImp<int> *pares = new ListImp<int>();
    int cantidad;
    int entrada;
    int K;
    cin >> cantidad;
    for (int i = 0; i < cantidad; i++)
    {
        cin >> entrada;
        a1->insert(entrada);
    }
    cin >> cantidad;
    for (int i = 0; i < cantidad; i++)
    {
        cin >> entrada;
        a2->insert(entrada);
    }
    cin >> K;
    a1->buscar(a2,K,*pares);

    cout << pares->getSize() << endl;
}