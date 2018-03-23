#include "stdafx.h"
#include "graph_cycle.h"
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int rank_find(struct Subset subsets[], int i)
{
	int parent;

	if (subsets[i].parent == i)
		return i;

    parent = rank_find(subsets, subsets[i].parent);

	subsets[i].parent = parent;

    return parent;
}

void rank_union(struct Subset subsets[], int x, int y)
{
    int xroot = rank_find(subsets, x);
    int yroot = rank_find(subsets, y);

	int xrank = subsets[xroot].rank;
	int yrank = subsets[yroot].rank;

    if (xrank < yrank)
	{
        subsets[xroot].parent = yroot;
	}
    else if (xrank > yrank)
	{
        subsets[yroot].parent = xroot;
	}
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int rank_is_cycle(struct Graph* graph)
{
	struct subset *subsets = (struct subset*)malloc(graph->vertex_count * sizeof(struct subset));

	for (int v = 0; v < graph->vertex_count; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

	for (int i = 0; i < graph->edges_count; ++i)
    {
		int x = naive_find(parent, graph->edges[i].src);
		int y = naive_find(parent, graph->edges[i].dest);
 
        if (x == y)
            return 1;
 
        naive_union(parent, x, y);
    }
}

int isCycle( struct Graph* graph )
{
    int V = graph->V;
    int E = graph->E;
 
    // Allocate memory for creating V sets
    struct subset *subsets =
        (struct subset*) malloc( V * sizeof(struct subset) );
 
    for (int v = 0; v < V; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
 
    // Iterate through all edges of graph, find sets of both
    // vertices of every edge, if sets are same, then there is
    // cycle in graph.
    for(int e = 0; e < E; ++e)
    {
        int x = find(subsets, graph->edge[e].src);
        int y = find(subsets, graph->edge[e].dest);
 
        if (x == y)
            return 1;
 
        Union(subsets, x, y);
    }
    return 0;
}
