#include "stdafx.h"
#include "hill.h"
#include <vector>  
#include <deque>
#include <algorithm> 
#include <errno.h>
#include <math.h>  
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include "regions.h"

using namespace System;
using namespace std;

namespace regions
{
    struct node
	{
		int id;
        int region;
		vector<int> children;
	};

	struct region
	{
		vector<int> ids;
        vector<pair<int, int>> ranges;
		int depth;

		region() : ids(), ranges(), depth(0) {}
	};

	int N, R, Q;
	vector<node> nodes;
	vector<region> regions;
    
	void process_tree(int root, int &id_pool)
	{
        int id = id_pool++;
		int r = nodes[root].region;

        regions[r].ids.push_back(id);
        regions[r].depth++;
        regions[r].ranges.push_back(make_pair(id_pool, regions[r].depth));

		for (size_t i = 0; i < nodes[root].children.size(); i++)
		{
            process_tree(nodes[root].children[i], id_pool);
		}

        regions[r].depth--;
        regions[r].ranges.push_back(make_pair(id_pool, regions[r].depth));
	}

	long long query_by_range(region &r1, region &r2)
	{
        long long ans = 0;
		for (size_t i = 0; i + 1 < r1.ranges.size(); i++)
		{
            int pos1 = r1.ranges[i].first;
			int pos2 = r1.ranges[i + 1].first;
            long long depth = r1.ranges[i].second;
            
			vector<int>::const_iterator first, last;
            first = lower_bound(r2.ids.begin(), r2.ids.end(), pos1);
            last = lower_bound(r2.ids.begin(), r2.ids.end(), pos2);
            ans += depth * (last - first);
		}
		return ans;
	}

	void solve()
	{
		// scanf("%d %d %d", &N, &R, &Q);
        N = 6;
		R = 3;
		Q = 4;

        nodes.resize(N);
		regions.resize(R);

		// scanf("%d", &nodes[0].region);
        nodes[0].region = 0;

        nodes[1].region = 1;
		nodes[0].children.push_back(1);

		nodes[2].region = 2;
        nodes[0].children.push_back(2);

		nodes[3].region = 2;
        nodes[2].children.push_back(3);

		nodes[4].region = 2;
        nodes[2].children.push_back(4);

		nodes[5].region = 0;
        nodes[4].children.push_back(5);

		/*
		for (int i = 1; i < N; i++)
		{
            int parent;
            scanf("%d %d", &parent, &nodes[i].region);
			parent--;
            nodes[i].region--;
			nodes[parent].children.push_back(i);
		}*/


		int id_pool = 0;
        process_tree(0, id_pool);
	}
}