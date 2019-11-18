#include "stdafx.h"
#include "hill.h"
#include <vector>  
#include <deque>
#include <algorithm> 
#include <errno.h>
#include <math.h>  
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include "regions.h"

using namespace System;
using namespace std;

namespace regions1
{
	const int N=200050;
	const int S=317;
	const int H=635;
    const int M=25050;
	int sol[H][M];

    int reg[N]; 
    int par[N]; 
    vector<int> E[N];
    vector<int> my[N];
    vector<int> ids[N];
	int tsz;
	int tid;
    int lid[N];
    int rid[N];
    int hid[N];

	void dfs(int u)
	{
        lid[u] = ++tid;
		ids[reg[u]].push_back(u);
        for (int i = 0; i < E[u].size(); i++)
		{
            dfs(E[u][i]); 
		}
        rid[u] = tid;
	}

	void heavy(int u, int r, int count)
	{
        if (hid[u] == r) 
			count++;
		else
			sol[r][hid[u]] += count;

		for (int i = 0; i < E[u].size(); i++)
		{
            heavy(E[u][i], r, count);
		}
	}

    void solve()
	{
        int n,m,q,i;
	    scanf("%i %i %i",&n,&m,&q);
        
		/*
		n = 6;
		m = 3;
		q = 4;
		*/
        // scanf("%i",&reg[1]);
        reg[1] = 1;
        
		/*
        for(i=2;i<=n;i++)
		{
		   scanf("%i %i",&par[i],&reg[i]);
		   E[par[i]].push_back(i);
		}
		*/
		par[2] = 1; reg[2] = 2; E[par[2]].push_back(2);
        par[3] = 1; reg[3] = 3; E[par[3]].push_back(3);
        par[4] = 2; reg[4] = 3; E[par[4]].push_back(4);
        par[5] = 2; reg[5] = 3; E[par[5]].push_back(5);
        par[6] = 5; reg[6] = 1; E[par[6]].push_back(6);
		
        for(i=1;i<=n;i++) 
		{
			my[reg[i]].push_back(i);
		}
		
        dfs(1);
        for(i=1;i<=m;i++) 
		{ 
	       if (my[i].size()>=S) 
		   { 
	           hid[i]=++tsz;
			   heavy(1,i,0);		
		   }
		}
		int x, y;
		while (q--)
		{
           scanf("%i %i", &x, &y);
		   if (my[x].size() > S)
		   {
			   printf("%i", sol[hid[x]][y]);
		   }
		   else
		   {

		   }
		}
	}
}