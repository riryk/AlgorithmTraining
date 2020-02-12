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
            v = original[u][1]; // secondary edge
            if (original[v][0] != u || original[v].size() == 1) {
				adjList[v].push_back(u+N);
			} else {
                adjList[v+N].push_back(u+N);
			}
		}        
	}
    
    int color[300005];
	int d[300005][2];
	int C[2]={-1,-1};
	int inCycle[2];
    int t = 0;

	void dfs(int u)
	{
        color[u] = 1;
		for (int i = 0; i < adjList[u].size(); i++) {
            int v = adjList[u][i];
			if (color[v] == 0) {
                d[v][t] = d[u][t] + 1;
				dfs(v);
			} 
			else if (color[v] == 1) {
                C[t] = d[u][t] + 1;
                inCycle[t] = 1;
			}
		}
		color[u] = -1;
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
        for (int i = 0; i < 2*N; i++) {
            d[i][0] = d[i][1] = 1000000000;
        }  
		d[P][0]=0;
		dfs(P);
		t++;
        for (int i = 0; i < 2*N; i++) {
			color[i] = 0;
		}
		d[P+N][1]=0;
		dfs(P+N);
		for (int i = 0; i < Q; i++) {
            int k = G[i];
            int total = 0;
			for (int u = 0; u < N; u++) {
				for (int j = 0; j < 2; j++) {
					if (d[u][j] == 1000000000) continue;
					if (inCycle[j]) {
                        int D = k-d[u][j];
                        if (D>=0) {
                          if (D%C[j]==0) total++;
                        }
					} else {
                        int D = k-d[u][j]; 
                        if (D == 0) total++;
                    }
				}
			}
		}
	}
}