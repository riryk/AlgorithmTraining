#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>

using namespace System;
using namespace std;

namespace fenwick_tree_1
{
	void update(int* fenwick, int n, int index, int val)
	{
        index++;
		while (index <= n) 
		{
            fenwick[index] += val;
			index += index & (-index);
		}
	}

    void construct(int* fenwick, int n, int* arr)
	{
        for (int i = 0; i < n; i++)
		{
			update(fenwick, n, i, arr[i]);
		}
	}

	int sum(int* fenwick, int n, int index)
	{
		index++;
		int sum = 0; 
		while (index > 0)
		{
            sum += fenwick[index];
            index -= index & (-index);
		}
		return sum;
	}

	void main()
	{
		int arr[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9}; 
		int n = sizeof(arr)/sizeof(arr[0]);
		int* fenwick = (int*)malloc((n+1)*sizeof(int));
		memset(fenwick, 0, sizeof(fenwick));

		//test
		int val = 10;
		arr[7] += val;
		update(fenwick, n, 7, 10);
	}
}
