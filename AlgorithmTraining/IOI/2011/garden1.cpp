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
 
namespace garden1
{ 
    vector<int> original[150005];
    vector<int> adjList[300005];

	void build_graph(int N)
	{
		for (int u = 0; u < N; u++) {
            int v = original[u][0]; // principal edge 
			if (original[v][0] != u || original[v].size() == 1) {
				adjList[v].push_back(u);
			} else {
                adjList[v+N].push_back(u);
			}
			if (original[u].size() == 1) continue;
            int v = original[u][1]; // secondary edge
            if (original[v][0] != u || original[v].size() == 1) {
				adjList[v].push_back(u+N);
			} else {
                adjList[v+N].push_back(u+N);
			}
		}        
	}

	void count_routes(int N, int M, int P, int R[][2], int Q, int G[])
    {
		for (int i = 0; i < M; i++) {
            int u = R[i][0];
			int v = R[i][1];
			original[u].push_back(v);
            original[v].push_back(u);
		}

		build_graph(N);
	}
}