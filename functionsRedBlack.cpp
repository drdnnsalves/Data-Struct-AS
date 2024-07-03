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
        if(ptrBefore == nullptr) {  // Insert as the root if tree is empty
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
            if(ptrInsert->ptrParent == ptrInsert->ptrParent->ptrParent->ptrLeft) {
                Node<T>* ptrUncle = ptrInsert->ptrParent->ptrParent->ptrRight;

                // Case A1: Uncle is RED
                if(ptrUncle != nullptr && ptrUncle->color == RED) {
                    ptrInsert->ptrParent->color = BLACK;
                    ptrUncle->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    ptrInsert = ptrInsert->ptrParent->ptrParent;
                }
                else {
                    // Case A2: Uncle is BLACK and current node is a right ptrChild
                    if (ptrInsert == ptrInsert->ptrParent->ptrRight) {
                        ptrInsert = ptrInsert->ptrParent;
                        leftRotation(ptrRoot, ptrInsert);
                    }

                    // Case A3: Uncle is BLACK and current node is a left ptrChild
                    ptrInsert->ptrParent->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    rightRotation(ptrRoot, ptrInsert->ptrParent->ptrParent);
                }
            } 
            else {
                // Symmetric cases for right side of the tree
                Node<T>* ptrUncle = ptrInsert->ptrParent->ptrParent->ptrLeft;

                if(ptrUncle != nullptr && ptrUncle->color == RED) {
                    ptrInsert->ptrParent->color = BLACK;
                    ptrUncle->color = BLACK;
                    ptrInsert->ptrParent->ptrParent->color = RED;
                    ptrInsert = ptrInsert->ptrParent->ptrParent;
                } 
                else {
                    if(ptrInsert == ptrInsert->ptrParent->ptrLeft) {
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

        if(ptrTemp->ptrLeft != nullptr)
            ptrTemp->ptrLeft->ptrParent = ptrNode;

        ptrTemp->ptrParent = ptrNode->ptrParent;

        if(ptrNode->ptrParent == nullptr)               // Case 1: ptrNode is the Root
            *ptrRoot = ptrTemp;
        else if (ptrNode == ptrNode->ptrParent->ptrLeft) // Case 2: ptrNode is the left ptrChild of its parent
            ptrNode->ptrParent->ptrLeft = ptrTemp;
        else                                             // Case 3: ptrNode is the right ptrChild of its parent
            ptrNode->ptrParent->ptrRight = ptrTemp;

        ptrTemp->ptrLeft = ptrNode;
        ptrNode->ptrParent = ptrTemp;
    }

    template<typename T>
    void rightRotation(Node<T>** ptrRoot, Node<T>* ptrNode) {
        Node<T>* ptrTemp = ptrNode->ptrLeft;
        ptrNode->ptrLeft = ptrTemp->ptrRight;

        if(ptrTemp->ptrRight != nullptr)
            ptrTemp->ptrRight->ptrParent = ptrNode;

        ptrTemp->ptrParent = ptrNode->ptrParent;

        if(ptrNode->ptrParent == nullptr)                // Case 1: ptrNode is the Root
            *ptrRoot = ptrTemp;
        else if(ptrNode == ptrNode->ptrParent->ptrRight) // Case 2: ptrNode is the left ptrChild of its parent
            ptrNode->ptrParent->ptrRight = ptrTemp;
        else                                              // Case 3: ptrNode is the right ptrChild of its parent
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
        if(ptrRoot == nullptr) {
            return -1;
        }

        // Consider just the red path
        if(ptrRoot->ptrLeft != nullptr && ptrRoot->ptrLeft->color == RED && ptrRoot->ptrRight != nullptr && ptrRoot->ptrRight->color == BLACK) {
            return 1 + treeHeightOptimized(ptrRoot->ptrLeft);
        } else if (ptrRoot->ptrRight != nullptr && ptrRoot->ptrRight->color == RED && ptrRoot->ptrLeft != nullptr && ptrRoot->ptrLeft->color == BLACK) {
            return 1 + treeHeightOptimized(ptrRoot->ptrRight);
        } else {
            int leftHeight = treeHeightOptimized(ptrRoot->ptrLeft);
            int rightHeight = treeHeightOptimized(ptrRoot->ptrRight);

            // Return the maximum height between left and right subtrees
            return 1 + max(leftHeight, rightHeight);
        }
    }

    template<typename T>
    void removeNode(Node<T>** ptrRoot, T value) {
        Node<T>* ptrNodeToDelete = searchNode(*ptrRoot, value); // Find the node to delete
        if(ptrNodeToDelete == nullptr) return;

        Node<T>* ptrSuccessor = ptrNodeToDelete;
        Node<T>* ptrChild;
        bool bOriginalColorBlack = (ptrSuccessor->color == BLACK); // Save the original color of the node to be deleted

        if(ptrNodeToDelete->ptrLeft == nullptr) {
            ptrChild = ptrNodeToDelete->ptrRight;
            transplant(ptrRoot, ptrNodeToDelete, ptrNodeToDelete->ptrRight); // Replace ptrNodeToDelete with its right ptrChild
        } 
        else if(ptrNodeToDelete->ptrRight == nullptr) {
            ptrChild = ptrNodeToDelete->ptrLeft;
            transplant(ptrRoot, ptrNodeToDelete, ptrNodeToDelete->ptrLeft); // Replace ptrNodeToDelete with its left ptrChild
        }
        else {
            ptrSuccessor = minNode(ptrNodeToDelete->ptrRight); // Find the minimum node in the right subtree
            bOriginalColorBlack = ptrSuccessor->color == BLACK; // Save the original color of the ptrSuccessor
            ptrChild = ptrSuccessor->ptrRight;

            if (ptrSuccessor->ptrParent == ptrNodeToDelete) {
                if (ptrChild != nullptr) ptrChild->ptrParent = ptrSuccessor; // Update ptrChild's parent to ptrSuccessor if ptrSuccessor is the direct ptrChild of ptrNodeToDelete
            } 
            else {
                transplant(ptrRoot, ptrSuccessor, ptrSuccessor->ptrRight); // Replace ptrSuccessor with its right ptrChild
                ptrSuccessor->ptrRight = ptrNodeToDelete->ptrRight;
                ptrSuccessor->ptrRight->ptrParent = ptrSuccessor;
            }

            transplant(ptrRoot, ptrNodeToDelete, ptrSuccessor); // Replace ptrNodeToDelete with ptrSuccessor
            ptrSuccessor->ptrLeft = ptrNodeToDelete->ptrLeft;
            ptrSuccessor->ptrLeft->ptrParent = ptrSuccessor;
            ptrSuccessor->color = ptrNodeToDelete->color; // Copy the color of ptrNodeToDelete to ptrSuccessor
        }

        free(ptrNodeToDelete);

        if(bOriginalColorBlack) {
            fixRemoveRedBlack(ptrRoot, ptrChild); // Fix any violations of the Red-Black properties
        }
    }

    template<typename T>
    void clearTree(Node<T>** ptrRoot) {
        if(*ptrRoot == nullptr) return;

        // Post-order traversal to delete all nodes
        clearTree(&((*ptrRoot)->ptrLeft));
        clearTree(&((*ptrRoot)->ptrRight));

        free(*ptrRoot);
        *ptrRoot = nullptr;
    }

    template<typename T>
    Node<T>* searchNode(Node<T>* ptrRoot, T value) {
        if(ptrRoot == nullptr) {
            cout << "Error: Node with value " << value << " not found." << endl;
            return nullptr;
        } 
        else if(value == ptrRoot->payload)
            return ptrRoot;
        else if(value < ptrRoot->payload)
            return searchNode(ptrRoot->ptrLeft, value);
        else
            return searchNode(ptrRoot->ptrRight, value);
    }

    template<typename T>
    bool verifyRedBlack(Node<T>* ptrRoot) {
        if(ptrRoot == nullptr) return true;  // An empty tree is a valid Red-Black tree

        // Root is black
        if(ptrRoot->color != BLACK) {
            cerr << "Error: The root is not black" << endl;
            return false;
        }

        // Red nodes have black ptrChildren
        if(!verifyRedProperty(ptrRoot)) {
            cerr << "Error: The property of red nodes is violated" << endl;
            return false;
        }

        // All paths from any node to its descendant leaves contain the same number of black nodes
        int blackNodeCount = 0;
        Node<T>* temp = ptrRoot;
        while(temp != nullptr) {
            if(temp->color == BLACK) blackNodeCount++;
            temp = temp->ptrLeft;
        }

        if(!verifyBlackProperty(ptrRoot, blackNodeCount, 0)) {
            cerr << "Error: Paths from nodes to NIL do not have the same number of black nodes" << endl;
            return false;
        }

        return true;
    }

    template<typename T>
    bool verifyRedProperty(Node<T>* ptrNode) {
        if(ptrNode == nullptr) return true;

        // Checks if a red node has black ptrChildren
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
        if(ptrNode == nullptr)
            return currentCount == blackNodeCount;

        // Increment the current black node count if the current node is black.
        if(ptrNode->color == BLACK)
            currentCount++;

        // Recursively verify the black height property for both the left and right subtrees.
        return verifyBlackProperty(ptrNode->ptrLeft, blackNodeCount, currentCount) &&
            verifyBlackProperty(ptrNode->ptrRight, blackNodeCount, currentCount);
    }

    template<typename T>
    void fixRemoveRedBlack(Node<T>** ptrRoot, Node<T>* node) {
        while (node != *ptrRoot && (node == nullptr || node->color == BLACK)) {

            if (node == nullptr) return;

            if (node == node->ptrParent->ptrLeft) {
                Node<T>* sibling = node->ptrParent->ptrRight;

                if (sibling != nullptr) {  // Ensure sibling is not null before accessing its color
                    // Case 1: Sibling is red
                    if (sibling->color == RED) {
                        sibling->color = BLACK;
                        node->ptrParent->color = RED;
                        leftRotation(ptrRoot, node->ptrParent);
                        sibling = node->ptrParent->ptrRight;
                    }

                    // Case 2: Sibling's ptrChildren are both black
                    if ((sibling->ptrLeft == nullptr || sibling->ptrLeft->color == BLACK) &&
                        (sibling->ptrRight == nullptr || sibling->ptrRight->color == BLACK)) {
                        sibling->color = RED;
                        node = node->ptrParent;
                    } else {
                        // Case 3: Sibling's right ptrChild is black
                        if (sibling->ptrRight == nullptr || sibling->ptrRight->color == BLACK) {
                            if (sibling->ptrLeft != nullptr) sibling->ptrLeft->color = BLACK;
                            sibling->color = RED;
                            rightRotation(ptrRoot, sibling);
                            sibling = node->ptrParent->ptrRight;
                        }

                        // Case 4: Sibling's right ptrChild is red
                        sibling->color = node->ptrParent->color;
                        node->ptrParent->color = BLACK;
                        if (sibling->ptrRight != nullptr) sibling->ptrRight->color = BLACK;
                        leftRotation(ptrRoot, node->ptrParent);
                        node = *ptrRoot;
                    }
                }
            } else {
                Node<T>* sibling = node->ptrParent->ptrLeft;

                if (sibling != nullptr) {  // Ensure sibling is not null before accessing its color
                    // Case 1: Sibling is red
                    if (sibling->color == RED) {
                        sibling->color = BLACK;
                        node->ptrParent->color = RED;
                        rightRotation(ptrRoot, node->ptrParent);
                        sibling = node->ptrParent->ptrLeft;
                    }

                    // Case 2: Sibling's ptrChildren are both black
                    if ((sibling->ptrRight == nullptr || sibling->ptrRight->color == BLACK) &&
                        (sibling->ptrLeft == nullptr || sibling->ptrLeft->color == BLACK)) {
                        sibling->color = RED;
                        node = node->ptrParent;
                    } else {
                        // Case 3: Sibling's left ptrChild is black
                        if (sibling->ptrLeft == nullptr || sibling->ptrLeft->color == BLACK) {
                            if (sibling->ptrRight != nullptr) sibling->ptrRight->color = BLACK;
                            sibling->color = RED;
                            leftRotation(ptrRoot, sibling);
                            sibling = node->ptrParent->ptrLeft;
                        }

                        // Case 4: Sibling's left ptrChild is red
                        sibling->color = node->ptrParent->color;
                        node->ptrParent->color = BLACK;
                        if (sibling->ptrLeft != nullptr) sibling->ptrLeft->color = BLACK;
                        rightRotation(ptrRoot, node->ptrParent);
                        node = *ptrRoot;
                    }
                }
            }
        }
        if (node != nullptr) node->color = BLACK;
    }


    template<typename T>
    void transplant(Node<T>** ptrRoot, Node<T>* target, Node<T>* replacement) {
        // If target is the root of the tree, set the root to replacement
        if(target->ptrParent == nullptr) {
            *ptrRoot = replacement;
        }
        // If target is the left ptrChild, replace it with replacement as the left ptrChild
        else if(target == target->ptrParent->ptrLeft) {
            target->ptrParent->ptrLeft = replacement;
        }
        // If target is the right ptrChild, replace it with replacement as the right ptrChild
        else {
            target->ptrParent->ptrRight = replacement;
        }
        // Set replacement's parent to target's parent, if replacement is not nullptr
        if(replacement != nullptr)
            replacement->ptrParent = target->ptrParent;
    }

// Explicit instantiations for char
template Node<char>* createNode(char value);
template void insertNode(Node<char>** ptrRoot, char value);
template void fixInsertRedBlack(Node<char>** ptrRoot, Node<char>* ptrInsert);
template void leftRotation(Node<char>** ptrRoot, Node<char>* ptrNode);
template void rightRotation(Node<char>** ptrRoot, Node<char>* ptrNode);
template void traverseInOrder(Node<char>* ptrRoot);
template void printBT(const Node<char>* node);
template Node<char>* maxNode(Node<char>* ptrRoot);
template Node<char>* minNode(Node<char>* ptrRoot);
template int treeHeight(Node<char>* ptrRoot);
template int treeHeightOptimized(Node<char>* ptrRoot);
template void removeNode(Node<char>** ptrRoot, char value);
template void clearTree(Node<char>** ptrRoot);
template Node<char>* searchNode(Node<char>* ptrRoot, char value);
template bool verifyRedBlack(Node<char>* ptrRoot);
template bool verifyRedProperty(Node<char>* ptrNode);
template bool verifyBlackProperty(Node<char>* ptrNode, int blackNodeCount, int currentCount);
template void fixRemoveRedBlack(Node<char>** ptrRoot, Node<char>* node);
template void transplant(Node<char>** ptrRoot, Node<char>* target, Node<char>* replacement);

// Explicit instantiations for float
template Node<float>* createNode(float value);
template void insertNode(Node<float>** ptrRoot, float value);
template void fixInsertRedBlack(Node<float>** ptrRoot, Node<float>* ptrInsert);
template void leftRotation(Node<float>** ptrRoot, Node<float>* ptrNode);
template void rightRotation(Node<float>** ptrRoot, Node<float>* ptrNode);
template void traverseInOrder(Node<float>* ptrRoot);
template void printBT(const Node<float>* node);
template Node<float>* maxNode(Node<float>* ptrRoot);
template Node<float>* minNode(Node<float>* ptrRoot);
template int treeHeight(Node<float>* ptrRoot);
template int treeHeightOptimized(Node<float>* ptrRoot);
template void removeNode(Node<float>** ptrRoot, float value);
template void clearTree(Node<float>** ptrRoot);
template Node<float>* searchNode(Node<float>* ptrRoot, float value);
template bool verifyRedBlack(Node<float>* ptrRoot);
template bool verifyRedProperty(Node<float>* ptrNode);
template bool verifyBlackProperty(Node<float>* ptrNode, int blackNodeCount, int currentCount);
template void fixRemoveRedBlack(Node<float>** ptrRoot, Node<float>* node);
template void transplant(Node<float>** ptrRoot, Node<float>* target, Node<float>* replacement);

// Explicit instantiations for int
template Node<int>* createNode(int value);
template void insertNode(Node<int>** ptrRoot, int value);
template void fixInsertRedBlack(Node<int>** ptrRoot, Node<int>* ptrInsert);
template void leftRotation(Node<int>** ptrRoot, Node<int>* ptrNode);
template void rightRotation(Node<int>** ptrRoot, Node<int>* ptrNode);
template void traverseInOrder(Node<int>* ptrRoot);
template void printBT(const Node<int>* node);
template Node<int>* maxNode(Node<int>* ptrRoot);
template Node<int>* minNode(Node<int>* ptrRoot);
template int treeHeight(Node<int>* ptrRoot);
template int treeHeightOptimized(Node<int>* ptrRoot);
template void removeNode(Node<int>** ptrRoot, int value);
template void clearTree(Node<int>** ptrRoot);
template Node<int>* searchNode(Node<int>* ptrRoot, int value);
template bool verifyRedBlack(Node<int>* ptrRoot);
template bool verifyRedProperty(Node<int>* ptrNode);
template bool verifyBlackProperty(Node<int>* ptrNode, int blackNodeCount, int currentCount);
template void fixRemoveRedBlack(Node<int>** ptrRoot, Node<int>* node);
template void transplant(Node<int>** ptrRoot, Node<int>* target, Node<int>* replacement);

}

