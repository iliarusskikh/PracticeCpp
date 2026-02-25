// C++ code of Vertical Traversal using Brute Force
#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

// A utility function to find min and max 
// distances with respect to root.
void findMinMax(Node* node, int& min, int& max, int hd) {
  
    // Base case
    if (node == nullptr) return;

    // Update min and max
    if (hd < min) min = hd;
    else if (hd > max) max = hd;

    // Recur for left and right subtrees
    findMinMax(node->left, min, max, hd - 1);
    findMinMax(node->right, min, max, hd + 1);
}

// A utility function to collect all 
// nodes on a given vertical line_no.
// hd is horizontal distance of current node with respect to root.
void collectVerticalLine(Node* node, int line, 
                         int hd, vector<int>& res) {
    // Base case
    if (node == nullptr) return;

    // If this node is on the given vertical line
    if (hd == line)
        res.push_back(node->data);

    // Recur for left and right subtrees
    collectVerticalLine(node->left, line, hd - 1, res);
    collectVerticalLine(node->right, line, hd + 1, res);
}

// The main function that returns a 
// vector of nodes in vertical order
vector<vector<int>> verticalOrder(Node* root) {
    vector<vector<int>> res;

    // Find min and max distances with 
    // respect to root
    int min = 0, max = 0;
    findMinMax(root, min, max, 0);

    // Iterate through all possible vertical
    // lines from leftmost to rightmost
    for (int line = min; line <= max; line++) {
        vector<int> verticalNodes;
        collectVerticalLine(root, line, 0, verticalNodes);
        res.push_back(verticalNodes);
    }

    return res;
}

int main() {
  
    // Create binary tree
    //            1
    //          /   \
    //         2     3
    //        / \   / \
    //       4   5 6   7
    //              \   \
    //               8   9

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    root->right->left->right = new Node(8);
    root->right->right->right = new Node(9);

    vector<vector<int>> res = verticalOrder(root);

    // Print grouped vertical nodes
    for (vector<int> group : res) {
        cout << "[ ";
        for (int val : group) 
            cout << val << " ";
        cout << "] ";
    }
    cout << endl;

    return 0;
}


