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
#include "wall.h"

using namespace System;
using namespace std;
 
namespace wall
{
	pair<int, int> segt[8000001];
	pair<int, int> lazy[8000001];

    pair<int, int> implement(pair<int, int> o, pair<int, int> n)
    {
       if (o == make_pair(8000001,0))
	   {
           return n;
	   }
	   else if (n == make_pair(8000001,0))
	   {
           return o;
	   }

	   if (o.second <= n.first)
	   {
		   return make_pair(n.first, n.first);
	   }

	   if (o.second >= n.first && o.first <= n.first && n.second >= o.second)
	   {
		   return make_pair(n.first, o.second);
	   }

	   if (n.first >= o.first && n.second <= o.second)
	   {
           return n;
	   }

	   if (o.first >= n.first && o.second <= n.second)
	   {
           return o;
	   }

	   if (o.first >= n.first && o.second >= n.second && n.second >= o.first)
	   {
		   return make_pair(o.first, n.second);
	   }

	   if (o.first >= n.second)
	   {
		   return make_pair(n.second, n.second);
	   }
	}
    
	void up(int node, int l, int r, int t, int s, int e, int h)
	{
       if (lazy[node] != make_pair(8000001, 0))
	   {
           segt[node] = implement(segt[node], lazy[node]);
           lazy[2*node+1] = implement(lazy[2*node+1], lazy[node]);
           lazy[2*node+2] = implement(lazy[2*node+2], lazy[node]);
           lazy[node] = make_pair(8000001, 0);
	   }

       if (l > e || r < s)
	   {
           return;
	   }

	   if (l >= s && r <= e)
	   {
		   pair<int, int> p = t == 1 ? make_pair(h, 1000000) : make_pair(0, h);
           segt[node] = implement(segt[node], p); 
           lazy[2*node+1] = implement(lazy[2*node+1], p);
           lazy[2*node+2] = implement(lazy[2*node+2], p);
		   return;
	   }

	   int mid = (l+r)>>1;

       up(2*node + 1, l, mid, t, s, e, h);
       up(2*node + 2, mid + 1, r, t, s, e, h);

	   int left = min(segt[2*node + 1].first, segt[2*node + 2].first);
	   int right = max(segt[2*node + 1].second, segt[2*node + 2].second);
       
	   segt[node] = make_pair(left, right);
	}

    pair<int, int> qu(int node, int l, int r, int s, int e)
	{
       if (lazy[node] != make_pair(8000001, 0))
	   {
           segt[node] = implement(segt[node], lazy[node]);
           lazy[2*node+1] = implement(lazy[2*node+1], lazy[node]);
           lazy[2*node+2] = implement(lazy[2*node+2], lazy[node]);
           lazy[node] = make_pair(8000001, 0);
	   }
       
	   if (l > e || r < s)
	   {
		   return make_pair(8000001, 0);
	   }

	   if (l >= s && r <= e)
	   {
		   return segt[node];
	   }

       int mid = (l+r)>>1;

       pair<int, int> left = qu(2*node + 1, l, mid, s, e);
       pair<int, int> right = qu(2*node + 2, mid + 1, r, s, e);

	   return make_pair(
		   min(segt[2*node + 1].first, segt[2*node + 2].first), 
		   max(segt[2*node + 1].second, segt[2*node + 2].second));
	}

	void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[])
	{
       for (int i = 0; i < 8000001; i++)
	   {
           lazy[i] = make_pair(8000001, 0);
           segt[i] = make_pair(8000001, 0);
	   }

	   for (int i = 0; i < k; i++)
	   {
           up(0, 0, n - 1, op[i], left[i], right[i], height[i]);
	   }

       for (int i = 0; i < n; i++)
	   {
		   finalHeight[i] = qu(0, 0, n - 1, i, i).first;

		   if (finalHeight[i] == 8000001)
		   {
               finalHeight[i] = 0;
		   }
	   }
	}
}

