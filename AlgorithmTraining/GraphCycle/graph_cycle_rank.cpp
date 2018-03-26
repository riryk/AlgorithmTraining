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
	struct Subset *subsets = (struct Subset*)malloc(graph->vertex_count * sizeof(struct Subset));

	for (int v = 0; v < graph->vertex_count; ++v)
    {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

	for (int i = 0; i < graph->edges_count; ++i)
    {
		int x = rank_find(subsets, graph->edges[i].src);
		int y = rank_find(subsets, graph->edges[i].dest);
 
        if (x == y)
            return 1;
 
        rank_union(subsets, x, y);
    }
}

void rank_is_cycle_test()
{
    /* graph
         0
        |  \
        |    \
        1-----2 */    
    int vertex_count = 3;
	int edges_couunt = 3;

    struct Graph* graph = createGraph(vertex_count, edges_couunt);

    graph->edges[0].src = 0;
    graph->edges[0].dest = 1;

    graph->edges[1].src = 1;
    graph->edges[1].dest = 2;

    graph->edges[2].src = 0;
    graph->edges[2].dest = 2;
    
	int is_cycle = rank_is_cycle(graph);
}



