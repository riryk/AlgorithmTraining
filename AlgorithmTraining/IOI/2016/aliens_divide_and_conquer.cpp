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
#include "aliens.h"

using namespace System;
using namespace std;

typedef long long ll;

namespace aliens
{
   int n, m, k;
   vector<int> r, c, le, ri;
   int SA[5000];
   ll dp[5000][5000];
   
   ll getCost(int i, int j)
   {
      ll w = ri[j]-le[i]+1;
      ll res = w*w;
	  if (j != n-1)
	  {
         ll sw = ri[j]-le[j+1]+1;
         if (sw > 0)
		    res -= sw*sw;
	  }
	  return res;
   }

   int compare(int i, int j)
   {
      if (r[i] == r[j]) return c[i] > c[j];
	  return r[i] < r[j];
   }

   void computeDP(int i, int l, int r, int optl, int optr) 
   {
      if (r < l) return;
      int m = (l + r) / 2;

	  int opt = -1;
      dp[m][i] = 1e18;

	  for (int j = optl; j < min(optr+1,m); j++)
	  {
         ll ndp = dp[j][i-1] + getCost(j,m-1);
		 if (ndp < dp[m][i])
		 {
			 dp[m][i] = ndp;
             opt = j;
		 }
	  }

      computeDP(i, l, m-1, optl, opt);
      computeDP(i, m+1, r, opt, optr);
   }

   ll take_photos(int _n, int _m, int _k, vector<int> _r, vector<int> _c) 
   {
      n=_n; 
	  m=_m; 
	  k=_k; 
	  r=_r; 
	  c=_c;

	  for (int i = 0; i < n; i++) if (c[i] < r[i]) swap(c[i], r[i]);
      for (int i = 0; i < n; i++) SA[i] = i;
      
	  sort(SA, SA + n, compare);
      
	  ll mxr = -1;

      for (int i = 0; i < n; i++)
	  {
	     if (c[SA[i]] <= mxr) continue;
		 le.push_back(r[SA[i]]);
		 ri.push_back(c[SA[i]]);
         mxr = c[SA[i]];
	  }

      n = le.size();

	  for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
	       dp[i][j] = 1e18;

	  if (k > n) k = n;
	  for (int i = 0; i <= n; i++) dp[i][0] = 1e18;
      for (int i = 0; i <= k; i++) dp[0][i] = 0;

      for (int i = 1; i <= k + 1; i++) computeDP(i,1,n,0,n-1);
      
	  return (ll)0;
   }
}

