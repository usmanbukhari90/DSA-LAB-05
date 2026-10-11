// TASK 6: Tree Analysis (before and after deletion)
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
 
 
int countLeaves(TreeNode* n) {
    if (!n) return 0;
    if (n->children.empty()) return 1;
    int t = 0;
    for (TreeNode* c : n->children) t += countLeaves(c);
    return t;
}
 
void analysis(TreeNode* root) {
    cout << "  Number of nodes : " << countNodes(root) << "\n";
    cout << "  Height          : " << height(root) << "\n";
    cout << "  Leaf nodes      : " << countLeaves(root) << "\n";
    cout << "  BFS             : "; bfs(root);
    cout << "  Pre-order       : "; preOrder(root);  cout << "\n";
    cout << "  Post-order      : "; postOrder(root); cout << "\n";
}
 
int main() {
    TreeNode* root = buildTree();
 
    cout << "===== TASK 6: ORIGINAL TREE =====\n";
    analysis(root);
 
    deleteNode(root, 3);
    cout << "\n===== TASK 6: AFTER DELETING NODE 3 =====\n";
    analysis(root);
 
    cout << "\nTime complexity: BFS = O(n), Pre-order = O(n), Post-order = O(n)\n";
 
    freeSubtree(root);
    return 0;
}
 