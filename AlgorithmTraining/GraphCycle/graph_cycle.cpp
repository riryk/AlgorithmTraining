#include "stdafx.h"
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace graph_cycle_simple
{
	struct Edge
	{
		int x;
		int y;
	};
	typedef struct Edge EE;

	struct Graph
	{
		int V;
		int E;
		EE *edges;
	};
	typedef struct Graph GG;

	GG* constructGraph(int v, int e)
	{
		GG* g = (GG*)malloc(sizeof(GG));
		g->V = v;
		g->E = e;
		g->edges = (EE*)malloc(e*sizeof(EE));
		return g;
	}

	int find(int v, int* parent){
		while(parent[v]!=-1){
			v = parent[v];
		}
		return v;
	}

	void unite(int v1, int v2, int* parent){
        int p1 = find(v1,parent);
        int p2 = find(v2,parent);
		if (p1!=p2)
	        parent[p2]=p1;
	}

	int isCycle(GG* g){
		int* parent = (int*)malloc(g->V*sizeof(int));
		memset(parent, -1, g->V*sizeof(int));
        
		for(int i = 0; i < g->E; i++){
		   int px = find(g->edges[i].x, parent);
		   int py = find(g->edges[i].y, parent);
		   if (px == py) return 1;
		   unite(px, py, parent);
		}

        return 0;
	}

	void main()
	{
        GG* g = constructGraph(3, 3);
		g->edges[0].x = 0;
        g->edges[0].y = 1;
        g->edges[1].x = 1;
        g->edges[1].y = 2;
        g->edges[2].x = 0;
        g->edges[2].y = 2;
		int hasCycle = isCycle(g);
	}
}