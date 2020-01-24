#include "stdafx.h"
#include <vector>  
#include <errno.h>
#include <math.h>  

namespace binary_tree_array
{
	struct nnode
	{
		int key;
		int value;
	};
    typedef struct nnode node;

	int search(node** tree, int i, int key)
	{
		if (tree[i] == NULL || tree[i]->key == key) return i;
		return key < tree[i]->key 
			? search(tree, 2*i+1, key)
			: search(tree, 2*i+2, key);
	}

	void insert(node** tree, int* count, int val)
	{
        int root = 0;
	}

	void test()
	{
		node* tree[10000];
		memset(tree, 10000, NULL);

        int count = 0;
		insert(tree, &count, 2);
	}
}