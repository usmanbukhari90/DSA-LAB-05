// TASK 4: Tree Traversals
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
 
void bfs(TreeNode* root) {
    if (!root) { cout << "(empty)\n"; return; }
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();
        cout << cur->data << " ";
        for (TreeNode* c : cur->children) q.push(c);
    }
    cout << "\n";
}
void preOrder(TreeNode* n) {
    if (!n) return;
    cout << n->data << " ";
    for (TreeNode* c : n->children) preOrder(c);
}
void postOrder(TreeNode* n) {
    if (!n) return;
    for (TreeNode* c : n->children) postOrder(c);
    cout << n->data << " ";
}
 
int main() {
    TreeNode* root = buildTree();
    cout << "===== TASK 4: Traversals =====\n";
    cout << "Breadth-first (BFS): "; bfs(root);
    cout << "Pre-order          : "; preOrder(root);  cout << "\n";
    cout << "Post-order         : "; postOrder(root); cout << "\n";
 
    cout << "\nEmpty tree BFS: "; bfs(nullptr);
 
    freeSubtree(root);
    return 0;
}