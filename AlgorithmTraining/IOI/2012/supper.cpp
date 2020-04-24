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
 
namespace supper
{ 
	void compute_advise(int* c, int n, int k, int m)
	{
        vector<int> last(n, n);
        vector<int> nxt(n);

		for (int i = n - 1; i >= 0; i--)
		{
            nxt[i] = last[c[i]];
            last[c[i]] = i;
		}

		set<pair<int, int>> pq;
        vector<int> pos(n, -1);

		for (int i = 0; i < k; i++)
		{
			pq.insert(make_pair(last[i], i));
			pos[i] = i;
		}
	}

	void test()
	{
		int c[4] = { 2, 0, 3, 0 };
		int n = 4;
        int k = 2;
        int m = 2;

        compute_advise(c, n, k, m);
	}
}