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
		dm[now] = max(dm[now], dp[now].first + dp[now].second);
		dm[par[now].first] = max(dp[par[now].first].first, dm[now]);
		long long path = dp[now].first + par[now].second;
		if (path > dp[par[now].first].first) swap(path, dp[par[now].first].first);
		if (path > dp[par[now].first].second) swap(path, dp[par[now].first].second);
		if (!--deg[par[now].first]) Q.push_back(par[now].first);
	}
}
