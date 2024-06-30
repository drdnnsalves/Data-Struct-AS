#include "functionsRedBlack.h"
#include <iostream>
#include <cstdlib>

using namespace std;

namespace RedBlackFunctions {

    template<typename T>
    Node<T>* createNode(T value) {
        Node<T>* ptrNode = new Node<T>;

        if(ptrNode == nullptr) {
            cerr << "Error in createNode: memory allocation failed" << endl;
            exit(1);
        }

        // Initialize the new node
        ptrNode->ptrParent = nullptr;
        ptrNode->ptrLeft = nullptr;
        ptrNode->ptrRight = nullptr;
        ptrNode->color = RED;           // New node is initially set as RED
        ptrNode->payload = value;

        return ptrNode;
    }

    template<typename T>
    void insertNode(Node<T>** ptrRoot, T value) {
        Node<T>* ptrTemp = *ptrRoot;
        Node<T>* ptrNewNode = createNode(value);

        Node<T>* ptrBefore = nullptr;

        // Traverse the tree to find the insertion point
        while(ptrTemp != nullptr) {
            ptrBefore = ptrTemp;
            
            if(ptrNewNode->payload < ptrTemp->payload) {
                ptrTemp = ptrTemp->ptrLeft;
            }
            else {
                ptrTemp = ptrTemp->ptrRight;
            }
        }

        ptrNewNode->ptrParent = ptrBefore;
        if(ptrBefore == nullptr) {
            *ptrRoot = ptrNewNode;
        }
        else if(ptrNewNode->payload < ptrBefore->payload) {
            ptrBefore->ptrLeft = ptrNewNode;
        }
        else {
            ptrBefore->ptrRight = ptrNewNode;
        }

        // Fix any Red-Black Tree violations
        fixRedBlack(ptrRoot, ptrNewNode);
    }

    template<typename T>
    void fixRedBlack(Node<T>** ptrRoot, Node<T>* ptrInsert) {
        while (ptrInsert != *ptrRoot && ptrInsert->ptrParent->color == RED) {
            if (ptrInsert->ptrParent == ptrInsert->ptrParent->ptrParent->ptrLeft) {
                Node<T>* ptrUncle = ptrInsert->ptrParent->ptrParent->ptrRight;

                // Case A1: Uncle is RED
                if (ptrUncle != nullptr && ptrUncle->color == RED) {
                    ptrInsert->ptrParent->color = BLACK;
                    ptrUncle->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    ptrInsert = ptrInsert->ptrParent->ptrParent;
                }
                else {
                    // Case A2: Uncle is BLACK and current node is a right child
                    if (ptrInsert == ptrInsert->ptrParent->ptrRight) {
                        ptrInsert = ptrInsert->ptrParent;
                        leftRotation(ptrRoot, ptrInsert);
                    }

                    // Case A3: Uncle is BLACK and current node is a left child
                    ptrInsert->ptrParent->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    rightRotation(ptrRoot, ptrInsert->ptrParent->ptrParent);
                }
            } 
            else {
                // Symmetric cases for right side of the tree
                Node<T>* ptrUncle = ptrInsert->ptrParent->ptrParent->ptrLeft;

                if (ptrUncle != nullptr && ptrUncle->color == RED) {
                    ptrInsert->ptrParent->color = BLACK;
                    ptrUncle->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    ptrInsert = ptrInsert->ptrParent->ptrParent;
                } 
                else {
                    if (ptrInsert == ptrInsert->ptrParent->ptrLeft) {
                        ptrInsert = ptrInsert->ptrParent;
                        rightRotation(ptrRoot, ptrInsert);
                    }
                    ptrInsert->ptrParent->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    leftRotation(ptrRoot, ptrInsert->ptrParent->ptrParent);
                }
            }
        }
        // Ensure the root is always black after fixing violations
        (*ptrRoot)->color = BLACK;
    }

    template<typename T>
    void leftRotation(Node<T>** ptrRoot, Node<T>* ptrNode) {
        Node<T>* ptrTemp = ptrNode->ptrRight;
        ptrNode->ptrRight = ptrTemp->ptrLeft;

        if (ptrTemp->ptrLeft != nullptr)
            ptrTemp->ptrLeft->ptrParent = ptrNode;

        ptrTemp->ptrParent = ptrNode->ptrParent;

        if (ptrNode->ptrParent == nullptr)               // Case 1: ptrNode is the Root
            *ptrRoot = ptrTemp;
        else if (ptrNode == ptrNode->ptrParent->ptrLeft) // Case 2: ptrNode is the left child of its parent
            ptrNode->ptrParent->ptrLeft = ptrTemp;
        else                                             // Case 3: ptrNode is the right child of its parent
            ptrNode->ptrParent->ptrRight = ptrTemp;

        ptrTemp->ptrLeft = ptrNode;
        ptrNode->ptrParent = ptrTemp;
    }

