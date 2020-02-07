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
 
namespace crocodile_tree
{ 
    #define MAX 1001
	vector<pair<int, int>> tree[MAX];

	int dfs(int s) 
	{
		if (tree[s].empty()) return 0;
		int best = INT_MAX, second = INT_MAX;
		for (int i = 0; i < tree[s].size(); i++) {
			int res = dfs(tree[s][i].first) + tree[s][i].second;
			if (res < best) {
                second = best;
                best = res;
			} else if (res < second) {
				second = res;
			}
		}
		return second;
	}

    int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
	{
		int s, t, len;
		for (int i = 0; i < M; i++) {
           s = R[i][0], t = R[i][1], len = L[i];
		   tree[s].push_back(make_pair(t, len));
		}   
		return dfs(0);
	}
}