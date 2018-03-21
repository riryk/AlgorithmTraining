#include "stdafx.h"
#include "dfs_adjacency_matrix.h"
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>

int am_visited[Max];

void dfs_adjacency_matrix(int i, int n, int g[Max][Max], void (*action)(int))
{
   am_visited[i] = 1;
   action(i);
   for (int j = 0; j < n; j++)
       if (!am_visited[i] && g[i][j])
       	   dfs_adjacency_matrix(j, n, g, action);
}
