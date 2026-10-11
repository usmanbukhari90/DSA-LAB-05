// TASK 2: Basic Tree Operations
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
 
bool isRoot(TreeNode* n) { 
    return n && n->parent == nullptr;
 }

bool isLeaf(TreeNode* n) {
     return n && n->children.empty();
     }

int  degree(TreeNode* n) { 
    return n ? (int)n->children.size() : 0;
 }
 
int  countNodes(TreeNode* root) {
    if (!root) return 0;
    int total = 1;
    for (TreeNode* c : root->children) total += countNodes(c);
    return total;
}
 
int main() {
    TreeNode* root = buildTree();
    cout << "===== TASK 2: Basic Operations =====\n";
    cout << "Is node 1 root?  " << (isRoot(findNode(root, 1)) ? "Yes" : "No") << "\n";
    cout << "Is node 5 root?  " << (isRoot(findNode(root, 5)) ? "Yes" : "No") << "\n";
    cout << "Is node 5 leaf?  " << (isLeaf(findNode(root, 5)) ? "Yes" : "No") << "\n";
    cout << "Is node 4 leaf?  " << (isLeaf(findNode(root, 4)) ? "Yes" : "No") << "\n";
    cout << "Degree of node 1: " << degree(findNode(root, 1)) << "\n";
    cout << "Degree of node 4: " << degree(findNode(root, 4)) << "\n";
    cout << "Total nodes     : " << countNodes(root) << "\n";
    cout << "Nodes in empty tree: " << countNodes(nullptr) << "\n";
 
    freeSubtree(root);
    return 0;
}