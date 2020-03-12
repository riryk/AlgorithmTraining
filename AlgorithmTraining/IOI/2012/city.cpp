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
#include <map>
#include <utility>
#include "crayfish.h"

using namespace System;
using namespace std;
 
namespace city
{ 
	#define MOD 1000000000
	#define MAX_VL (8)

	typedef long long int lld;
    typedef pair<int, int> pii;
    typedef pair<int, pii> triple;
    
    struct node
	{
		int weight;
		int index;
		node* parent;
		vector<node*> children;
	}

	typedef node;

	node* root_h, root_v;

	int list_h[100050];
    int list_v[100050];
    int tree_indexes;

    triple positions_x[100050];
    triple positions_y[100050];
	map<lld, int> positions;

	vector<int> graph[100050];
	int weight[100050];
    int visited[100050];
	lld sum[100050];

    void dfs(node *cur, int vertex)
	{
		cur->weight = weight[vertex];
		cur->index = tree_indexes++;
		visited[vertex] = 1;
		for (int i = 0; i < (int)graph[vertex].size(); i++)
		{
			int c = graph[vertex][i];
			if (!visited[c])
			{
                node *child = new node();
				child->parent = cur;
				cur->children.push_back(child);
				dfs(child, c);
			}
		}
	}

    void calc_sum(node* cur)
	{
		int s = cur->weight;
		for (int i = 0; i < (int)cur->children.size(); i++)
		{
			calc_sum(cur->children[i]);
			s += sum[cur->children[i]->index];
		}
		sum[cur->index] = s;
	}

    int distanceSum(int n, int* x, int *y)
    {
        for (int i = 0; i < n; i++)
		{
            positions_x[i] = triple(x[i], make_pair(y[i], i));
            positions_y[i] = triple(y[i], make_pair(x[i], i));
			positions[MAX_VL * y[i] + x[i]] = i;
		}

		sort(positions_x, positions_x + n);
        sort(positions_y, positions_y + n);

        for (int i = 0; i < n; i++)
		{
			graph[i].clear();
			weight[i] = 0;
		}

		int num_nodes = 1;
		int first_i = positions_x[0].second.second;

		list_h[first_i] = 0;
		weight[0] = 1;

        for (int i = 1; i < n; i++)
		{
			int prev_x = positions_x[i - 1].first;
			int prev_y = positions_x[i - 1].second.first;
            int prev_i = positions_x[i - 1].second.second;

			int curr_x = positions_x[i].first;
			int curr_y = positions_x[i].second.first;
            int curr_i = positions_x[i].second.second;

			if (prev_x == curr_x && curr_y == prev_y + 1)
			{
                weight[list_h[prev_i]]++;
                list_h[curr_i] = list_h[prev_i]; 
			}
			else
			{
			    weight[num_nodes] = 1;
				list_h[curr_i] = num_nodes++;
			}

			int prev_code = MAX_VL * curr_y + curr_x - 1;
            if (positions.find(prev_code) != positions.end())
			{
				int prev_group_i = list_h[positions[prev_code]];
                int curr_group_i = list_h[curr_i];

				graph[curr_group_i].push_back(prev_group_i);
                graph[prev_group_i].push_back(curr_group_i);
			}
		}

		tree_indexes = 0;
		root_h = new node();
        memset(visited, 0, sizeof(visited));

		dfs(root_h, 0);

		memset(sum, 0, sizeof(sum));
		calc_sum(root_h);

		lld tsum = sum[0];
		lld ans = 0;

		for (int i = 1; i < tree_indexes; i++)
		{
            ans += (sum[i] * (tsum - sum[i])) % MOD;
		}

		return ans;
    }

	void test()
	{
        int* xx = (int*)malloc(6*sizeof(int));
        int* yy = (int*)malloc(6*sizeof(int));

		xx[0] = 0;
		yy[0] = 0;

        xx[1] = 0;
		yy[1] = 1;

        xx[2] = 0;
		yy[2] = 2;
        
        xx[3] = 1;
		yy[3] = 0;

        xx[4] = 1;
		yy[4] = 1;

        xx[5] = 1;
		yy[5] = 2;

		int sum = distanceSum(6, xx, yy);
	}
}