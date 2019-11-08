#include "stdafx.h"
#include <vector>  
#include <errno.h>
#include <math.h>  
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace System;
using namespace std;
 
namespace rivers
{ 
   int n, k, a, c;
   int T[103];
   int D[103];
   int s[103];
   int b[103];
   vector<pair<int, int>> E[103];
   int saving[103][103];
   int totalCost = 0;

   void dfs_reprocess(int node, int d) {
       D[node] = d;
	   for (int i = 0; i < E[node].size(); i++) {
		   dfs_reprocess(E[node][i].first, d + E[node][i].second);
           T[i] += T[E[node][i].first];
		   totalCost += T[E[node][i].first] * E[node][i].second;
	   }
	   if (E[node].size() > 0) 
		   s[node] = E[node][0].first;
       for (int i = 1; i < E[node].size(); i++)
           b[E[node][i - 1].first] = E[node][i].first;
   }

   void solve()
   {
	   cin >> n >> k;
	   for (int i = 1; i <= n; i++) {
          cin >> T[i] >> a >> c;
		  E[a].push_back(make_pair(i, c));
	   }
       dfs_reprocess(0, 0);
	   for( int i = 0; i <= n; i++ )
		  for( int j = 0; j <= n; j++ )
			saving[i][j] = T[i] * (D[i] - D[j]);
   }
}