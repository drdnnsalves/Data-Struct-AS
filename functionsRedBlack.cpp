#include "functionsRedBlack.h"
#include <cstdlib>

using namespace std;

#define ANSI_RED "\033[31m"
#define ANSI_BLACK "\033[90m"
#define ANSI_RESET "\033[0m"

namespace RedBlackFunctions {

    template<typename T>
    Node<T>* createNode(T value) {
        Node<T>* ptrNode = (Node<T>*) malloc(sizeof(Node<T>));

        if(ptrNode == nullptr) {
            cerr << "Error in createNode: memory allocation failed" << endl;
            exit(1);
        }

        // Initialize the new node
        ptrNode->ptrParent = nullptr;
        ptrNode->ptrLeft = nullptr;
        ptrNode->ptrRight = nullptr;
        ptrNode->color = RED;
        ptrNode->payload = value;

        return ptrNode;
    }

    template<typename T>
    void insertNode(Node<T>*& ptrNode, T value) {
        Node<T>* x = ptrNode;
        Node<T>* ptrNewNode = createNode(value);

        Node<T>* y = nullptr;

        while(x != nullptr) {
            y = x;
            
            if(ptrNewNode->payload < x->payload) {
                x = x->ptrLeft;
            }
            else {
                x = x->ptrRight;
            }
        
        }

        ptrNewNode->ptrParent = y;
        if(y == nullptr) {
            ptrNode = ptrNewNode;
        }
        else if(ptrNewNode->payload < y->payload) {
            y->ptrLeft = ptrNewNode;
        }
        else {
            y->ptrRight = ptrNewNode;
        }

        fixRedBlack(ptrNode, ptrNewNode);
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
        if(ptrNode != nullptr) {
            traverseInOrder(ptrNode->ptrLeft);

            // Escolhe a cor baseada na cor do nó
            if(ptrNode->color == RED)
                cout << ANSI_RED << ptrNode->payload << "-R " << ANSI_RESET;
            else if(ptrNode->color == BLACK)
                cout << ANSI_BLACK << ptrNode->payload << "-B " << ANSI_RESET;

            traverseInOrder(ptrNode->ptrRight);
        }
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
        if (ptrNode == nullptr) {
            cerr << "Error in changeColor: null node" << endl;
            exit(1);
        }

        // Toggle the color of the node
        if (ptrNode->color == RED)
            ptrNode->color = BLACK;
        else
            ptrNode->color = RED;

        return ptrNode;
    }

    template<typename T>
    void leftRotation(Node<T>*& ptrRoot, Node<T>*& ptrNode) {
        Node<T>* ptrTemp = ptrNode->ptrRight;
        ptrNode->ptrRight = ptrTemp->ptrLeft;

        if (ptrTemp->ptrLeft != nullptr)
            ptrTemp->ptrLeft->ptrParent = ptrNode;

        if (ptrNode->ptrParent == nullptr)
            ptrRoot = ptrTemp;
        else if (ptrNode == ptrNode->ptrParent->ptrLeft)
            ptrNode->ptrParent->ptrLeft = ptrTemp;
        else
            ptrNode->ptrParent->ptrRight = ptrTemp;

        ptrTemp->ptrLeft = ptrNode;
        ptrNode->ptrParent = ptrTemp;
    }

    template<typename T>
    void rightRotation(Node<T>*& ptrRoot, Node<T>*& ptrNode) {
        Node<T>* ptrTemp = ptrNode->ptrLeft;
        ptrNode->ptrLeft = ptrTemp->ptrRight;

        if (ptrTemp->ptrRight != nullptr)
            ptrTemp->ptrRight->ptrParent = ptrNode;

        if (ptrNode->ptrParent == nullptr)
            ptrRoot = ptrTemp;
        else if (ptrNode == ptrNode->ptrParent->ptrRight)
            ptrNode->ptrParent->ptrRight = ptrTemp;
        else
            ptrNode->ptrParent->ptrLeft = ptrTemp;

        ptrTemp->ptrRight = ptrNode;
        ptrNode->ptrParent = ptrTemp;
    }

    template<typename T>
    void fixRedBlack(Node<T>*& ptrRoot, Node<T>* ptrInsert) {
        while (ptrInsert != ptrRoot && ptrInsert->ptrParent->color == RED) {
            if (ptrInsert->ptrParent == ptrInsert->ptrParent->ptrParent->ptrLeft) {
                Node<T>* ptrUncle = ptrInsert->ptrParent->ptrParent->ptrRight;

                if (ptrUncle != nullptr && ptrUncle->color == RED) {
                    ptrInsert->ptrParent->color = BLACK;
                    ptrUncle->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    ptrInsert = ptrInsert->ptrParent->ptrParent;
                } else {
                    if (ptrInsert == ptrInsert->ptrParent->ptrRight) {
                        ptrInsert = ptrInsert->ptrParent;
                        leftRotation(ptrRoot, ptrInsert);
                        ptrRoot->ptrParent = nullptr;
                    }
                    ptrInsert->ptrParent->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    rightRotation(ptrRoot, ptrInsert->ptrParent->ptrParent);
                    ptrRoot->ptrParent = nullptr;
                }
            } else {
                Node<T>* ptrUncle = ptrInsert->ptrParent->ptrParent->ptrLeft;

                if (ptrUncle != nullptr && ptrUncle->color == RED) {
                    ptrInsert->ptrParent->color = BLACK;
                    ptrUncle->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    ptrInsert = ptrInsert->ptrParent->ptrParent;
                } else {
                    if (ptrInsert == ptrInsert->ptrParent->ptrLeft) {
                        ptrInsert = ptrInsert->ptrParent;
                        rightRotation(ptrRoot, ptrInsert);
                        ptrRoot->ptrParent = nullptr;
                    }
                    ptrInsert->ptrParent->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    leftRotation(ptrRoot, ptrInsert->ptrParent->ptrParent);
                    ptrRoot->ptrParent = nullptr;
                }
            }
        }
        ptrRoot->color = BLACK;
    }
}