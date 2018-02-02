#include <limits.h>

/* Addition that saturates to TMin or TMax */
int saturating_add(int x, int y)
{
	int xNonnegative = !(x & INT_MIN);
	int yNonnegative = !(y & INT_MIN);
	int ans = x + y;
	int ansNonnegative = !(ans & INT_MIN);
	int poOverflow = (xNonnegative && yNonnegative && !ansNonnegative);
	int NeOverflow = (!xNonnegative && !yNonnegative && ansNonnegative);

	((!NeOverflow) && (!poOverflow)) || (((!NeOverflow) && (poOverflow)) && (ans = INT_MAX)) || (ans = INT_MIN);

	return ans;

}
