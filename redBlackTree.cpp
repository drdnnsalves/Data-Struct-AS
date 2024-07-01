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

    cout << "#=#=#=#=#=#=# Insertion Tests #=#=#=#=#=#=#\n\n";

    cout << "After each step, we use the function 'verifyRedBlack', which returns '0' if the tree is not a red-black tree and '1' if it is\n\n";

    cout << "Adding nodes 100, 80 and 110: \n\n ";

    insertNode(&root, 100);
    insertNode(&root, 80);
    insertNode(&root, 110);

    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl;

    cout << "\n\nCase A: The node's parent is the left child of its parent: \n\n";
    cout << "Adding node 70. We have Case A1: Uncle is RED. \n";

    insertNode(&root, 70);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl;

    cout << "\n\nAdding node 75. We have case A2: Uncle is BLACK and current node is a right child \n";

    insertNode(&root, 75);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl;

    cout << "\n\nAdding node 65.\n";

    insertNode(&root, 65);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl;

    cout << "\n\nAdding node 60. We have Case A3: Uncle is BLACK and current node is a left child\n";
    
    insertNode(&root, 60);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl;

    cout << "\n\nCase B: The node's parent is the right child of its parent: \n\n";
    cout << "Adding node 115. We have case B1: Uncle is RED\n";

    insertNode(&root, 115);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl;

    cout << "\n\nAdding node 120. We have Case B2: Uncle is BLACK and current node is a right child\n";

    insertNode(&root, 120);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl;

    cout <<"\n\nAdding node 105\n";
    insertNode(&root, 105);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl;

    cout << "\n\nAdding node 117. We have Case B3: Uncle is BLACK and current node is a left child\n";

    insertNode(&root, 117);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////// Max and Min tests: ////////////////////////////////

    cout << "\n\n#=#=#=#=#=#=# Max and Min Tests #=#=#=#=#=#=#\n\n";

    Node<int>* max = maxNode(root);
    cout << "Maximum payload in the tree: " << max->payload << endl;

    Node<int>* min = minNode(root);
    cout << "\n\nMinimum payload in the tree: " << min->payload << endl;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    cout << "\n\n#=#=#=#=#=#=# Finding Test #=#=#=#=#=#=#\n\n";

    cout << "Using the function 'searchNode' to find the node 117. The function returns the node itself:\n";

    Node<int>* ptrSearchNode = searchNode(root, 117);

    cout << "Payload of ptrSearchNode: " << ptrSearchNode->payload << endl;

    cout << "\nThe function works.";

    cout << "\n\nShall we find one nonexistent node in the tree we've made. For example the node 666.\n";

    Node<int>* ptrSearchNode2 = searchNode(root, 666);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////// In Order tests: ////////////////////////////////

    cout << "\n\n#=#=#=#=#=#=# In Order Test #=#=#=#=#=#=#\n\n";

    cout << "Using the 'traverseInOrder' function we have: \n";

    traverseInOrder(root);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////// Removing tests: ////////////////////////////////

    cout << "\n\n#=#=#=#=#=#=# Removing Tests #=#=#=#=#=#=#\n";

    cout << "\n\nWe are going to test the 'removeNode' function using the function we've created.\n";

    cout << "After each step, we use the function 'verifyRedBlack', which returns '0' if the tree is not a red-black tree and '1' if it is\n\n";

    cout << "Removing node 8. Case 1: The node doesn't have children.\n";

    removeNode(&root, 80);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl << endl;

    cout << "Removing node 120. Case 2: The node has the left children.\n";

    removeNode(&root, 120);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl << endl;

    cout << "Removing node 115. Case 3: The node has both childrens.\n";

    removeNode(&root, 115);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl << endl;

    cout << "Removing node 100. Case 4: Removing the root.\n";

    removeNode(&root, 100);
    printBT(root);

    // Verifying red-black
    cout << "\nVerifying red-blach property: " << verifyRedProperty(root) << endl << endl;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    
    cout << "\n\n#=#=#=#=#=#=# Height test #=#=#=#=#=#=#\n\n";

    cout << "We are going to test the funtions 'treeHeight' and 'treeHeightOptimized'. The following results is the mean of 10 iterations, using trees with 1000000 nodes each, in both fucntions: \n";

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
    cout << "Average execution time of treeHeight:          " << avgDurationNormal << " nanoseconds" << endl;
    

    return 0;
}
