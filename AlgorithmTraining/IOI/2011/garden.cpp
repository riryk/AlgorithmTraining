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
 
namespace garden
{ 
	int f[300001];
	vector<int> graph[300001];

	void count_routes(int N, int M, in P, int R[][2], int Q, int G[])
	{
        for (int i = 0; i < 2 * N; i++) f[i] = -1;

		for (int i = 0; i < M; i++) {
			graph[R[i][0]].push_back(i);
            graph[R[i][1]].push_back(i);
		}    

		for (int i = 0; i < N; i++) {
			int e = graph[i][0];
			int to = R[e][0] + R[e][1] - i;
			if (graph[to][0] == e) 
              f[2*i] = 2*to + 1;
			else
              f[2*i] = 2*to;
			if (graph[i].size() >= 2) {
              int e = graph[i][1];
			  int to = R[e][0] + R[e][1] - i;
			  if (graph[to][0] == e)
                f[2*i + 1] = 2*to + 1;
			  else
                f[2*i + 1] = 2*to;
			}else if (graph[i].size() == 1) {
              f[2*i + 1] = f[2*i];
			}
		}  
	}
}