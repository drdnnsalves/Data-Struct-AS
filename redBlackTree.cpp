#include <iostream>
#include <cstdlib>
#include "functionsRedBlack.h"

using namespace std;
using namespace RedBlackFunctions;


int main() {
    Node<int>* root = nullptr;

    insertNode(root, 10, root);
    insertNode(root, 11, root);
    insertNode(root, 9, root);
    insertNode(root, 7, root);

    cout << "In-order traversal of the Red-Black Tree:" << endl;
    traverseInOrder(root);
    cout << endl;

    return 0;
}