#include "stdafx.h"
#include "dfs_adjacency_list.h"
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>

int al_visited[Max];

void dfs_adjacency_list(int i, graph_node *g[], void (*action)(int))
{
	graph_node *p;

    al_visited[i] = 1;
    action(i);
    
	p = g[i];
    while (p != NULL)
	{
	   if (!al_visited[p->vertex])
		   dfs_adjacency_list(p->vertex, g, action);
	   p = p->next;
	}
}

void insert_edge(graph_node *g[], int vi, int vj)
{
    graph_node *p, *vnew;

    vnew = (graph_node*)malloc(sizeof(graph_node));
    vnew->vertex = vj;
    vnew->next = NULL;

    if (g[vi] == NULL)
	{
        g[vi] = vnew;
		return;
	}

    p = g[vi];   
    while (p->next != NULL)
       p = p->next;

    p->next = vnew;
}