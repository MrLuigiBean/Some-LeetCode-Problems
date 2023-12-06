// Runtime: 1777ms, Beats 5.20% of users with C++
// Memory: 6.28MB, Beats 71.11% of users with C++
#include <stdint.h> // for INT32_MAX and INT32_MIN
#include <iso646.h> // for xor as exclusive-or operation

class Solution
{
public:
	int divide(int dividend, int divisor)
	{
		// edge case where the actual result is outside the integer range
		if (dividend == INT32_MIN && divisor == -1)
			return INT32_MAX;

		// the quotient of 0 / divisor is just 0
		if (dividend == 0)
			return 0;

		// the quotient of dividend / 1 is just dividend
		if (divisor == 1)
			return dividend;

		// the quotient of dividend / -1 is its negative
		if (divisor == -1)
			return GetNegative(dividend);

		// if either number is negative (but not both), the result is negative
		bool isResultNegative = dividend < 0 xor divisor < 0;

		// working with negatives as it has a slightly larger range than positives
		if (dividend > 0)
			dividend = GetNegative(dividend);
		if (divisor > 0)
			divisor = GetNegative(divisor);

		// division is just repeated subtraction!
		int quotient = 0;
		while (dividend <= divisor)
		{
			dividend -= divisor;
			++quotient;
		}

		return isResultNegative ? GetNegative(quotient) : quotient;
	}
private:
	// x - x - x -> 0 - x -> -x
	static int GetNegative(int x)
	{
		return x - x - x;
	}
};
