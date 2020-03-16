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
#include <map>
#include <utility>
#include "crayfish.h"

using namespace System;
using namespace std;
 
namespace tournament
{ 
	typedef pair<int,int> PII;

    const int N = 100005;

	int Rank, n;
    int p[N];
    int fw[N];
	int L[N];
	int R[N];
	int* num;
    set<pair<PII, int>> interval;    
	set<pair<PII, int>>::iterator it, it2;
    vector<int> g[N];
    int seg[N<<2];
	int dp[N];

	int fin(int i)
	{
	    if (p[i] == i) return i;
	    return p[i] = fin(p[i]);
    }

    void add(int a, int b)
	{
		while (a < N)
		{ 
		    fw[a] += b;
		    a += a&-a;
		}
    }

    int get(int a)
	{
	    int b = 0;
		while (a) 
		{
			b += fw[a]; 
			a -= a&-a;
		}
	    return b;
    }

	int bs(int a)
	{
        int l = 0; 
		int r = N-1;
        while (l < r)
		{
           int m = (l+r)>>1;
           if (get(m) < a) l = m+1;
           else r = m;
        }
        return l;
    }
    
	void findTournamentBoundaries(int c, int *S, int *E)
	{
        for (int i = 0; i < c; i++)
		{
			int l = bs(S[i] + 1);
            int r = bs(E[i] + 1);
			L[i] = bs(S[i]) + 1;
            R[i] = r;
            for (int j = l; j < r; j = fin(j + 1))
			{
				add(j, -1);
                p[j] = fin(j + 1);
			}
		}
	}

    void buildTournamentTree(int c)
	{
        for (int i = 0; i < c; i++)
		{
			it = interval.lower_bound(make_pair<PII,int>(make_pair<int,int>(L[i],0),0));
			while (it != interval.end() && it->first.first >= L[i] && it->first.second <= R[i])
			{
                it2 = it;
                it++;
				g[i].push_back(it2->second);
				interval.erase(it2);
			}
			interval.insert(make_pair<PII,int>(make_pair<int,int>(L[i],R[i]),i));
		}
	}
    
	void buildSegmentTree(int l, int r, int now)
	{
        if (l == r)
		{
            seg[now] = num[l];
			return;
		}
        int mid = (l + r) >> 1;
        buildSegmentTree(l, mid, now << 1);
		buildSegmentTree(mid + 1, r, (now << 1)|1);
        seg[now] = max(seg[now << 1], seg[(now << 1)|1]);
	}

	int query(int ll, int rr, int l = 1, int r = n-1, int now = 1)
	{
        if (rr < l || ll > r) return 0;
		if (ll <= l && r <= rr) return seg[now];
		int mid = (l + r) >> 1;
		return max(
			query(ll, rr, l, mid, now << 1),
			query(ll, rr, mid + 1, r, (now << 1)|1));
	}

	void dfs(int u, int v)
	{
        bool can_win = query(L[u], R[u] - 1) < Rank;
        if (can_win) 
			dp[u] = dp[v] + 1;
		for (int i = 0; i < g[u].size(); i++)
			dfs(g[u][i], u);
	}

	int getBestPosition(int n1, int c, int r, int *K, int *S, int *E) 
	{
	    num = K;
	    n = n1;
	    Rank = r;
		for (int i = 1; i <= n+1; i++)
		{ 
			add(i, 1); 
			p[i] = i;
		}

		findTournamentBoundaries(c, S, E);
        buildTournamentTree(c);
        buildSegmentTree(1, n-1, 1);
        dfs(c-1, c);
        
		int ans = 0;
		for (int i = 0; i < c; i++)
		{
			if (!g[i].empty())
			{
				ans = max(ans, dp[i]);
			}
		}

		return ans;
	}

	void test()
	{
		int K[4] = { 1, 0, 2, 4 };
		int S[3] = { 1, 0, 0 };
        int E[3] = { 3, 1, 1 };

        int pos = getBestPosition(5, 3, 3, K, S, E);                         
	}
}