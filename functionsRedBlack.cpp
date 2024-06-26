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

        // Initialize the new node
        ptrNode->ptrLeft = nullptr;
        ptrNode->ptrRight = nullptr;
        ptrNode->color = RED;

        return ptrNode;
    }

    template<typename T>
    Node<T>* insertNode(Node<T>* ptrNode, T value) {
        Node<T>* ptrNewNode = createNode(value);

        // If the tree is empty, insert the new node as the root
        if(ptrNode == nullptr) {
            ptrNewNode = changeColor(ptrNewNode);
            return ptrNewNode;
        }

        // Inserting the node as a Binary Tree
        if(value < ptrNode->payload)
            ptrNode->ptrLeft = insertNode(ptrNode->ptrLeft, value);
        else
            ptrNode->ptrRight = insertNode(ptrNode->ptrRight, value);


        // Rearranging nodes to form a Red-Black Tree
        if((ptrNode->ptrRight != nullptr && ptrNode->ptrRight->color == RED) && 
           (ptrNode->ptrLeft == nullptr || ptrNode->ptrLeft->color == BLACK)) {
            ptrNode = leftRotation(ptrNode);
        }
        if(ptrNode->ptrLeft != nullptr && ptrNode->ptrLeft->color == RED && 
           ptrNode->ptrLeft->ptrLeft != nullptr && ptrNode->ptrLeft->ptrLeft->color == RED) {
            ptrNode = rightRotation(ptrNode);
        }

        if(ptrNode->ptrLeft != nullptr && ptrNode->ptrLeft->color == RED && 
           ptrNode->ptrRight != nullptr && ptrNode->ptrRight->color == RED) {
            flipColors(ptrNode);
        }

        return ptrNode;
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
        if (ptrNode == nullptr) {
            cerr << "Error in maxNode: the tree is empty" << endl;
            exit(1);
        }

        // Traverse to the rightmost node
        Node<T>* ptrCurrent = ptrNode;
        while (ptrCurrent->ptrRight != nullptr) {
            ptrCurrent = ptrCurrent->ptrRight;
        }
        return ptrCurrent->payload;
    }
    
    template<typename T>
    T minNode(Node<T>* ptrNode) {
        if (ptrNode == nullptr) {
            cerr << "Error in minNode: the tree is empty" << endl;
            exit(1);
        }

        // Traverse to the leftmost node
        Node<T>* ptrCurrent = ptrNode;
        while (ptrCurrent->ptrLeft != nullptr) {
            ptrCurrent = ptrCurrent->ptrLeft;
        }
        return ptrCurrent->payload;
    }
    
    template<typename T>
    int treeHeight(Node<T>* ptrNode) {
        if (ptrNode == nullptr) {
            return -1;
        }

        int iLeftHeight = treeHeight(ptrNode->ptrLeft);
        int iRightHeight = treeHeight(ptrNode->ptrRight);

        // Return the maximum height between left and right subtrees
        return 1 + max(iLeftHeight, iRightHeight);
    }

    template<typename T>
    Node<T>* changeColor(Node<T>* ptrNode) {
        if(ptrNode == nullptr) {
            cerr << "Error in changeColor: memory allocation failed" << endl;
            exit(1);
        }

        // Toggle the color of the node
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