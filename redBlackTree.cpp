#include <iostream>
#include <cstdlib>
#include "functionsRedBlack.h"

using namespace std;
using namespace RedBlackFunctions;

int main() {
    Node<int>* root = nullptr;

    insertNode(&root, 1);
    insertNode(&root, 2);
    insertNode(&root, 3);
    insertNode(&root, 4);
    insertNode(&root, 5);
    insertNode(&root, 6);
    insertNode(&root, 7);
    insertNode(&root, 20);
    insertNode(&root, 30);
    insertNode(&root, 100);
    insertNode(&root, 1001);
    insertNode(&root, 28);

    printBT(root);

    cout << verifyRedBlack(root) <<endl;

    Node<int>* node = nullptr;

    node = searchNode(root, 5);
    cout << node->payload << endl;

    node = searchNode(root, 1001);
    cout << node->payload << endl;

    return 0;
}
