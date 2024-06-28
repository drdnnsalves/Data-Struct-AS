#include <iostream>
#include <cstdlib>
#include "functionsRedBlack.h"

using namespace std;
using namespace RedBlackFunctions;

int main() {
    Node<int>* root = nullptr;

    insertNode(root, 10);
    insertNode(root, 9);
    insertNode(root, 7);

    cout << "In-order traversal of the Red-Black Tree:" << endl;
    traverseInOrder(root);
    cout << endl;

    return 0;
}
