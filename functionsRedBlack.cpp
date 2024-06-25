#include "functionsRedBlack.h"
#include <cstdlib>

using namespace std;

namespace RedBlackFunctions {

    template<typename T>
    Node<T>* createNode(T value) {
        Node<T>* ptrNode = (Node<T>*) malloc(sizeof(Node<T>));

        if(ptrNode == nullptr) {
            cerr << "Error in createNode: memory allocation failed" << endl;
            exit(1);
        }

        ptrNode->ptrLeft = nullptr;
        ptrNode->ptrRight = nullptr;
        ptrNode->color = RED;

        return ptrNode;
    }

    template<typename T>
    Node<T>* insertNode(Node<T>* ptrNode, T value) {
        return nullptr;
    }

    template<typename T>
    Node<T>* removeNode(Node<T>* ptrNode, T value) {
        return nullptr;
    }

    template<typename T>
    Node<T>* searchEspecific(Node<T>* ptrNode, T value) {
        return nullptr;
    }

    template<typename T>
    void traverseInOrder(Node<T>* ptrNode) {

    }

    template<typename T>
    void verifyRedBlack(Node<T>* ptrNode) {
    }

    template<typename T>
    T maxNode(Node<T>* ptrNode) {
        return 0;
    }
    
    template<typename T>
    T minNode(Node<T>* ptrNode) {
        return 0;
    }
    
    template<typename T>
    int treeHeight(Node<T>* ptrNode) {
        return 0;
    }

    template<typename T>
    Node<T>* colorFlip(Node<T>* ptrNode) {
        return nullptr;
    }

    template<typename T>
    Node<T>* leftRotation(Node<T>* ptrNode) {
        return nullptr;
    }

    template<typename T>
    Node<T>* rightRotation(Node<T>* ptrNode) {
        return nullptr;
    }
}