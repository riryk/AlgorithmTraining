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
#include "dreaming.h"

using namespace System;
using namespace std;
 
namespace dreaming
{
	typedef pair<int,int> edge;

	vector<edge> graph[10000];
    int visited[10000];

	int maxdist;
	int at;
	
	void dfs(int u, int parent, int dist) 
	{
        if (dist > maxdist)
		{
			maxdist = dist;
		    at = u;
		}
		for (int i = 0; i < graph[u].size(); i++)
		{
			int c = graph[u][i].first;
			if (c != parent)
			{
				dfs(c, u, dist + graph[u][i].second);
			}
		}
	}

	int travelTime(int N, int M, int L, int A[], int B[], int T[])
	{
        for (int i = 0; i < M; i++)
		{
			graph[A[i]].push_back(make_pair(B[i], T[i]));
            graph[B[i]].push_back(make_pair(A[i], T[i]));
		}

		for (int i = 0; i < N; i++)
		{
            if (visited[i]) continue;
			maxdist = -1;
			dfs(i, i, 0);
			int one = at;
		}

		return 0;
	}
}