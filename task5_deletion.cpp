// TASK 5: Node Deletion
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
 
 
// Deletes node with given value together with all its descendants
bool deleteNode(TreeNode*& root, int value) {
    TreeNode* target = findNode(root, value);
    if (!target) { cout << "  [Error] Node " << value << " not found.\n"; return false; }
    if (target == root) {              // root selected: delete whole tree
        freeSubtree(root);
        root = nullptr;
        return true;
    }
    vector<TreeNode*>& sib = target->parent->children;
    sib.erase(remove(sib.begin(), sib.end(), target), sib.end());
    freeSubtree(target);
    return true;
}
 
int main() {
    TreeNode* root = buildTree();
    cout << "===== TASK 5: Deletion =====\n";
    cout << "Tree BEFORE deletion:\n";
    display(root);
 
    cout << "\nDeleting node 3 (and its subtree)...\n";
    deleteNode(root, 3);
    cout << "\nTree AFTER deletion:\n";
    display(root);
 
    cout << "\nDeleting invalid node 42...\n";
    deleteNode(root, 42);
 
    cout << "\nDeleting root (node 1)...\n";
    deleteNode(root, 1);
    display(root);
 
    return 0;
}