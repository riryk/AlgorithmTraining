#include <vector>  
#include <errno.h>
#include <math.h>  
#include <algorithm> 
#include <set>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
#include "holiday.h"

using namespace System;
using namespace std;
 
namespace holiday
{
	const int N = 1e5+5;

    int n;
	int start;
	int d;
    long long attraction[N], dp[N];
	vector<long long> cval;
	map<long long, int> cidx;

	struct SegmentTree
	{
        int n;
		SegmentTree(int _n): n(_n) 
		{
		}
	};
    
	SegmentTree *st;

	int walk(int l, int r) 
	{
	   return r - l + min(start - l, r - start);
    }

	long long cost(int l, int r, int k)
	{
       return 0;
	}

    void solve(int l, int r, int optL, int optR) 
	{
	   if (l > r)
	   {
		   return;
	   }

	   int mid = (l+r)>>1;
	   int best = -1;
	   long long ret = -1e15;
	   dp[mid] = -1e15;

	   for (int i = optL; i <= optR; i++) 
	   {
		  long long cur = cost(mid, i, d - walk(mid, i));
		  if (ret < cur)
		  {
			 ret = cur;
			 dp[mid] = cur;
			 best = i;
	      }
	   }

	   solve(l, mid - 1, optL, best);
	   solve(mid + 1, r, best, optR);
    }

	long long findMaxAttraction(int _n, int _start, int _d, int _attraction[]) 
	{
	   n = _n;
	   start = _start; 
	   d = _d;

	   for(int i = 0; i < n; i++)
	   {
		  attraction[i] = _attraction[i];
	   }
 
	   for(int i = 0; i < n; i++)
	   {
		  cval.push_back(attraction[i]);
	   }

	   sort(cval.begin(), cval.end());
	   vector<long long>::iterator it = unique(cval.begin(), cval.end());
	   cval.erase(it, cval.end());

	   for(int i = 0; i < cval.size(); i++)
	   {
	  	  cidx[cval[i]] = i;
	   }
 
	   st = new SegmentTree(n);
	   solve(0, start, start, n-1);

	   return 0;
    }
}

