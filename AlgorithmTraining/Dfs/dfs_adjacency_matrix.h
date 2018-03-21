#ifndef dfs_adjacency_matrix_h
#define dfs_adjacency_matrix_h 1

const int Max = 100;

void dfs_adjacency_matrix(int i, int n, int g[Max][Max], void (*action)(int));

#endif
