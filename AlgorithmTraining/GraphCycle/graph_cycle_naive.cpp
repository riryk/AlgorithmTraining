#include "stdafx.h"
#include "graph_cycle.h"
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Graph* createGraph(int vertex_count, int edges_count)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
	graph->vertex_count = vertex_count;
	graph->edges_count = edges_count;
	graph->edges = (struct Edge*)malloc(graph->edges_count * sizeof(struct Edge)); 
    return graph;
}

int naive_find(int parent[], int i)
{
    if (parent[i] == -1)
        return i;

    return naive_find(parent, parent[i]);
}

void naive_union(int parent[], int x, int y)
{
    int xset = naive_find(parent, x);
    int yset = naive_find(parent, y);
    parent[xset] = yset;
}

int naive_is_cycle(struct Graph* graph)
{
	int *parent = (int*)malloc(graph->vertex_count * sizeof(int));

	memset(parent, -1, sizeof(int) * graph->vertex_count);

	for (int i = 0; i < graph->edges_count; ++i)
    {
		int x = naive_find(parent, graph->edges[i].src);
		int y = naive_find(parent, graph->edges[i].dest);
 
        if (x == y)
            return 1;
 
        naive_union(parent, x, y);
    }

    return 0;
}

void naive_is_cycle_test()
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
    
	int is_cycle = naive_is_cycle(graph);
}

