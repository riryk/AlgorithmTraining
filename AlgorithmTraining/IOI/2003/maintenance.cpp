#include "stdafx.h"
#include <vector>  
#include <errno.h>
#include <math.h>  
#include <algorithm> 
#include <set>

using namespace System;
using namespace std;
 
namespace maintenance
{ 
   struct edge
   {
	   int u,v,w;
       bool operator < (const edge &e) const
	   {
		   return w < e.w;
	   }
   };

   const int MAXV = 200;

   int V,E;
   int u,v,w;
   int P[MAXV];

   multiset<edge> S;
   multiset<edge>::iterator it,tmp;
   
   int find(int x)
   {
	   while(P[x]!=x) P[x]=find(P[x]);
	   return P[x];
   }

   void unite(int x, int y)
   {
       int py = find(y);
	   int px = find(x);
	   P[py] = px;
   }
    
   void solve()
   {
	   scanf("%d %d", &V,&E);
       while (E--)
	   {
		   scanf("%d %d %d", &u,&v,&w);
		   u--;v--;
		   int mst = 0;
		   for (int i = 0; i< V; i++) 
			   P[i] = i;

		   struct edge item;
		   item.u = u;
		   item.v = v;
		   item.w = w;

		   S.insert(item);
		   for (it=S.begin(); it != S.end();)
		   {
			   int u = (*it).u;
			   int v = (*it).v;
			   int w = (*it).w;
               if (find(u) != find(v))
			   {
				   unite(u,v);
				   mst += w;
                   it++;
			   }
			   else
			   {
                   tmp = it;
				   it++;
				   S.erase(tmp);
			   }
		   }
	   }
   }
}