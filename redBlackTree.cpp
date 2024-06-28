#include <iostream>
#include <cstdlib>
#include "functionsRedBlack.h"

using namespace std;
using namespace RedBlackFunctions;

int main() {
    Node<int>* root = nullptr;

    insertNode(&root, 10);
    insertNode(&root, 9);
    insertNode(&root, 11);
    insertNode(&root, 7);
    insertNode(&root, 6);
    insertNode(&root, 2);
    insertNode(&root, 1);
    insertNode(&root, 20);
    insertNode(&root, 30);
    insertNode(&root, 100);
    insertNode(&root, 1001);
    insertNode(&root, 28);

    printBT(root);

    return 0;
}
