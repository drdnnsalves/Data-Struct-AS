#include <iostream>
#include <cstdlib>
#include <chrono>
#include "functionsRedBlack.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

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

    removeNode(&root, 80);
    printBT(root);

    cout << verifyRedProperty(root) << endl;


    /*
    cout << "\n\n#=#=#=# Height test #=#=#=#\n\n";

    const int numNodes = 1000000; // Number of nodes in the tree
    const int iterations = 10;    // Number of iterations for averaging

    long long totalDurationOptimized = 0;
    long long totalDurationNormal = 0;

    // Perform measurements over iterations
    for (int iter = 0; iter < iterations; ++iter) {
        Node<int>* root = nullptr;

        // Seed the random number generator
        srand(time(nullptr));

        // Insert 'numNodes' random values into the Red-Black tree
        for (int i = 0; i < numNodes; ++i) {
            int value = rand() % 1000000000; // Generate a random value (adjust range as needed)
            insertNode(&root, value);
        }

        // Measure time for treeHeightOptimized
        auto timeStart = high_resolution_clock::now();
        treeHeightOptimized(root);
        auto timeStop = high_resolution_clock::now();
        auto timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        totalDurationOptimized += timeDuration.count();

        // Measure time for treeHeight
        timeStart = high_resolution_clock::now();
        treeHeight(root);
        timeStop = high_resolution_clock::now();
        timeDuration = duration_cast<nanoseconds>(timeStop - timeStart);
        totalDurationNormal += timeDuration.count();

        clearTree(&root);

    }

    // Calculate the average execution times
    long long avgDurationOptimized = totalDurationOptimized / iterations;
    long long avgDurationNormal = totalDurationNormal / iterations;

    // Print the results
    cout << "Average execution time of treeHeightOptimized: " << avgDurationOptimized << " nanoseconds" << endl;
    cout << "Average execution time of treeHeight: " << avgDurationNormal << " nanoseconds" << endl;
    */

    return 0;
}
