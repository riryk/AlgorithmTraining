#ifndef dfs_adjacency_list_h
#define dfs_adjacency_list_h 1

typedef struct graph_node
{
    struct graph_node *next;
    int vertex;
} graph_node;

const int Max = 100;

#endif
