#include "stdafx.h"
#include <vector>  
#include <deque>
#include <algorithm> 
#include <errno.h>
#include <math.h>  
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace System;
using namespace std;
 
namespace farmer
{ 
   int N,K,Q;
   int cyc[150010];
   int path[150010];
   int dp[2010][2];

   int compute()
   {
	   int i,b,q;

       dp[0][0] = 1;
	   dp[cyc[0]][0] = 1;

	   for (int i = 1; i < N; i++)
	   {
		   b = i&1;
           for (int q = 0; q <= Q; q++)
		   {
               dp[q][b] = dp[q][!b];
               if (cyc[i] <= q)
			   {
				   dp[q][b] |= dp[q-cyc[i]][!b];
			   }
		   }
	   }

       b = (N-1)&1;
	   return dp[Q][b];
   }

   int main()
   {
      int sum, i, tot;

      scanf("%d%d%d", &Q, &N, &K);
      
      sum = 0;
	  for (i = 0; i < N; i++)
	  {
		  scanf("%d", &cyc[i]);
		  sum += cyc[i];
	  }

      for (i = 0; i < K; i++)
	  {
          scanf("%d", &path[i]);
	  }

      sort(path,path+K);

      
   }  
}