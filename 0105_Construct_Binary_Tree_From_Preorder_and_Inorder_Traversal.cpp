// Runtime: 7ms, Beats 37.87% with C++
// Memory: 27.17MB, Beats 81.03% with C++
#include <vector>
#include <span>

struct TreeNode;

class Solution {
public:
	TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder)
	{
		// base case
		if (inorder.size() == 1)
			return new TreeNode(inorder.front());

		return _buildTree(preorder, inorder);
	}

private:

	TreeNode* _buildTree(const std::span<const int> preOrderSubspan, const std::span<const int> inOrderSubspan)
	{
        if (preOrderSubspan.empty() || inOrderSubspan.empty())
		{
			return nullptr;
		}
		
		// base case (for leaf nodes)
		if (inOrderSubspan.size() == 1)
		{
			return new TreeNode(preOrderSubspan.front());
		}

		// the parentNode is always at the start of the preorder range
		TreeNode* parentNode = new TreeNode(preOrderSubspan.front());
		int parentPreOrderIndex = 0;

		// find parentNode in inorder
		int parentInOrderIndex = FindIndex(inOrderSubspan, preOrderSubspan.front());

		// MASSIVE THANKS TO https://cs.stackexchange.com/a/441z !!

		parentNode->left = _buildTree(
			preOrderSubspan.subspan(1, parentInOrderIndex),                                 // why tho
			inOrderSubspan.subspan(0, parentInOrderIndex));

		int rightPreOrderSubspanCount = preOrderSubspan.size() - parentInOrderIndex;        // why tho
		parentNode->right = _buildTree(
			preOrderSubspan.subspan(parentInOrderIndex + 1, rightPreOrderSubspanCount),     // why tho
			inOrderSubspan.subspan(parentInOrderIndex + 1));

		return parentNode;
	}

	int FindIndex(const std::span<const int>& span, int element)
	{
		auto it = std::ranges::find(span, element);
		if (it == span.end())
		{
			return -1;
		}

		return it - span.begin();
	}
};

#ifndef TREE_NODE
#define TREE_NODE
// Definition for a binary tree node.
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};
#endif
