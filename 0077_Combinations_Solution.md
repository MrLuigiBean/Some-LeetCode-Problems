# Intuition
<!-- Describe your first thoughts on how to solve this problem. -->
The intuition necessary is that from combination to combination, only the last 'digit' ever changes. For example, in the case of `n = 4` and `n = 2`, the combinations `[1,2],[1,3],[1,4]` only ever have the last 'digit' increasing.

This is unless it has hit its maximum. Once the last 'digit' hits that limit, an index before it must be incremented, and once done, the last digit can be reset to an appropriate value.

In the same example, the combination `[1,4]` has its last 'digit' at its maximum. If we try to increment it, we get an invalid combination(`[1,5]`) - no way to have a `5` when `n = 4` after all! This means that we should increment a 'digit' before that (may not necessarily be "i - 1" as the adjacent 'digit' could also be at its limit!). Here we increment `1` to get `2`. We can't have `[2,5]` as a combination, so we need to set the appropriate values for the elements after the one we just changed. Since the combinations being generated here are in ascending order, the appropriate values would be the numbers in ascending order, starting with the one just after the one we changed. This results in our next valid combination, `[2,3]`.

# Approach
<!-- Describe your approach to solving the problem. -->
The flow of this backtracking solution boils down to a couple of key steps. Before that though, the trivial cases (k = 1 and k = n) can be calculated and returned immediately.

## Step 1: Allocate the necessary space
The last thing you want in C++ is having your vector resize over and over and make heap allocations due to all the element insertions! Reserving space using `std::vector::reserve()` is crucial to avoiding this problem. To reserve the right amount of space, the number of combinations must be calculated. Fortunately, there is another LeetCode problem that is exactly that: Problem #0118.

## Step 2: Begin backtracking
The `backtrack()` function takes in two parameters, `result` and `comb`. `result` will be the return value of `Solution::combine()`, so we need to make sure we add insert our combinations(`comb`) there. After doing so, we increment the last 'digit' to try and get the next combination. If it is not valid, we signal a failure by returning `false` from the backtracking function.

## Step 3: Managing Invalid Combinations
Should the combination be invalid, we need to find the next most appropriate 'digit' to increment instead. If there is no such result, we have reached the end of generating combinations. Otherwise, we increase the 'digit' we just found, set appropriate values to the remaining part to the right of that index, and set the index back to be the last element to let the backtracking take control again.

# Complexity
If my complexities seem incorrect, please let me know. Thank you!

<!-- Add your time complexity here, e.g. $$O(n)$$ -->
- Time complexity: $$O(k^2)$$

<!-- Add your space complexity here, e.g. $$O(n)$$ -->
- Space complexity: $$O(C(n,k))$$

# Code
```
class Solution
{
public:
	std::vector<std::vector<int>> combine(int n, int k)
	{
		// case for n choose 1
		if (k == 1)
		{
			std::vector<std::vector<int>> result(n, std::vector<int>(k));
			for (int i = 0; i < n; ++i)
				result[i][0] = i + 1;
			return result;
		}

		// case for n choose n
		else if (k == n)
		{
			std::vector<std::vector<int>> result(1, std::vector<int>(k));
			for (int i = 0; i < k; ++i)
				result[0][i] = i + 1;
			return result;
		}

		// general case
		std::vector<std::vector<int>> result{};
		result.reserve(numOfCombinations(n, k));
		priv_n = n;
		priv_k = k;
		index = k - 1; // the last element in the combination

		// create the first combination [1,2,3,...]
		std::vector<int> comb(k);
		for (int i = 0; i < k; ++i)
			comb[i] = i + 1;

		backtrack(result, comb);

		return result;
	}

private:
	int priv_n = 0;
	int priv_k = 0;
	int index = 0;

	// The maximum of any element should be is n - k + index + 1.
	// The value of a given index is 'bad' if this limit is exceeded.
	// e.g. for C(20, 3), max = [18, 19, 20]
	// e.g. for C(4, 2), max = [3, 4]
	bool isBadIndex(const std::vector<int> &comb)
	{
		return comb[index] > priv_n - priv_k + 1 + index;
	}

	// if i WERE to increment it, would it be bad?
	bool isIncrementBadIndex(const std::vector<int> &comb)
	{
		return comb[index] + 1 > priv_n - priv_k + 1 + index;
	}

	// yoinked and modified from 118. Pascal's Triangle submission
	int numOfCombinations(int n, int k)
	{
		// initialise result with having the correct number of rows
		std::vector<std::vector<int>> result(n + 1);

		// make each row have the correct number of spaces
		for (int i = 0; i < result.size(); ++i)
			result[i].reserve(i + 1);

		for (int i = 0; i < result.size(); ++i)
		{
			for (int j = 0; j < result[i].capacity(); ++j)
			{
				// using the subscript operator to insert doesn't work
				// because the size is still 0 dummy!!!

				int value;

				// the edges are always 1
				if (j == 0 || j == result[i].capacity() - 1)
					value = 1;

				// the next closest to the edges are always the row number
				else if (j == 1 || j == result[i].capacity() - 2)
					value = i;

				// take numbers from previous row
				else
					value = result[i - 1][j - 1] + result[i - 1][j];

				result[i].emplace_back(value);
			}
		}
		return result[n][k];
	}

	bool backtrack(std::vector<std::vector<int>> &result, std::vector<int> &comb)
	{
		// add new valid combination to result
		result.emplace_back(comb);

		// increment for next combination
		++comb[index];

		if (isBadIndex(comb))
		{
			// the max for this index has been hit
			// go back and increment the previous one instead
			return false;
		}

		while (!backtrack(result, comb))
		{
			while (index >= 0 && isIncrementBadIndex(comb))
				--index;

			// the base case / stop condition
			if (index < 0)
				return true;

			// increment the identified index (since its guaranteed to be safe to do so)
			++comb[index];

			// set all subsequent elements (e.g. from [...,1,8,9] to [...,2,3,4])
			for (int i = index + 1; i < priv_k; ++i)
				comb[i] = comb[index] + i - index;

			// set index to the last index in the combination
			index = priv_k - 1;
		}
		return true;
	}
};

```