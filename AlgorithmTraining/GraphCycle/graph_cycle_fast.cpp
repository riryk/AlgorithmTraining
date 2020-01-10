#include "stdafx.h"
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace graph_cycle_fast
{
	struct Edge
	{
		int x,y;
	};
	typedef struct Edge EE;
    
	struct Graph
	{
		int V,E;
		EE* edges;
	};
    typedef struct Graph GG;

	struct Set
	{
		int parent;
		int rank;
	};
    typedef struct Set SS;

	GG* createGraph(int v, int e)
	{
       GG* g = (GG*)malloc(sizeof(GG));
	   g->V = v;
	   g->E = e;
	   g->edges = (EE*)malloc(g->E*sizeof(EE));
	   return g;
	}
    
	int find(int i, SS* sets)
	{
		while(sets[i].parent != -1)
		{
			sets[i].parent = find(sets[i].parent, sets);
		}
        return i;
	}
    
	void unite(int x, int y, SS* sets)
	{
		int px = find(x, sets);
        int py = find(x, sets);
		if (px == py) return;

		int xrank = sets[px].rank;
		int yrank = sets[py].rank;
		if (xrank > yrank){
			sets[py].parent = px;
		} else if (yrank > xrank){
			sets[px].parent = py;
		} else {
            sets[px].parent = py;
			sets[px].rank++;
		}
	}

	int hasCycle(GG* g)
	{
	   SS* sets = (SS*)malloc(g->V * sizeof(SS)); 
	   for (int i = 0; i < g->V; i++)
	   {
		   sets[i].parent = -1;
           sets[i].rank = 0;
	   }

       for (int i = 0; i < g->E; i++)
	   {
		   int x = g->edges[i].x;
		   int y = g->edges[i].y;
           int px = find(x, sets);
           int py = find(y, sets);
		   if (px == py) return 1;
		   unite(px, py, sets);
	   }
	   return 0;
	}

	void solve()
	{
       GG* g = createGraph(3,3);
	   g->edges->x = 0;
	   g->edges->y = 1;
       g->edges->x = 0;
	   g->edges->y = 2;
       g->edges->x = 1;
	   g->edges->y = 2;
	}
}