#pragma once

#include <iostream>

namespace RedBlackFunctions {

    enum Color {
        RED, 
        BLACK
    };

    template<typename T>
    struct Node {
        T payload;
        Node* ptrLeft;
        Node* ptrRight;
        Color color;
    };

    template<typename T>
    Node<T>* createNode(T value);

    template<typename T>
    Node<T>* insertNode(Node<T>* ptrNode, T value);

    template<typename T>
    Node<T>* removeNode(Node<T>* ptrNode, T value);

    template<typename T>
    Node<T>* searchEspecific(Node<T>* ptrNode, T value);

    template<typename T>
    void traverseInOrder(Node<T>* ptrNode);

    template<typename T>
    void verifyRedBlack(Node<T>* ptrNode);

    template<typename T>
    T maxNode(Node<T>* ptrNode);
    
    template<typename T>
    T minNode(Node<T>* ptrNode);
    
    template<typename T>
    int treeHeight(Node<T>* ptrNode);

    template<typename T>
    Node<T>* changeColor(Node<T>* ptrNode);

    template<typename T>
    Node<T>* colorFlip(Node<T>* ptrNode);

    template<typename T>
    Node<T>* leftRotation(Node<T>* ptrNode);

    template<typename T>
    Node<T>* rightRotation(Node<T>* ptrNode);
}

#include "functionsRedBlack.cpp"
