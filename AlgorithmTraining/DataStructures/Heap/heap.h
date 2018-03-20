#ifndef Hash_h
#define Hash_h 1

struct heap 
{
	int size;
	int count;
	int *heap_array;
};

int heap_init(struct heap *h);

void max_heapify(int *heap_array, int i, int count);

int heap_delete(struct heap *h);

void heap_display(struct heap *h);

void emptyPQ(struct heap *pq);

void heap_test();

#endif
