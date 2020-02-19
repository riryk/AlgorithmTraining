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
 
namespace race
{ 
	#define MAXN 200050
	#define MAXK 1000050

	int N,K;
	int global_answer;
    int H[MAXN][2];
    int L[MAXN]; 
    
	int book_keeping;
	int split_node, current_max;
	int processed[MAXN];
	int size[MAXN];
	int achievable[MAXK];
    int minimum_paths[MAXK];

	vector<pair<int, int>> neighbours[MAXN];
    
	void calc_size(int current, int parent)
	{
        size[current] = 0;
        for (int i = 0; i < neighbours[current].size(); i++)
		{
			int c = neighbours[current][i].first;
			if (!processed[c] && c != parent)
			{
                calc_size(c, current);
				size[current] += 1 + size[c];
			}
		}
	}
    
	void select_split_node(int current, int parent, int total)
	{
        int node_max = total - size[current] - 1;
        for (int i = 0; i < neighbours[current].size(); i++)
		{
			int c = neighbours[current][i].first;
			if (!processed[c] && c != parent)
			{
                select_split_node(c, current, total);
				node_max = max(node_max, size[c]);
			}
		}

		if (node_max < current_max)
		{
            split_node = current;
			current_max = node_max;
		}
	}

	void dfs_calculate_path(int current, int parent, int current_cost, int current_length)
	{
		if (current_cost > K) return;

		if (achievable[current_cost] < book_keeping)
		{
            achievable[current_cost] = book_keeping;
			minimum_paths[current_cost] = current_length;
		}
		else if (current_length < minimum_paths[current_cost])
		{
            achievable[current_cost] = book_keeping;
            minimum_paths[current_cost] = current_length;
		}

        for (int i = 0; i < neighbours[split_node].size(); i++)
		{
            int child = neighbours[current][i].first;
            int len_to_child = neighbours[current][i].second;
			if (!processed[child] && child != parent)
			{
                dfs_calculate_path(child, current, current_cost + len_to_child, current_length + 1);
			}
		}
	}

    void dfs_calculate_min_path(int current, int parent, int current_cost, int current_length)
	{
		if (current_cost > K) return;

        for (int i = 0; i < neighbours[split_node].size(); i++)
		{
            int child = neighbours[current][i].first;
            int len_to_child = neighbours[current][i].second;
			if (!processed[child] && child != parent)
			{
                dfs_calculate_min_path(child, current, current_cost + len_to_child, current_length + 1);
			}
		}
	} 

	void process(int current)
	{
        calc_size(current, -1);
		if (size[current] <= 1) return;
        
		split_node = -1;
        current_max = size[current] + 3;
        select_split_node(current, -1, size[current] + 1);

        book_keeping++;
		for (int i = 0; i < neighbours[split_node].size(); i++)
		{
            int child = neighbours[current][i].first;
			int len_to_child = neighbours[current][i].second;
			if (!processed[child])
			{
                dfs_calculate_path(child, split_node, len_to_child, 1);
				dfs_calculate_min_path(child, split_node, len_to_child, 1);
			}
		}
	}

	int best_path(int NN, int KK, int H[][2], int L[])
	{
        N = NN, K = KK;
        for (int i = 0; i < N - 1; i++)
		{
			neighbours[H[i][0]].push_back(make_pair(H[i][1], L[i]));
            neighbours[H[i][1]].push_back(make_pair(H[i][0], L[i]));
		}
		global_answer = -1;
        process(0);
        return global_answer;
	}

    void read_input()
	{
        scanf("%d %d", &N, &K);
	    for (int i = 0; i < N-1; i++)
          scanf("%d %d %d", &H[i][0], &H[i][1], &L[i]);        
	}

    int main()
    {
	    int ans;
	    read_input();
	    ans = best_path(N, K, H, L);
	    return 0;
    }
}