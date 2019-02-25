#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>

using namespace System;
using namespace std;

const int N = 10;

int ns, t[N];
vector<pair<int, int>> V;

void update(int x, int v) 
{
	for(int i = x; i > 0; i -= i & -i)
	{ 
		t[i-1] += v;
	}
}
 
int query(int x, int v = 0) 
{
    for(int i = x; i <= N; i += i & -i)
	{
		v += t[i-1];
	}

    return v;
}

int getft(int x) 
{
    int l = 0, r = N;
    while(l < r) 
	{
        int m = (l + r + 1) >> 1;
        if (query(m) >= x) 
			l = m;
        else 
			r = m-1;
    }
    return l;
}

int findMinInefficiency()
{
   sort(V.begin(), V.end());

   for(int i = 0; i < V.size(); i++) 
   {
	   pair<int, int> x = V[i];
	   int h = x.first, k = x.second;
       int p = h - k;
	   update(h, 1);
	   if (!p) continue;
	   int pval = query(p);
       int lb = min(getft(pval), h);
       int rb = getft(pval + 1); 
       update(lb, -1);
	   update(rb, -1);
       update(lb + rb - (h - k), 1);
   }   
   
   long ans = 0;
   for(int i = 1; i <= N; ++i) ans += 1ll * query(i) * (query(i)-1) / 2;

   return ans;
}

void sails_test()
{
	ns = 6;

	V.push_back(make_pair(3, 2));
	V.push_back(make_pair(5, 3));
	V.push_back(make_pair(4, 1));
	V.push_back(make_pair(2, 1));
	V.push_back(make_pair(4, 3));
	V.push_back(make_pair(3, 2));
    
    findMinInefficiency();
}


/*

               -|
         -| -| -|
   -| -|  | -|  |
 |  | -|  |  | -|
-| -|  |  | -|  |

*/
