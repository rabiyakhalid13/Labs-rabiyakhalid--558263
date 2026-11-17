#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int id;          // service ID
    int cost;        // monthly cost
    Node* left;
    Node* right;
};

/* ---------- BST insert (ordered by cost) ---------- */
Node* insert(Node* root, int id, int cost) {
    // Empty spot found: create the new node here
    if (root == NULL) {
        Node* n = new Node;
        n->id = id;
        n->cost = cost;
        n->left = NULL;
        n->right = NULL;
        return n;
    }
    // Smaller cost goes left, otherwise right
    if (cost < root->cost) root->left = insert(root->left, id, cost);
    else                   root->right = insert(root->right, id, cost);
    return root;
}

int B;   // target budget

/* ================= PART A: downward paths ================= */
vector<Node*> path;   // current path (acts as the stack)

// Print the nodes currently in the path
void printPath() {
    cout << "  ";
    for (int i = 0; i < path.size(); i++) {
        cout << "S" << path[i]->id << "(" << path[i]->cost << ")";
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << endl;
}

// Walk downward from one start node, tracking the running sum
void walkDown(Node* node, int sum) {
    if (node == NULL) return;

    path.push_back(node);          // MAKE: add this node to the path
    sum += node->cost;

    if (sum == B) printPath();     // solution: path sum equals the budget

    // PRUNING: if sum already reached B, going deeper only increases it
    // (costs are positive), so stop here
    if (sum < B) {
        walkDown(node->left, sum);     // RECURSE into left child
        walkDown(node->right, sum);    // RECURSE into right child
    }

    path.pop_back();               // UNDO: remove this node (backtrack)
}

// Treat every node in the tree as a possible starting point
void partA(Node* root) {
    if (root == NULL) return;
    walkDown(root, 0);     // paths starting at this node
    partA(root->left);     // then try left subtree nodes as starts
    partA(root->right);    // then try right subtree nodes as starts
}

/* ================= PART B: subsets with pruning ================= */
vector<Node*> sortedNodes;   // all nodes in ascending cost order
vector<Node*> chosen;        // nodes chosen in the current subset

// Inorder traversal of a BST visits nodes in ascending order
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    sortedNodes.push_back(root);
    inorder(root->right);
}

// Print the nodes currently chosen
void printSubset() {
    cout << "  { ";
    for (int i = 0; i < chosen.size(); i++)
        cout << "S" << chosen[i]->id << "(" << chosen[i]->cost << ") ";
    cout << "}" << endl;
}

// i = index of the node being decided, sum = sum of chosen nodes so far
void subsetSum(int i, int sum) {
    // Solution: chosen nodes add up to the budget
    if (sum == B) {
        printSubset();
        return;
    }

    // No more nodes left to decide
    if (i == (int)sortedNodes.size()) return;

    // PRUNING: the list is sorted, so if this node already pushes the sum
    // over B, every later (larger) node will too. Stop immediately.
    if (sum + sortedNodes[i]->cost > B) return;

    chosen.push_back(sortedNodes[i]);                  // MAKE: include this node
    subsetSum(i + 1, sum + sortedNodes[i]->cost);      // RECURSE
    chosen.pop_back();                                 // UNDO: remove this node

    subsetSum(i + 1, sum);                             // SKIP this node
}

/* ================= main ================= */
int main() {
    int n;
    cout << "Number of nodes: ";
    cin >> n;

    // Build the BST from user input
    Node* root = NULL;
    for (int i = 0; i < n; i++) {
        int id, cost;
        cout << "Node " << i + 1 << " (id cost): ";
        cin >> id >> cost;
        root = insert(root, id, cost);
    }

    cout << "Target budget B: ";
    cin >> B;

    cout << "Part A (downward paths):" << endl;
    partA(root);

    // Part B needs the nodes in sorted order first
    inorder(root);
    cout << "Part B (subsets):" << endl;
    subsetSum(0, 0);

    return 0;
}