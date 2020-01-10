#include "stdafx.h"
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace kruskal
{
	struct Edge
	{
		int x,y;
		int weight;
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

	SS* initSets(GG* g)
	{
       SS* sets = (SS*)malloc(g->V * sizeof(SS)); 
	   for (int i = 0; i < g->V; i++)
	   {
		   sets[i].parent = -1;
           sets[i].rank = 0;
	   }
	   return sets;
	}

	int hasCycle(GG* g, SS* sets)
	{
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
    
	int compare(const void* e1, const void* e2)
	{
       EE* edge1 = (EE*)e1;
       EE* edge2 = (EE*)e2;
	   return edge1->weight - edge2->weight;
	}

	EE* kruskal(GG* g)
	{
		EE* mintree = (EE*)malloc(g->V*sizeof(EE));
		qsort(g->edges, g->E, sizeof(EE), compare);
        SS* sets = initSets(g);
		int e = 0;
		int i = 0;
		while (e < g->V && i < g->E)
		{
			EE edge = g->edges[i];
			int px = find(edge.x, sets);
            int py = find(edge.y, sets);
			if (px==py){
				i++;
				continue;
			}
			mintree[i++] = edge;
			unite(px, py, sets);
		}

		return mintree;
	}

	void solve()
	{
       GG* g = createGraph(4,5);

	   g->edges[0].x = 0;
	   g->edges[0].y = 1;
	   g->edges[0].weight = 10;

       g->edges[0].x = 0;
	   g->edges[0].y = 2;
	   g->edges[0].weight = 6;

       g->edges[0].x = 0;
	   g->edges[0].y = 3;
	   g->edges[0].weight = 5;

       g->edges[0].x = 1;
	   g->edges[0].y = 3;
	   g->edges[0].weight = 15;

       g->edges[0].x = 2;
	   g->edges[0].y = 3;
	   g->edges[0].weight = 4;
	}
}