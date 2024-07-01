#pragma once

#include <iostream>
#include <string>

namespace RedBlackFunctions {

    enum Color {
        RED, 
        BLACK
    };

    template<typename T>
    struct Node {
        T payload;
        Node* ptrParent;
        Node* ptrLeft;
        Node* ptrRight;
        Color color;
    };


    template<typename T>
    Node<T>* createNode(T value);

    template<typename T>
    void insertNode(Node<T>** ptrRoot, T value);

    // Three auxiliary functions made for "insertNode" function
    template<typename T>
    void fixInsertRedBlack(Node<T>** ptrRoot, Node<T>* ptrInsert);

    template<typename T>
    void leftRotation(Node<T>** ptrRoot, Node<T>* ptrNode);

    template<typename T>
    void rightRotation(Node<T>** ptrRoot, Node<T>* ptrNode);


    template<typename T>
    void traverseInOrder(Node<T>* ptrRoot);

    // Functions made for printing the red-black tree with colors
    template<typename T>
    void printBT(const std::string& prefix, const Node<T>* ptrRoot, bool isLeft);

    template<typename T>
    void printBT(const Node<T>* ptrRoot);


    template<typename T>
    Node<T>* maxNode(Node<T>* ptrRoot);
    
    template<typename T>
    Node<T>* minNode(Node<T>* ptrRoot);
    
    template<typename T>
    int treeHeight(Node<T>* ptrRoot);

    template<typename T>
    int treeHeightOptimized(Node<T>* ptrRoot);

    template<typename T>
    void removeNode(Node<T>** ptrRoot, T value);

    template<typename T>
    void clearTree(Node<T>** ptrRoot);

    template<typename T>
    Node<T>* searchNode(Node<T>* ptrRoot, T value);

    template<typename T>
    bool verifyRedBlack(Node<T>* ptrNode);

    template<typename T>
    bool verifyRedProperty(Node<T>* ptrNode);

    template<typename T>
    bool verifyBlackProperty(Node<T>* ptrRoot, int blackNodeCount, int currentCount);


    // Three auxiliary functions made for "removeNode" function
    template<typename T>
    void fixRemoveRedBlack(Node<T>** ptrRoot, Node<T>* node);

    template<typename T>
    void transplant(Node<T>** ptrRoot, Node<T>* target, Node<T>* replacement);

}

#include "functionsRedBlack.cpp"
