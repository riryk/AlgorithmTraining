#include "stdafx.h"
#include "heap.h"
#include <cstddef>
#include <stdlib.h>
#include <stdio.h>

int initial_size = 4;

int heap_init(struct heap *h)
{
	h->count = 0;
	h->size = initial_size;
	h->heap_array = (int *) malloc(sizeof(int) * initial_size);

	if (!h->heap_array)
		return -1;
}

int parent(int i) { return (i - 1) / 2; }

int left(int i) { return 2 * i + 1; }

int right(int i) { return 2 * i + 2; }

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void max_heapify(int *heap_array, int i, int count) {
	int largest = i;

	if (left(i) <= count && heap_array[left(i)] > heap_array[largest])
		largest = left(i);

	if (right(i) <= count && heap_array[right(i)] > heap_array[largest])
		largest = right(i);

	if (largest != i) 
	{
        swap(&heap_array[i], &heap_array[largest]);
		max_heapify(heap_array, largest, count);
	}
}

void heap_push(struct heap *h, int value)
{
	int i;
	if (h->count == h->size)
	{
		h->size += 1;
		h->heap_array = (int*)realloc(h->heap_array, sizeof(int) * h->size);
		if (!h->heap_array) 
			exit(-1); 
	}
 	
 	h->count++;
	i = h->count - 1;
	h->heap_array[i] = value;

	while (i != 0 && h->heap_array[parent(i)] < h->heap_array[i])
	{
        swap(&h->heap_array[parent(i)], &h->heap_array[i]);
		i = parent(i);
	}
}

int heap_delete(struct heap *h)
{
	int removed;

	if (h->count <= h->size - 2 && h->size > initial_size)
	{
		h->size -= 1;
		h->heap_array = (int*)realloc(h->heap_array, sizeof(int) * h->size);
		if (!h->heap_array)
			exit(-1); 
	}
    
	removed = h->heap_array[0];

	h->count--;
	swap(&h->heap_array[0], &h->heap_array[h->count]);

	h->heap_array[h->count] = INT_MIN;
	max_heapify(h->heap_array, 0, h->count);

 	return removed;
}

void heap_display(struct heap *h) 
{
	for (int i = 0; i < h->count; ++i) 
	{
		printf("|%d|", h->heap_array[i]);
	}

	printf("\n");
}

void emptyPQ(struct heap *pq) 
{
	while (pq->count != 0) 
	{
		printf("<<%d", heap_delete(pq));
	}
}

void heap_test()
{
    struct heap h;

	heap_init(&h);

	heap_push(&h,1);
	heap_push(&h,5);
	heap_push(&h,3);
	heap_push(&h,7);
	heap_push(&h,9);
	heap_push(&h,8);

	heap_display(&h);
	heap_display(&h);

	emptyPQ(&h);
}
