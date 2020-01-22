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

namespace traffic
{
   #define NMAX 1000010
   
   int N;
   int total;
   int weight[NMAX];
   int size[NMAX];
   vector<int> adj[NMAX];
   
   pair<int, int> dfs(int v, int p)
   {
	   int con;
	   pair<int,int> best;

       size[v]=weight[v];
	   best = make_pair(total,v);
       con = 0;

	   for(int i = 0; i < adj[v].size(); i++)
	   {
		   int c = adj[v][i];
		   if (c == p) continue;
		   best = min(best, dfs(c, v));
		   size[v] += size[c];
		   con = max(con, size[c]);
	   }

	   con = max(con, total-size[v]);
       
	   return min(best, make_pair(con,v));
   }

   void main()
   {
	   int i,j;
       scanf("%d", &N);
	   for(i = 0; i< N; i++)
	   {
		   scanf("%d", &weight[i]);
		   total += weight[i];
	   }

	   while(--N)
	   {
           scanf("%d%d", &i, &j);
		   adj[i].push_back(j);
		   adj[j].push_back(i);
	   }
   }
}