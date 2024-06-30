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
        fixInsertRedBlack(ptrRoot, ptrNewNode);
    }

    template<typename T>
    void fixInsertRedBlack(Node<T>** ptrRoot, Node<T>* ptrInsert) {
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
        Node<T>* nodeToDelete = searchNode(*ptrRoot, value); // Find the node to delete
        if (nodeToDelete == nullptr) return;

        Node<T>* y = nodeToDelete;
        Node<T>* x;
        bool originalColorBlack = y->color == BLACK; // Save the original color of the node to be deleted

        if (nodeToDelete->ptrLeft == nullptr) {
            x = nodeToDelete->ptrRight;
            transplant(ptrRoot, nodeToDelete, nodeToDelete->ptrRight); // Replace nodeToDelete with its right child
        } 
        else if (nodeToDelete->ptrRight == nullptr) {
            x = nodeToDelete->ptrLeft;
            transplant(ptrRoot, nodeToDelete, nodeToDelete->ptrLeft); // Replace nodeToDelete with its left child
        } 
        else {
            y = minNode(nodeToDelete->ptrRight); // Find the minimum node in the right subtree
            originalColorBlack = y->color == BLACK; // Save the original color of the successor
            x = y->ptrRight;

            if (y->ptrParent == nodeToDelete) {
                if (x != nullptr) x->ptrParent = y; // Update x's parent to y if y is the direct child of nodeToDelete
            } 
            else {
                transplant(ptrRoot, y, y->ptrRight); // Replace y with its right child
                y->ptrRight = nodeToDelete->ptrRight;
                y->ptrRight->ptrParent = y;
            }

            transplant(ptrRoot, nodeToDelete, y); // Replace nodeToDelete with y
            y->ptrLeft = nodeToDelete->ptrLeft;
            y->ptrLeft->ptrParent = y;
            y->color = nodeToDelete->color; // Copy the color of nodeToDelete to y
        }

        free(nodeToDelete);

        if (originalColorBlack) {
            fixRemoveRedBlack(ptrRoot, x); // Fix any violations of the Red-Black properties
        }
    }

    template<typename T>
    void clearTree(Node<T>** ptrRoot) {
        if (*ptrRoot == nullptr) {
            return;
        }

        // Post-order traversal to delete all nodes
        clearTree(&((*ptrRoot)->ptrLeft));
        clearTree(&((*ptrRoot)->ptrRight));

        free(*ptrRoot); // Free memory using free() (assuming nodes were allocated with malloc)
        *ptrRoot = nullptr;
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

    template<typename T>
    void fixRemoveRedBlack(Node<T>** ptrRoot, Node<T>* x) {
        while (x != *ptrRoot && (x == nullptr || x->color == BLACK)) {

            if (x == nullptr) return;
            
            if (x == x->ptrParent->ptrLeft) {
                
                Node<T>* w = x->ptrParent->ptrRight;

                if (w != nullptr) {  // Ensure w is not null before accessing its color
                    // Case 1: Sibling w is red
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->ptrParent->color = RED;
                        leftRotation(ptrRoot, x->ptrParent);
                        w = x->ptrParent->ptrRight;
                    }

                    // Case 2: Sibling w's children are both black
                    if ((w->ptrLeft == nullptr || w->ptrLeft->color == BLACK) &&
                        (w->ptrRight == nullptr || w->ptrRight->color == BLACK)) {
                        if (w != nullptr) w->color = RED;
                        x = x->ptrParent;
                    } else {
                        // Case 3: Sibling w's right child is black
                        if (w->ptrRight == nullptr || w->ptrRight->color == BLACK) {
                            if (w->ptrLeft != nullptr) w->ptrLeft->color = BLACK;
                            if (w != nullptr) w->color = RED;
                            rightRotation(ptrRoot, w);
                            w = x->ptrParent->ptrRight;
                        }

                        // Case 4: Sibling w's right child is red
                        if (w != nullptr) w->color = x->ptrParent->color;
                        if (x->ptrParent != nullptr) x->ptrParent->color = BLACK;
                        if (w != nullptr && w->ptrRight != nullptr) w->ptrRight->color = BLACK;
                        leftRotation(ptrRoot, x->ptrParent);
                        x = *ptrRoot;
                    }
                }
            } else {
                Node<T>* w = x->ptrParent->ptrLeft;

                if (w != nullptr) {  // Ensure w is not null before accessing its color
                    // Case 1: Sibling w is red
                    if (w->color == RED) {
                        w->color = BLACK;
                        x->ptrParent->color = RED;
                        rightRotation(ptrRoot, x->ptrParent);
                        w = x->ptrParent->ptrLeft;
                    }

                    // Case 2: Sibling w's children are both black
                    if ((w->ptrRight == nullptr || w->ptrRight->color == BLACK) &&
                        (w->ptrLeft == nullptr || w->ptrLeft->color == BLACK)) {
                        if (w != nullptr) w->color = RED;
                        x = x->ptrParent;
                    } else {
                        // Case 3: Sibling w's left child is black
                        if (w->ptrLeft == nullptr || w->ptrLeft->color == BLACK) {
                            if (w->ptrRight != nullptr) w->ptrRight->color = BLACK;
                            if (w != nullptr) w->color = RED;
                            leftRotation(ptrRoot, w);
                            w = x->ptrParent->ptrLeft;
                        }

                        // Case 4: Sibling w's left child is red
                        if (w != nullptr) w->color = x->ptrParent->color;
                        if (x->ptrParent != nullptr) x->ptrParent->color = BLACK;
                        if (w != nullptr && w->ptrLeft != nullptr) w->ptrLeft->color = BLACK;
                        rightRotation(ptrRoot, x->ptrParent);
                        x = *ptrRoot;
                    }
                }
            }
        }

        if (x != nullptr) x->color = BLACK;
    }

    template<typename T>
    void transplant(Node<T>** ptrRoot, Node<T>* u, Node<T>* v) {
        // If u is the root of the tree, set the root to v
        if (u->ptrParent == nullptr) {
            *ptrRoot = v;
        }
        // If u is the left child, replace it with v as the left child
        else if (u == u->ptrParent->ptrLeft) {
            u->ptrParent->ptrLeft = v;
        }
        // If u is the right child, replace it with v as the right child
        else {
            u->ptrParent->ptrRight = v;
        }
        // Set v's parent to u's parent, if v is not nullptr
        if (v != nullptr) {
            v->ptrParent = u->ptrParent;
        }
    }


}

