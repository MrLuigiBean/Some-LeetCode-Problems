// Runtime: 4ms, Beats 50.58% with C++
// Memory: 27.02MB, Beats 92.43% with C++
#include <vector>
#include <span>
#include <iostream>

struct TreeNode;

class Solution {
public:
	TreeNode* buildTree(std::vector<int>& inorder, std::vector<int>& postorder)
	{
		// base case
		if (inorder.size() == 1)
			return new TreeNode(inorder.front());

		return _buildTree(inorder, postorder);
	}

private:

	TreeNode* _buildTree(const std::span<const int> inOrderSubspan, const std::span<const int> postOrderSubspan)
	{
		if (inOrderSubspan.empty() || postOrderSubspan.empty())
		{
			return nullptr;
		}
		
		// base case (for leaf nodes)
		if (inOrderSubspan.size() == 1)
		{
			return new TreeNode(postOrderSubspan.front());
		}

		// the parentNode is always at the end of the postorder range
		TreeNode* parentNode = new TreeNode(postOrderSubspan.back());
		int parentPostOrderIndex = postOrderSubspan.size() - 1;

		// find parentNode in inorder
		int parentInOrderIndex = FindIndex(inOrderSubspan, postOrderSubspan.back());

		// MASSIVE THANKS TO https://cs.stackexchange.com/a/441z !!

		int leftPostOrderSubspanCount = postOrderSubspan.size() - parentPostOrderIndex + 1;
		parentNode->left = _buildTree(
			inOrderSubspan.subspan(0, parentInOrderIndex),
			postOrderSubspan.subspan(0, parentInOrderIndex));                                // why tho

		int rightPostOrderSubspanCount = (postOrderSubspan.size() - 1) - parentInOrderIndex; // why tho
		parentNode->right = _buildTree(
			inOrderSubspan.subspan(parentInOrderIndex + 1),
			postOrderSubspan.subspan(parentInOrderIndex, rightPostOrderSubspanCount));       // why tho

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

	void PrintSpan(const std::span<const int>& span, int level)
	{
		constexpr const char* leftBracket = "[";
		constexpr const char* rightBracket = "]";
		constexpr const char* sep = ","; // ", "

		for (int i = 0; i < level; ++i)
			std::cout << " ";

		std::cout << leftBracket;
		for (auto i = span.begin(); i < span.end(); ++i)
			std::cout << *i << ((span.end() - i) == 1 ? "" : sep);
		std::cout << rightBracket << '\n';
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

// ============================================================================
// || my testing framework that failed is below :)                           ||
// ============================================================================

#define PRINT(x) std::cout << #x": " << (x) << "\n"

/// @brief Prints out the elements of a vector on one line, separated by commas.
/// @tparam T The value type of the vector.
/// @param os The output stream to print elements to.
/// @param vec The vector containing the elements to print.
/// @return A reference to the modified output stream.
template <typename T> static std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
	constexpr const char* leftBracket = "[";
	constexpr const char* rightBracket = "]";
	constexpr const char* sep = ","; // ", "

	os << leftBracket;
	for (unsigned i = 0; i < vec.size(); ++i)
		os << vec[i] << (i == vec.size() - 1 ? rightBracket : sep);
	return vec.empty() ? os << rightBracket : os;
}

struct TestCaseInfo {
	std::vector<int> inOrder, postOrder, result;
};

#include <functional>
// i think i messed up somewhere in here :(
class SolutionHelper {
public:
	constexpr static int nullNodeValue = -3001;

	static void freeTree(TreeNode* root) { _postOrder(root, freeNode); };

	static int getTreeHeight(const TreeNode* root) {
		int height = 0;
		_getTreeHeightInOrder(root, &height, 0);
		return height;
	}

	static std::vector<int> getTreeValuesTopToBottom(TreeNode* root) {
		int height = getTreeHeight(root);

		// Since it must include null nodes, there will be 2^h - 1 values to return.
		std::vector<int> treeValues;
		treeValues.reserve(static_cast<std::vector<int>::size_type>((int)std::pow(2, height)) - 1);

		// need to add one to not miss out on the last row of nodes!
		for (int i = 0; i < height + 1; ++i)
			_storeTreeValuesPreOrder(root, treeValues, 0, i);

		// trim trailing null node values (?)
		while (treeValues.back() == nullNodeValue) treeValues.pop_back();

		return treeValues;
	}

	// using Action1 = decltype(hi);
	// using Action2 = void(*)(const TreeNode*);
	using Action = std::function<void(TreeNode*)>;

private:
	static void _storeTreeValuesPreOrder(TreeNode* node, std::vector<int>& treeValues, int currHeight, int heightToMatch) {
		// Since nullptr is a valid value in this case, prevent stack overflow based on currHeight instead.
		if (currHeight > heightToMatch)
			return;

		// action comes before recursion calls
		if (currHeight == heightToMatch)
			treeValues.push_back(node ? node->val : nullNodeValue);

		_storeTreeValuesPreOrder(node ? node->left : nullptr, treeValues, currHeight + 1, heightToMatch);
		_storeTreeValuesPreOrder(node ? node->right : nullptr, treeValues, currHeight + 1, heightToMatch);
	}

	static void _getTreeHeightInOrder(const TreeNode* node, int* height, int currHeight) {
		if (!node)
			return;

		_getTreeHeightInOrder(node->left, height, currHeight + 1);

		// action comes in between recursion calls
		*height = std::max(currHeight, *height);

		_getTreeHeightInOrder(node->right, height, currHeight + 1);
	}

	static void _postOrder(TreeNode* node, Action action) {
		if (!node)
			return;

		_postOrder(node->left, action);
		_postOrder(node->right, action);
		action(node); // action comes after recursion calls
	}

	static void hi(const TreeNode* node) {
		std::cout << "hi, i'm " << (node ? node->val : nullNodeValue) << '\n';
	}

	static void freeNode(TreeNode* node) {
		delete node;
		node = nullptr;
	}
};

int main()
{
	constexpr int null = SolutionHelper::nullNodeValue;

	TestCaseInfo tests[] = {
		// in order,       post order,     expected
		{ { 9,3,15,20,7 }, { 9,15,7,20,3 }, { 3,9,20,null,null,15,7} },
		{ {-1},            {-1},            {-1}                     },
		{ { 2,1 },         { 2,1 },         { 1,2,null }             },
		{ { 1, 2},         { 2,1 },         { 1,null,2 }             },
		{ { 2,3,1 } ,      { 3,2,1 },       { 1,2,null,null,3 }      }, // <- PAINNNNNN
		{ { 3,2,1 },       { 3,2,1 },       { 1,2,null,3 }           },
		{ { 1,2,3,4 },     { 3,2,1,4 },     { 4,1,null,null,2,null,3 }}
	};

	constexpr unsigned testsSize = sizeof(tests) / sizeof(*tests);

	Solution solution;

	for (unsigned i = 0; i < testsSize; ++i)
	{
		TestCaseInfo& test = tests[i];

		PRINT(i);
		PRINT(test.inOrder);
		PRINT(test.postOrder);
		PRINT(test.result);

		if (i == 3)
		{
			int x = 1;
			x += 1;
		}

		TreeNode* result = solution.buildTree(test.inOrder, test.postOrder);
		std::vector<int> treeValues = SolutionHelper::getTreeValuesTopToBottom(result);

		if (treeValues == test.result)
			printf("test passed! :D\n\n");
		else
		{
			std::cout << "Expected: " << test.result << '\n';
			std::cout << "Output: " << treeValues << '\n';
			printf("TEST FAILED. :(\n\n");
		}

		SolutionHelper::freeTree(result);
	}

	printf("\n=====END=====\n");
	return 0;
}
