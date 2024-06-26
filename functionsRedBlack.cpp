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
        ptrNode->ptrParent = nullptr;
        ptrNode->ptrLeft = nullptr;
        ptrNode->ptrRight = nullptr;
        ptrNode->color = RED;
        ptrNode->payload = value;

        return ptrNode;
    }

    template<typename T>
    Node<T>* insertNode(Node<T>* ptrNode, T value) {
        Node<T>* ptrNewNode = createNode(value);

        Node<T>* ptrTemp = ptrNode;

        if(ptrNode == nullptr) {
            // If the tree is empty, insert the new node as the root
            ptrNewNode->color = BLACK;
            return ptrNewNode;
        }

        if(value < ptrNode->payload) {
            if(ptrNode->ptrLeft == nullptr) {
                ptrNode->ptrLeft = ptrNewNode;
                ptrNewNode->ptrParent = ptrNode;
            } 
            else
                insertNode(ptrNode->ptrLeft, value);
        }
        else {
            if(ptrNode->ptrRight == nullptr) {
                ptrNode->ptrRight = ptrNewNode;
                ptrNewNode->ptrParent = ptrNode;
            }
            else
                insertNode(ptrNode->ptrRight, value);
        }

        // Fixing the Tree to be RedBlack
        return fixRedBlack(ptrTemp, ptrNewNode);
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
            cout << ptrNode->payload;
            if(ptrNode->color == RED)
                cout << "-R ";
            else if(ptrNode->color == BLACK)
                cout << "-B ";
            traverseInOrder(ptrNode->ptrRight);
        }
    }
/*
    template<typename T>
    void traverseInOrder(Node<T>* ptrNode) {
        if(ptrNode != nullptr) {
            traverseInOrder(ptrNode->ptrLeft);
            cout << ptrNode->payload << " ";
             if(ptrNode->ptrParent != nullptr)
             cout << " ptrNode->ptrRight>payload = "<< ptrNode->ptrParent->payload;
            
            traverseInOrder(ptrNode->ptrRight);
        }
    }*/


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
    Node<T>* colorFlip(Node<T>* ptrNode) {
        if(ptrNode == nullptr) {
            cerr << "Error in colorFlip: null node" << endl;
            exit(1);
        }

        ptrNode = changeColor(ptrNode);
        if(ptrNode->ptrLeft != nullptr)
            ptrNode->ptrLeft = changeColor(ptrNode->ptrLeft);
        if(ptrNode->ptrRight != nullptr)
            ptrNode->ptrRight = changeColor(ptrNode->ptrRight);

        return ptrNode;
    }

    template<typename T>
    void leftRotation(Node<T>*& ptrNode) {
        Node<T>* ptrTemp = ptrNode->ptrRight;
        ptrNode->ptrRight = ptrTemp->ptrLeft;

        if (ptrTemp->ptrLeft != nullptr)
            ptrTemp->ptrLeft->ptrParent = ptrNode;

        ptrTemp->ptrParent = ptrNode->ptrParent;

        if (ptrNode->ptrParent == nullptr)
            ptrNode = ptrTemp;
        else if (ptrNode == ptrNode->ptrParent->ptrLeft)
            ptrNode->ptrParent->ptrLeft = ptrTemp;
        else
            ptrNode->ptrParent->ptrRight = ptrTemp;

        ptrTemp->ptrLeft = ptrNode;
        ptrNode->ptrParent = ptrTemp;

        ptrTemp = changeColor(ptrTemp);
        ptrTemp->ptrLeft = changeColor(ptrTemp->ptrLeft);
    }

    template<typename T>
    void rightRotation(Node<T>*& ptrNode) {
        Node<T>* ptrTemp = ptrNode->ptrLeft;
        ptrNode->ptrLeft = ptrTemp->ptrRight;

        if (ptrTemp->ptrRight != nullptr)
            ptrTemp->ptrRight->ptrParent = ptrNode;

        ptrTemp->ptrParent = ptrNode->ptrParent;

        if (ptrNode->ptrParent == nullptr)
            ptrNode = ptrTemp;
        else if (ptrNode == ptrNode->ptrParent->ptrRight)
            ptrNode->ptrParent->ptrRight = ptrTemp;
        else
            ptrNode->ptrParent->ptrLeft = ptrTemp;

        ptrTemp->ptrRight = ptrNode;
        ptrNode->ptrParent = ptrTemp;

        ptrTemp = changeColor(ptrTemp);
        ptrTemp->ptrRight = changeColor(ptrTemp->ptrRight);
    }

    template<typename T>
    Node<T>* fixRedBlack(Node<T>* ptrNode, Node<T>* ptrInsert) {
        while(ptrInsert != ptrNode && ptrInsert->ptrParent->color == RED) {
            if(ptrInsert->ptrParent == ptrInsert->ptrParent->ptrParent->ptrLeft) {
                Node<T>* ptrUncle1 = ptrInsert->ptrParent->ptrParent->ptrRight;


                cout << ptrNode->payload << endl;
                if(ptrUncle1 != nullptr && ptrUncle1->color == RED) {
                    ptrInsert->ptrParent->color = BLACK;
                    ptrUncle1->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    ptrInsert = ptrInsert->ptrParent->ptrParent;


                    cout << ptrInsert->payload << endl;
                    cout << ptrNode->payload << endl;
                }
                else {
                    if(ptrInsert == ptrInsert->ptrParent->ptrRight) {
                        ptrInsert = ptrInsert->ptrParent;
                        leftRotation(ptrInsert);
                    }
                    ptrInsert->ptrParent->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    rightRotation(ptrInsert->ptrParent->ptrParent);
                }
            }
            else {
                Node<T>* ptrUncle2 = ptrInsert->ptrParent->ptrParent->ptrLeft;
                if(ptrUncle2 != nullptr && ptrUncle2->color == RED) {
                    ptrInsert->ptrParent->color = BLACK;
                    ptrUncle2->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    ptrInsert = ptrInsert->ptrParent->ptrParent;
                }
                else {
                    if(ptrInsert == ptrInsert->ptrParent->ptrLeft) {
                        ptrInsert = ptrInsert->ptrParent;
                        rightRotation(ptrInsert);
                    }
                    ptrInsert->ptrParent->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    leftRotation(ptrInsert->ptrParent->ptrParent);
                }
            }
        }
        ptrNode->color = BLACK;
        return ptrNode;
    }


}