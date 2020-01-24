#include "stdafx.h"
#include <vector>  
#include <deque>
#include <algorithm> 
#include <errno.h>
#include <math.h>  
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <queue>

using namespace System;
using namespace std;

namespace saveit
{
    int n;
    vector<int> edge[1000];
	int inf = (int)1e5;
    int dist[36][1000];
    int pr[36][1000];

	void encode_bit(int bit){ }
	int decode_bit() { return 1; }
	void hops(int h, int i, int dist) { }

	void bfs(int dist[], int pr[], int s) {
        for (int i = 0; i < n; i++) dist[i] = inf;
		dist[s] = 0;
        queue<int> q;
		q.push(s);
		while(!q.empty()){
			int v = q.front(); q.pop();
			for (int i = 0; i< edge[v].size(); i++) {
				int u = edge[v][i];
				if (dist[u] < inf) continue;
				dist[u] = dist[v] + 1;
				pr[u] = v;
				q.push(u);
			}
		}
	}
    
	struct eencoder {
		unsigned int x,c;
		eencoder():x(0),c(0){}
		void encode(int i) {
			if (c == 20) {
                for (int j = 32; j--; )
					encode_bit((x>>j) & 1u);
				x = c = 0;
			}
            x = 3u * x + (unsigned int)i, 
		    ++c;           
		}
		void flush() {
            while (c != 1) encode(0);
		}
	};

	typedef struct eencoder encoder;

    void encode(int N, int H, int M, int * A, int * B) {
        n = N;
		for (int i = 0; i < N; i++) {
			edge[A[i]].push_back(B[i]);
            edge[B[i]].push_back(A[i]);
		}
		for (int i = 0; i < H; i++) bfs(dist[i], pr[i], i); 
        for (int i = 0; i < N; i++)
			for (int j = 10; j >= 0; j--)
                encode_bit((pr[0][i]>>j)|1);

		encoder e;
		for (int i = 0; i < H; i++){
			for (int j = 0; j < N; j++){
				int x = dist[i][j] - dist[i][pr[0][j]] + 1;
                e.encode(x);
			}
		}
		e.flush();
    }
    
	int d[1000];
	int dist1[1000];
	vector<int> edge1[1000];

	void dfs(int s) 
	{
        for (int i = 0; i < edge1[s].size(); i++)
		{
		   int u = edge1[s][i];
           dist1[u] = dist1[s] + d[u];
		   dfs(u);
		}
	}
    
    struct decoder
	{
		int x[20], c;
        decoder() : c(20) {}
		int decode_num() {
		   return 0;
		}
	};

	void decode(int N, int H) 
	{
		for (int i = 0; i < N; i++){
           int x = 0;
		   for (int j = 0; j < 10; j++){
			   x <<= 1;
			   x |= decode_bit();
		   }
		   d[i] = 1;
		   edge1[x].push_back(i);
		}
		dist1[0]=0;
		dfs(0);
		for (int i = 0; i < N; ++i) hops(0, i, dist1[i]);

		decoder dc;
        for (int i = 1; i < H; ++i) {
		   for (int j = 1; j < N; ++j) {
              d[j] = dc.decode_num() - 1;
		   }
		   dfs(0);
		   for (int j = 0; j < N; ++j) hops(i, j, dist[j] - dist[i]);
		}
	}
}