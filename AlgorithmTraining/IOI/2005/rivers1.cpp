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
   int n,k;
   int w[101];
   int p[101];
   int dist[101];
   vector<pair<int, int>> graph[101];
   
   void dfs(int x, int d)
   {
	   dist[x] = d;
	   for (int i = 0; i < (int)graph[x].size(); i++)
	   {
		   dfs(graph[x][i].second, d + 1);
	   }
   }

   int f(int x, int csub, int nearest, int left)
   {
	   int ret = 1e9;

	   if (csub == 0)
	   {
		   int first_child = graph[x][0].second;

           for (int i = 0; i < left; i++)
		   {
               ret = min(ret, f(first_child, 0, x, i) + f(x, 1, x, left - i - 1));    
		   }
	   }

	   return 1;
   }

   int main()
   {
	   scanf("%d %d", &n, &k);
       for (int i = 1; i <= n; i++)
	   { 
           int q;
           scanf("%d %d %d", &w[i], &p[i], &q);
		   graph[p[i]].push_back(make_pair(q,i));
	   }
       
	   dfs(0, 0);
       printf("%d", f(0,0,0,k));

	   return 0;
   }
}