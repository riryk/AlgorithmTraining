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

	void main()
	{
        scanf("%d%d%d",&N,&L,&Q);
	    for (int i = 0; i < N; ++i) {
		    scanf("%d",&A[i]);
	    }

		init();
	}
}