    template<typename T>
    void rightRotation(Node<T>** ptrRoot, Node<T>* ptrNode) {
        Node<T>* ptrTemp = ptrNode->ptrLeft;
        ptrNode->ptrLeft = ptrTemp->ptrRight;

        if (ptrTemp->ptrRight != nullptr)
            ptrTemp->ptrRight->ptrParent = ptrNode;

        ptrTemp->ptrParent = ptrNode->ptrParent;

        if (ptrNode->ptrParent == nullptr)                // Case 1: ptrNode is the Root
            *ptrRoot = ptrTemp;
        else if (ptrNode == ptrNode->ptrParent->ptrRight) // Case 2: ptrNode is the left child of its parent
            ptrNode->ptrParent->ptrRight = ptrTemp;
        else                                              // Case 3: ptrNode is the right child of its parent
            ptrNode->ptrParent->ptrLeft = ptrTemp;

        ptrTemp->ptrRight = ptrNode;
        ptrNode->ptrParent = ptrTemp;
    }

    template<typename T>
    void traverseInOrder(Node<T>* ptrRoot) {
        if(ptrRoot != nullptr) {
            traverseInOrder(ptrRoot->ptrLeft);

            // Choose the color based on the node's color
            if(ptrRoot->color == RED)
                cout << "\033[31m" << ptrRoot->payload << "-R \033[0m";
            else if(ptrRoot->color == BLACK)
                cout << "\033[90m" << ptrRoot->payload << "-B \033[0m";

            traverseInOrder(ptrRoot->ptrRight);
        }
    }

    template<typename T>
    void printBT(const std::string& prefix, const Node<T>* node, bool isLeft) {
        if(node != nullptr) {
            std::cout << prefix;

            std::cout << (isLeft ? "+---" : "+---" );

            // Choose the color based on the node's color
            if(node->color == RED)
                std::cout << "\033[31m" << node->payload << "" << "\033[0m" << std::endl;
            else if(node->color == BLACK)
                std::cout << "\033[90m" << node->payload << "" << "\033[0m" << std::endl;

            // Go to the next level of the tree - left and right branch
            printBT(prefix + (isLeft ? "|   " : "    "), node->ptrLeft, true);
            printBT(prefix + (isLeft ? "|   " : "    "), node->ptrRight, false);
        }
    }

    template<typename T>
    void printBT(const Node<T>* node) {
        printBT("", node, false);    
    }

    template<typename T>
    Node<T>* maxNode(Node<T>* ptrRoot) {
        if(ptrRoot == nullptr) {
            cerr << "Error in maxNode: the tree is empty" << endl;
            exit(1);
        }

        // Traverse to the rightmost node
        Node<T>* ptrCurrent = ptrRoot;
        while(ptrCurrent->ptrRight != nullptr)
            ptrCurrent = ptrCurrent->ptrRight;

        return ptrCurrent;
    }
    
    template<typename T>
    Node<T>* minNode(Node<T>* ptrRoot) {
        if(ptrRoot == nullptr) {
            cerr << "Error in minNode: the tree is empty" << endl;
            exit(1);
        }

        // Traverse to the leftmost node
        Node<T>* ptrCurrent = ptrRoot;
        while (ptrCurrent->ptrLeft != nullptr)
            ptrCurrent = ptrCurrent->ptrLeft;

        return ptrCurrent;
    }

    template<typename T>
    int treeHeight(Node<T>* ptrRoot) {
        if(ptrRoot == nullptr) {
            return -1;
        }

        int leftHeight = treeHeight(ptrRoot->ptrLeft);
        int rightHeight = treeHeight(ptrRoot->ptrRight);

        // Return the maximum height between left and right subtrees
        return 1 + max(leftHeight, rightHeight);
    }
    
