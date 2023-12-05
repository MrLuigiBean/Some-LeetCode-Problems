// Runtime: 115ms, Beats 70.14% of users with C++
// Memory: 6539MB, Beats 61.52% of users with C++
#include <vector>

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
