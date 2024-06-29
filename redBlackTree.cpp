#include <iostream>
#include <cstdlib>
#include "functionsRedBlack.h"

using namespace std;
using namespace RedBlackFunctions;

int main() {
    Node<int>* root = nullptr;

    //////////////////////////////// Insertion tests: ////////////////////////////////

    cout << "#=#=#=# Insertion Tests #=#=#=#\n\n";

    cout << "Adding nodes 100, 80 and 110: \n\n ";

    insertNode(&root, 100);
    insertNode(&root, 80);
    insertNode(&root, 110);

    printBT(root);

    cout << "\n\nCase A: The node's parent is the left child of its parent: \n\n";
    cout << "Adding node 70. We have Case A1: Uncle is RED. \n";

    insertNode(&root, 70);
    printBT(root);

    cout << "\n\nAdding node 75. We have case A2: Uncle is BLACK and current node is a right child \n";

    insertNode(&root, 75);
    printBT(root);

    cout << "\n\nAdding node 65.\n";

    insertNode(&root, 65);
    printBT(root);

    cout << "\n\nAdding node 60. We have Case A3: Uncle is BLACK and current node is a left child\n";
    
    insertNode(&root, 60);
    printBT(root);

    cout << "\n\nCase B: The node's parent is the right child of its parent: \n\n";
    cout << "Adding node 115. We have case B1: Uncle is RED\n";

    insertNode(&root, 115);
    printBT(root);

    cout << "\n\nAdding node 120. We have Case B2: Uncle is BLACK and current node is a right child\n";

    insertNode(&root, 120);
    printBT(root);

    cout <<"\n\nAdding node 105\n";
    insertNode(&root, 105);
    printBT(root);

    cout << "\n\nAdding node 117. We have Case B3: Uncle is BLACK and current node is a left child\n";

    insertNode(&root, 117);
    printBT(root);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////// Max and Min tests: ////////////////////////////////

    cout << "\n\n#=#=#=# Max and Min Tests #=#=#=#\n\n";

    Node<int>* max = maxNode(root);
    cout << "Maximum payload in the tree: " << max->payload << endl;

    Node<int>* min = minNode(root);
    cout << "\n\nMinimum payload in the tree: " << min->payload << endl;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    return 0;
}
