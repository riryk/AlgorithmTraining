#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>

using namespace System;
using namespace std;

int canDistribute(long long position[], long long food[], int n, int minfood)
{
	long long carry = 0; 
	for (int i = 0; i < n - 2; i++)
	{
        long long x = food[i] + carry;
		if (x < minfood) 
		{
			carry = x - minfood - (position[i + 1] - position[i]);
		}
		else 
		{
			carry = x - minfood - (position[i + 1] - position[i]);
			if (carry < 0)
				carry = 0;
		}
	}

	return food[n - 1] + carry >= minfood;
}

int maxFish(long long position[], long long food[], int n)
{
    long long maxfood = 0;
    for (int i = 0; i < n; i++)
	   if (maxfood < food[i])
		   maxfood = food[i];
    
	long long lo = 0;
	long long hi = maxfood;
    long long mid;

	while (lo < hi)
	{
       mid = (lo + hi) / 2;
	   if (canDistribute(position, food, n, mid))
		   lo = mid + 1;
	   else 
		   hi = mid;
	}

    return lo - 1;
}

