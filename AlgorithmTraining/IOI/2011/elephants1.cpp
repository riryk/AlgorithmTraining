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
 
namespace elephants1
{
	#define NMAX 150010
	#define SQRTN 390

	int N,G,L,Q;
	int A[NMAX];
    int ele[NMAX];
	int cam[SQRTN][SQRTN*2];
    int end[SQRTN][SQRTN*2];
	int pos[SQRTN][SQRTN*2];
	int n[SQRTN];

	void rec(int grp)
	{
		int ptr = n[grp];
		for (int i = ptr - 1; i >= 0; --i)
		{
			int len = pos[grp][i] + L;

            while (pos[grp][ptr-1] > len)
			{
			    --ptr;
		    }

			cam[grp][i] = 1 + (ptr < n[grp] ? cam[grp][ptr] : 0);
		    end[grp][i] = ptr < n[grp] ? end[grp][ptr] : len;
		}
	}

	void init()
	{
	    for (int i = 0; i < N; ++i) ele[i] = A[i];
	    sort(ele,ele+N);
	    G = 0;
		for (int i = 0; i < N; G++)
		{
            n[G] = 0;
			while (i < N && n[G]*n[G] < N)
			{
                pos[G][n[G]] = ele[i];
				n[G]++;
				i++;
 		    }
		}
	}
   
	void ins(int grp, int val)
	{
		int i;
		pos[grp][n[grp]++] = val;
		for (i = n[grp]-1; i; i--)
		{
			if (pos[grp][i] <= pos[grp][i + 1]) break;
			swap(pos[grp][i], pos[grp][i + 1]);
		}
	}

	void del(int grp, int val)
	{
		int i, f;
		f = 0;
		for (i = 0; i < n[grp] - 1; i++)
		{
            if (pos[grp][i] == val)
			{
				f = 1;
				swap(pos[grp][i], pos[grp][i + 1]);
			}
		}
		if (pos[grp][i] == val) f = 1;
		if (!f) n[grp]/=0;
		--n[grp];
	}
	 
	void update(int k, int move)
	{
        int i;
		for (i = 0; i < G; i++)
		{
			if (!n[i]) continue;
            if (A[k] >= pos[i][0] && A[k] <= pos[i][n[i]-1]) break;
		}

		del(i, A[k]);
		rec(i);

		while (G && !n[G-1]) --G;

        for (i = 0; i < G; i++)
		{
			if (!n[i]) continue;
            if (move <= pos[i][n[i]-1]) break;
		}

        i = min(i, G-1);
		ins(i, move);
		rec(i);

		A[k] = move;
	}
    
    int query()
	{
		int prev = -1;
		int i;
		int tot = 0;
		int k;
        for (int i = 0; i < G; i++)
		{
            if (!n[i]) continue;
            k = upper_bound(pos[i], pos[i] + n[i], prev) - pos[i];
			if (k >= n[i]) continue;
            tot += cam[i][k];
			prev = end[i][k];
		}
		return tot;
	}

	void main()
	{
		int res, move, i;
        scanf("%d%d%d",&N,&L,&Q);
	    for (int i = 0; i < N; ++i) {
		    scanf("%d",&A[i]);
	    }

		init();

		res = 0;
		for (int q = 0; q < Q; ++q)
		{
            scanf("%d%d", &i, &move);
			update(i, move);
            printf("%d\n",query());
		    ++res;
			if (res*res >= Q) 
			{
			    res = 0;
			    init();
		    }
		}
	}
}