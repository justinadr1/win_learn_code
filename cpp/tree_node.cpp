#include <iostream>
#include <queue>
using namespace std;

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}

};

TreeNode* invertTree(TreeNode* root)
{
	if (!root)
		return nullptr;

	TreeNode* temp = root->left;
	root->left = root->right;
	root->right = temp;

	invertTree(root->left);
	invertTree(root->right);

	return root;
}

void printLevelOrder(TreeNode* root) 
{
    if (!root) 
        return;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) 
    {
        TreeNode* node = q.front();
        q.pop();

        cout << node->val << ' ';

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
}

void deleteTree(TreeNode* root) 
{ 
	if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

int main()
{
	TreeNode* tree = new TreeNode(4,
		new TreeNode(2,
			new TreeNode(1), new TreeNode(3)),
		new TreeNode(7,
			new TreeNode(6), new TreeNode(9)));
	
    
    printLevelOrder(tree);  
    
    invertTree(tree);

	deleteTree(tree);

}