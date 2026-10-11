// TASK 1: General Tree Construction
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
 
// Prints every node with its parent and children
void display(TreeNode* root) {
    if (!root) { cout << "  (empty tree)\n"; return; }
    cout << "  Node " << root->data << " | Parent: ";
    if (root->parent) cout << root->parent->data; else cout << "None";
    cout << " | Children: ";
    if (root->children.empty()) cout << "None";
    for (TreeNode* c : root->children) cout << c->data << " ";
    cout << "\n";
    for (TreeNode* c : root->children) display(c);
}
 
int main() {
    TreeNode* root = buildTree();
    cout << "===== TASK 1: Tree (node | parent | children) =====\n";
    display(root);
 
    cout << "\nInvalid insert tests:\n";
    insertChild(root, 99, 11);   // parent does not exist
    insertChild(root, 1, 1);     // duplicate value
 
    freeSubtree(root);
    return 0;
}