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
        Node<T>* ptrNewNode = createNode(value);

        if(ptrNode == nullptr) {
            ptrNewNode = changeColor(ptrNewNode);
            return ptrNewNode;
        }

        if(value < ptrNode->payload) {
            ptrNode->ptrLeft = insertNode(ptrNode->ptrLeft, value);
        }
        else {
            ptrNode->ptrRight = insertNode(ptrNode->ptrRight, value);
        }
        
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

    // Auxiliary function 
    template<typename T>
    Node<T>* changeColor(Node<T>* ptrNode) {
        if(ptrNode == nullptr) {
            cerr << "Error in changeColor: memory allocation failed" << endl;
            exit(1);
        }

        if(ptrNode->color == RED) {
            ptrNode->color = BLACK;
            return ptrNode;
        }
        else {
            ptrNode->color = RED;
            return ptrNode;
        }
    }

    template<typename T>
    Node<T>* colorFlip(Node<T>* ptrNode) {
        if(ptrNode == nullptr) {
            cerr << "Error in colorFlip: memory allocation failed" << endl;
            exit(1);
        }

        ptrNode = changeColor(ptrNode);
        ptrNode->ptrLeft = changeColor(ptrNode->ptrLeft);
        ptrNode->ptrRight = changeColor(ptrNode->ptrRight); 
    }

    template<typename T>
    Node<T>* leftRotation(Node<T>* ptrNode) {
        // If there's no element in the right of the ptrNode, we can't do the left rotation
        // We must return the same ptrNode
        if(ptrNode->ptrRight == nullptr) {
            return ptrNode;
        }   
        else {
        Node<T>* ptrTemp = nullptr;

        ptrTemp = ptrNode->ptrRight;
        ptrNode->ptrRight = ptrTemp->ptrLeft;
        ptrTemp->ptrLeft = ptrNode;

        ptrTemp = changeColor(ptrTemp);
        ptrTemp->ptrLeft = changeColor(ptrTemp->ptrLeft);
        
        return ptrTemp;
        }
    }


    template<typename T>
    Node<T>* rightRotation(Node<T>* ptrNode) {
        // If there's no element in the left of the ptrNode, we can't do the right rotation
        // We must return the same ptrNode
        if(ptrNode->ptrLeft == nullptr) {
            return ptrNode;
        }
        else {
            Node<T>* ptrTemp = nullptr;

            ptrTemp = ptrNode->ptrLeft;
            ptrNode->ptrLeft = ptrTemp->ptrRight;
            ptrTemp->ptrRight = ptrNode;

            ptrTemp = changeColor(ptrTemp);
            ptrTemp->ptrRight = changeColor(ptrTemp->ptrRight);

            return ptrTemp;
        }
    }
}