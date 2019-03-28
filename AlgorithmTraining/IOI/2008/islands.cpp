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
int deg[N];

void islands()
{
	scanf("%d", in);
	for (int i = 1; i <= in; i++)
	{
        long long v, w;
		scanf("%lld%lld", &v, &w);
		par[i] = pll(v, w);
		deg[i]++;
	}
	deque<int> Q;
	for (int i = 1; i <= in; i++) if (!deg[i]) Q.push_back(i);
	while(!Q.empty())
	{
		int now = Q.front();
		Q.pop_front();
	}
}
