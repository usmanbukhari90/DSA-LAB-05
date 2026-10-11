// TASK 3: Tree Height and Depth
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
 
struct TreeNode {
    int data;
    TreeNode* parent;
    vector<TreeNode*> children;
    TreeNode(int v) : data(v), parent(nullptr) {}
};
 
// Find a node by its (unique) value; returns nullptr if not found
TreeNode* findNode(TreeNode* root, int value) {
    if (!root) return nullptr;
    if (root->data == value) return root;
    for (TreeNode* c : root->children) {
        TreeNode* r = findNode(c, value);
        if (r) return r;
    }
    return nullptr;
}
 
// Insert 'value' as a child of 'parentValue'
bool insertChild(TreeNode* root, int parentValue, int value) {
    if (!root) { cout << "  [Error] Tree is empty.\n"; return false; }
    if (findNode(root, value)) {
        cout << "  [Error] Value " << value << " already exists (must be unique).\n";
        return false;
    }
    TreeNode* p = findNode(root, parentValue);
    if (!p) {
        cout << "  [Error] Parent " << parentValue << " not found.\n";
        return false;
    }
    TreeNode* n = new TreeNode(value);
    n->parent = p;
    p->children.push_back(n);
    return true;
}
 
// Builds the 10-node test tree
TreeNode* buildTree() {
    TreeNode* root = new TreeNode(1);
    int pairs[][2] = {{1,2},{1,3},{1,4},{2,5},{2,6},{3,7},{4,8},{4,9},{8,10}};
    for (auto& p : pairs) insertChild(root, p[0], p[1]);
    return root;
}
 
// Frees a node and all its descendants
void freeSubtree(TreeNode* n) {
    if (!n) return;
    for (TreeNode* c : n->children) freeSubtree(c);
    delete n;
}
 
int height(TreeNode* n) {
    if (!n) return -1;                 // empty tree
    int best = -1;
    for (TreeNode* c : n->children) best = max(best, height(c));
    return best + 1;                   // leaf -> 0
}

int depth(TreeNode* n) {
    if (!n) return -1;                 // invalid node
    int d = 0;
    while (n->parent) { n = n->parent; d++; }
    return d;                          // root -> 0
}
 
int main() {
    TreeNode* root = buildTree();
    cout << "===== TASK 3: Height & Depth =====\n";
    cout << "Height of tree (root)  : " << height(root) << "\n";
    cout << "Height of node 4       : " << height(findNode(root, 4)) << "\n";
    cout << "Height of leaf node 5  : " << height(findNode(root, 5)) << "\n";
    cout << "Depth of root (node 1) : " << depth(root) << "\n";
    cout << "Depth of node 4        : " << depth(findNode(root, 4)) << "\n";
    cout << "Depth of node 10       : " << depth(findNode(root, 10)) << "\n";
    cout << "Height of empty tree   : " << height(nullptr) << "\n";
 
    freeSubtree(root);
    return 0;
}
 