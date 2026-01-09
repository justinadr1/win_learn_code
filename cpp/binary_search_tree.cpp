#include <iostream>
#include <queue>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

TreeNode* insertBST(TreeNode* root, int value)
{
    if (!root)
        return new TreeNode(value);

    if (value < root->val)
        root->left = insertBST(root->left, value);
    else if (value > root->val)
        root->right = insertBST(root->right, value);
    // else: ignore duplicates (or handle separately)

    return root;
}

TreeNode* searchBST(TreeNode* root, int target)
{
    if (!root || root->val == target)
        return root;

    if (target < root->val)
        return searchBST(root->left, target);

    return searchBST(root->right, target);
}

void inorder(TreeNode* root)
{
    if (!root) 
        return;

    inorder(root->left);
    std::cout << root->val << " ";
    inorder(root->right);
}

TreeNode* findMin(TreeNode* node)
{
    while (node && node->left)
        node = node->left;
    return node;
}

TreeNode* deleteBST(TreeNode* root, int value)
{
    if (!root)
        return nullptr;

    if (value < root->val) {
        root->left = deleteBST(root->left, value);
    }
    else if (value > root->val) {
        root->right = deleteBST(root->right, value);
    }
    else {
        // Node found

        // Case 1: no children
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }
        // Case 2: one child
        else if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        // Case 3: two children
        else {
            TreeNode* successor = findMin(root->right);
            root->val = successor->val;
            root->right = deleteBST(root->right, successor->val);
        }
    }
    return root;
}

void deleteTree(TreeNode* root)
{
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main()
{
    TreeNode* root = nullptr;

    int values[] = { 5, 3, 7, 2, 4, 6, 8 };
    for (int v : values)
        root = insertBST(root, v);

    inorder(root);  // 2 3 4 5 6 7 8
    std::cout << "\n";

    root = deleteBST(root, 5);
    inorder(root);  // 2 3 4 6 7 8
    std::cout << "\n";

    deleteTree(root);
}