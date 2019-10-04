#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>
#include <iostream>
#include <cmath>
#include <math.h> 

using namespace System;
using namespace std;

namespace lazy
{
    #define MAX 1000

	int tree[MAX] = {0};
	int lazy[MAX] = {0};
    
	void updateSTRangeUtil(int start, int end, int us, int ue, int diff, int si)
	{
		if (lazy[si] != 0)
		{
            tree[si] += (end - start + 1) * lazy[si];
            if (start != end)
			{
				lazy[2 * si + 1] += lazy[si];
                lazy[2 * si + 2] += lazy[si];
			}
			lazy[si] = 0;
		}

        if (start > end || ue < start || us > end)
		{
			return;
		}

		if (us <= start && end <= ue)
		{
            tree[si] += (end - start + 1) * diff;
			if (start < end)
			{
                lazy[2*si + 1] += diff;
                lazy[2*si + 2] += diff;
			}

			return;
		}

        int mid = (start + end) / 2;

        updateSTRangeUtil(start, mid, us, ue, diff, 2 * si + 1);
        updateSTRangeUtil(mid + 1, end, us, ue, diff, 2 * si + 2); 

        tree[si] = tree[2 * si + 1] + tree[2 * si + 2];
	}

	void updateSTRange(int n, int ustart, int uend, int diff, int si)
	{
        updateSTRangeUtil(0, n - 1, ustart, uend, diff, si);
	}

	void constructSTUtil(int arr[], int start, int end, int si)
	{
        if (start > end)
		{
			return;
		}

        if (start == end)
		{
			tree[si] = arr[start];
			return;
		}

		int mid = (start + end) / 2;

        constructSTUtil(arr, start, mid, 2 * si + 1);
        constructSTUtil(arr, mid + 1, end, 2 * si + 2);

		tree[si] = tree[2 * si + 1] + tree[2 * si + 2];
	}

    void constructST(int arr[], int n)
	{
        constructSTUtil(arr, 0, n - 1, 0); 
	}
}
