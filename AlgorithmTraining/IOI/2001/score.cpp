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
 
namespace score
{ 
    #define MAXN 1005
	#define FOR(i,a,b) for(i=a; i<=b; i++)

	vector<int> G[MAXN];
    int N;
    int B[MAXN], V[MAXN];
    int Max1[MAXN], Max2[MAXN];

	void rec(int x, int s)
	{
        if (x == 1 && s == 1) return;
		vector<int>::iterator it;
		for (it = G[x].begin(); it != G[x].end(); ++it)
			rec(*it, 1);

		int a(0),b,c,d(123123123);
		for (it = G[x].begin(); it != G[x].end(); ++it) {
			if (Max1[*it] > Max2[*it] && Max1[*it] > a) {
				a = Max1[*it];
				b = Max2[*it];
			}
			if (Max2[*it] < d) {
                d = Max2[*it];
				c = Max1[*it];
			}
		}
	}

    void solve()
    {
        int a,i,j;
        scanf("%d",&N);
        FOR(i,1,N)
        FOR(j,1,N)
        {
           scanf("%d",&a);
           if(a) G[i].push_back(j);
        }
     
        FOR(i,1,N) scanf("%d",B+i);
        FOR(i,1,N) scanf("%d",V+i);
     
        rec(1,0);
	}

    void main()
	{
        solve();
	}
}