    template<typename T>
    int treeHeightOptimized(Node<T>* ptrRoot) {
        if (ptrRoot == nullptr) {
            return -1;
        }

        // Consider just the red path
        if (ptrRoot->ptrLeft != nullptr && ptrRoot->ptrLeft->color == RED) {
            return 1 + treeHeight(ptrRoot->ptrLeft);
        } else if (ptrRoot->ptrRight != nullptr && ptrRoot->ptrRight->color == RED) {
            return 1 + treeHeight(ptrRoot->ptrRight);
        } else {
            int leftHeight = treeHeight(ptrRoot->ptrLeft);
            int rightHeight = treeHeight(ptrRoot->ptrRight);
            
            // Return the maximum height between left and right subtrees
            return 1 + std::max(leftHeight, rightHeight);
        }
    }

    template<typename T>
    void removeNode(Node<T>** ptrRoot, T value) {
        if(*ptrRoot == nullptr) 
            return;
        
        if(value < (*ptrRoot)->payload)
            removeNode(&(*ptrRoot)->ptrLeft, value);
        else if(value > (*ptrRoot)->payload)
            removeNode(&(*ptrRoot)->ptrRight, value); 
        else {
            Node<T>* ptrTemp = nullptr;
            
            if((*ptrRoot)->ptrLeft == nullptr) {
                ptrTemp = (*ptrRoot)->ptrRight;
                free(*ptrRoot);
                *ptrRoot = ptrTemp;
            } 
            else if((*ptrRoot)->ptrRight == nullptr) {
                ptrTemp = (*ptrRoot)->ptrLeft;
                free(*ptrRoot);
                *ptrRoot = ptrTemp;            
            } 
            else{
                ptrTemp = minNode((*ptrRoot)->ptrRight);
                (*ptrRoot)->payload = ptrTemp->payload;
                removeNode(&(*ptrRoot)->ptrRight, ptrTemp->payload);
            }
        }
    }

    template<typename T>
    Node<T>* searchNode(Node<T>* ptrRoot, T value) {
        if(ptrRoot == nullptr) return nullptr;
        else if(value == ptrRoot->payload) return ptrRoot;
        else if(value < ptrRoot->payload) return searchNode(ptrRoot->ptrLeft, value);
        else return searchNode(ptrRoot->ptrRight, value);
    }

    template<typename T>
    bool verifyRedBlack(Node<T>* ptrNode) {
        if(ptrNode == nullptr) return true;  // An empty tree is a valid Red-Black tree

        // Root is black
        if(ptrNode->color != BLACK) {
            cerr << "Error: The root is not black" << endl;
            return false;
        }

        // Red nodes have black children
        if(!verifyRedProperty(ptrNode)) {
            cerr << "Error: The property of red nodes is violated" << endl;
            return false;
        }

        // All paths from any node to its descendant leaves contain the same number of black nodes
        int blackNodeCount = 0;
        Node<T>* temp = ptrNode;
        while(temp != nullptr) {
            if (temp->color == BLACK) blackNodeCount++;
            temp = temp->ptrLeft;
        }

        if(!verifyBlackProperty(ptrNode, blackNodeCount, 0)) {
            cerr << "Error: Paths from nodes to NIL do not have the same number of black nodes" << endl;
            return false;
        }

        return true;
    }

    template<typename T>
    bool verifyRedProperty(Node<T>* ptrNode) {
        if(ptrNode == nullptr) return true;

        // Checks if a red node has black children
        if(ptrNode->color == RED) {
            if ((ptrNode->ptrLeft != nullptr && ptrNode->ptrLeft->color == RED) ||
                (ptrNode->ptrRight != nullptr && ptrNode->ptrRight->color == RED)) {
                return false;
            }
        }

        // Recursively check properties for left and right subtrees
        return verifyRedProperty(ptrNode->ptrLeft) && verifyRedProperty(ptrNode->ptrRight);
    }

    template<typename T>
    bool verifyBlackProperty(Node<T>* ptrNode, int blackNodeCount, int currentCount) {
        if(ptrNode == nullptr) {
            return currentCount == blackNodeCount;
        }

        // Increment the current black node count if the current node is black.
        if(ptrNode->color == BLACK) {
            currentCount++;
        }

        // Recursively verify the black height property for both the left and right subtrees.
        return verifyBlackProperty(ptrNode->ptrLeft, blackNodeCount, currentCount) &&
            verifyBlackProperty(ptrNode->ptrRight, blackNodeCount, currentCount);
    }
}

