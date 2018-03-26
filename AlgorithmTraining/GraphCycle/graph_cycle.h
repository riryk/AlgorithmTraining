#ifndef graph_cycle_h
#define graph_cycle_h 1

struct Edge
{
    int src;
	int dest;
};

struct Graph
{
    int vertex_count;
	int edges_count;
    struct Edge* edges;
};

struct Subset
{
    int parent;
    int rank;
};

struct Graph* createGraph(int vertex_count, int edges_count);

int naive_find(int parent[], int i);

int rank_find(struct Subset subsets[], int i);

void naive_union(int parent[], int x, int y);

void rank_union(struct Subset subsets[], int x, int y);

int naive_is_cycle(struct Graph* graph);

int rank_is_cycle(struct Graph* graph);

void naive_is_cycle_test();

void rank_is_cycle_test();

#endif
