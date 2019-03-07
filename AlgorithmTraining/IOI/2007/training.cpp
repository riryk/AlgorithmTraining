#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>

using namespace System;
using namespace std;

#define MAXN 1000 //max number of vertexes
#define MAXK 10   //max vertex degreee

struct Edge
{
   int u;
   int v;
   int cost;
   int LCA; // lowest common ancestor of u and v
} E[MAXN*MAXK];

int tn, tm;
int costSum;
vector<int> treeLinks[MAXN];

int traversalTime;
int discover[MAXN];
int finish[MAXN];
int degree[MAXN];
int depth[MAXN];
int color[MAXN];
pair<int, int> parent[MAXN];

int dp[MAXN][1<<MAXK]; // 1<<MAXK is number of subtrees of current tree

void load()
{
   costSum = 0;
   scanf("%d%d", &tn, &tm);
   for (int i = 0; i < tm ; i++)
   {
	   scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].cost);
       E[i].u--; E[i].v--;
	   if (E[i].cost == 0)
	   {
		   treeLinks[E[i].u].push_back(E[i].v);
           treeLinks[E[i].v].push_back(E[i].u);
	   }
   }
}

void treeInit(int a)
{
   discover[a] = ++traversalTime;
   for (vector<int>::iterator it = treeLinks[a].begin(); it <= treeLinks[a].end(); ++it)
   {
	   if (*it == parent[a].first) continue;
       depth[*it] = depth[a] + 1;
	   color[*it] = color[a] ^ 1;
	   degree[a]++;
	   parent[*it] = pair<int, int>(a, 1 << degree[a]);

	   treeInit(*it);
   }
   finish[a] = ++traversalTime;
}

void init()
{
   memset(dp, 0, sizeof(dp));
   traversalTime = 0;
   depth[0] = 0;
   color[0] = 0;
   parent[0] = pair<int, int>(-1, -1);
   treeInit(0);
}