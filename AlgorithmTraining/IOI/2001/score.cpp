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
			if (a){
				if (B[x] == 1) {
                    Max1[x] = max(a, V[x]);
                    Max2[x] = b;
				}
				else {
                    Max1[x] = a;
                    Max2[x] = max(b, V[x]);
                }
			}
			else {
				if (B[x] == 1) {
                    Max1[x] = max(c, V[x]);
                    Max2[x] = d;
				}
				else {
                    Max1[x] = c;
                    Max2[x] = max(d, V[x]);
				}
			}
		}
	}

	int find(int x)
    {
        int maxi(0),a,i,mini(123123123),b,t;

        for (i=0; i<=(int)G[x].size(); i++)
		{
             t = G[x][i];
             if (Max1[t] > Max2[t] && Max1[t] > maxi)
             {
                 maxi = Max1[t];
                 a = i;
             }
             if (Max2[t] < mini)
             {
                 mini = Max2[t];
                 b = i;
             }
		}

		return maxi ? G[x][a] : G[x][b];
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