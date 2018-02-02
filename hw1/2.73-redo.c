#include <limits.h>

/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y)
{
	int doOverflow = __builtin_add_overflow_p (x, y, (int) 0);
	int xyNonnegative = (!(x & INT_MIN)) && (!(y & INT_MIN));
	int ans = x + y;
	(!doOverflow)|| ((xyNonnegative)&&(ans = INT_MAX))||(ans = INT_MIN);

	return ans;
}
