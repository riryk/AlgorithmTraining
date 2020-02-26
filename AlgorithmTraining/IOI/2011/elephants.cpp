#include "stdafx.h"
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
#include <utility>

using namespace System;
using namespace std;
 
namespace elephants
{ 
	int l, n;
	int x[150010];
	int ci[150010], gp[150010];
    int gn;
	int gs[200];
	int pos[200][1310];
	int sz=800;

	int compare(int &i, int &j)
	{
		return x[i] < x[j];
	}

	void calc(int i)
	{
        int k = gs[i];
        for (int j = gs[i]; j >= 0; j--)
		{
            while (x[pos[i][k-1]] > x[pos[i][j]] + 1)
				k--;
		}
	}

	void group()
	{
        for (int i = 0; i < gn; i++) 
			gs[i] = 0;
		gn = 0;
        for (int i = 0; i < n; i++)
		{
			gp[ci[i]] = i/sz;
            pos[gp[ci[i]]][gs[i/sz]]=ci[i];
			gn=i/sz+1;   
			gs[i/sz]++;
		}
		for (int i = 0; i < gn; i++)
		{
			calc(i);
		}
	}

	void init(int N, int L, int X[])
	{
        l = L;
	    n = N;
        for (int i = 0; i < N; i++)
		{
			x[i] = X[i];
			ci[i] = i;
		}
        sort(ci, ci + N, compare);
		group();
	}
}