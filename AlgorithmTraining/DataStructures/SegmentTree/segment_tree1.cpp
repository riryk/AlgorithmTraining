#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>
#include <iostream>
#include <cmath>
#include <math.h> 

using namespace System;
using namespace std;

int constructTreeUtil(int arr[], int start, int end, int* sg, int i)
{
    if (start == end)
	{
		sg[i] = arr[start];
		return sg[i];
	}

    int mid = start + (end - start) / 2;
    sg[i] = constructTreeUtil(arr, start, mid, sg, 2*i + 1) 
		  + constructTreeUtil(arr, mid + 1, end, sg, 2*i + 2);  
	return sg[i];
}

int* constructTree(int arr[], int n)
{
    int x = (int)ceil(log((double)n)/log((double)2));
    int size = 2 * (int)pow(2, (double)x) - 1;

	int* sg = (int*)malloc(size * sizeof(int));
    
	constructTreeUtil(arr, 0, n - 1, sg, 0);

	return sg;
}

void updateTreeUtil(int start, int end, int i, int diff, int* sg, int si)
{
    if (i < start || i > end)
	{
		return;
	}

	sg[si] += diff;

	if (start != end)
	{
	    int mid = start + (end - start) / 2;
	    updateTreeUtil(start, mid, i, diff, sg, 2*si + 1);
        updateTreeUtil(mid + 1, end, i, diff, sg, 2*si + 2);
	}
}

void updateTree(int arr[], int n, int i, int diff, int* sg)
{
    arr[i] += diff;
	updateTreeUtil(0, n - 1, i, diff, sg, 0);
}

void updateRangeUtil(int start, int end, int r_start, int r_end, int diff, int* sg, int si)
{
    if (start > end || r_start > end || r_end < start)
	{
		return;
	}
    
    if (start == end)
	{
        sg[si] += diff;
	}

    int mid = (start + end) / 2;

    updateRangeUtil(start, mid, r_start, r_end, diff, sg, 2 * si + 1);
    updateRangeUtil(mid + 1, end, r_start, r_end, diff, sg, 2 * si + 2);
    
    sg[si] = sg[2*si + 1] + sg[2*si + 2];
}

int queryUtil(int start, int end, int left, int right, int* sg, int si)
{
	if (right < start || left > end)
	{
		return 0;
	}

	if (start >= left && end <= right)
	{
		return sg[si];
	}

	int mid = start + (end - start) / 2;
    return queryUtil(start, mid, left, right, sg, 2*si + 1) 
		+ queryUtil(mid + 1, end, left, right, sg, 2*si + 2); 
}

int query(int* sg, int n, int left, int right)
{
    return queryUtil(0, n - 1, left, right, sg, 0);
}

void test_segment_tree1()
{
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int* sg = constructTree(arr, n);
}
