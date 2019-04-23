#include "stdafx.h"
#include "islands.h"
#include <vector>  
#include <deque>
#include <algorithm> 
#include <errno.h>
#include <math.h>  

using namespace System;
using namespace std;

#define pll pair<long long, long long>

const int N = 1e6 + 5;

int in;
pll par[N];
pll dp[N];
int deg[N];
long long dm[N];

long long islands_solve(int u) 
{
    long long ret; 
	vector<pll> V;
	deque<pll> Q;
	V.push_back(pll(0, 0));
	while (deg[u])
	{
       deg[u]--;
	   dm[u] = max(dm[u], dp[u].first + dp[u].second);
	   ret = max(ret, dm[u]);
	   V.push_back(pll(u, par[u].second));
	   u = par[u].first;
	}

	int sz = V.size() - 1;
	for (int i = 1; i <= sz; i++) V[i].second += V[i - 1].second;

	long long longest_subpath;
	for (int i = 2; i <= sz; i++) 
	{
		longest_subpath = V[i - 1].second + dp[V[i].first].first;
		while(!Q.empty() && Q.back().first < longest_subpath) Q.pop_back();
		Q.push_back(pll(longest_subpath, i));
	}

	ret = max(ret, dp[V[1].first].first + Q.front().first);

    for (int i = 1; i < sz; i++) 
	{
		if(Q.front().second == i + 1) Q.pop_front();
		longest_subpath = V[sz].second + V[i - 1].second + dp[V[i].first].first;
		while(!Q.empty() && Q.back().first < longest_subpath) Q.pop_back();
		Q.push_back(pll(longest_subpath, i));
		ret = max(ret, dp[V[i + 1].first].first + Q.front().first - V[i].second);
	}

	return ret;
}

void islands()
{
	scanf("%d", in);
	for (int i = 1; i <= in; i++)
	{
        long long v, w;
		scanf("%lld%lld", &v, &w);
		par[i] = pll(v, w);
		deg[v]++;
	}
	deque<int> Q;
	for (int i = 1; i <= in; i++) if (!deg[i]) Q.push_back(i);
	while(!Q.empty())
	{
		int now = Q.front();
		Q.pop_front();

		long long p = par[now].first, w = par[now].second;
		dm[now] = max(dm[now], dp[now].first + dp[now].second);
		dm[p] = max(dm[p], dm[now]);
 
		long long ret = dp[now].first + w;
		if(ret > dp[p].first) swap(ret, dp[p].first);
		if(ret > dp[p].second) swap(ret, dp[p].second);

		if (!--deg[par[now].first]) Q.push_back(par[now].first);
	}

	long long ans = 0;
	for(int i = 1; i <= in; i++) if(deg[i]) ans += islands_solve(i);
}
