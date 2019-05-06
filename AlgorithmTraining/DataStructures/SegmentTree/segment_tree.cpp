#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>
#include <iostream>
#include <cmath>

using namespace System;
using namespace std;

int constructSTUtil(int arr[], int ss, int se, int *st, int si)  
{
    if (ss == se)  
    {  
        st[si] = arr[ss];  
        return arr[ss];  
    }  

    int mid = ss + (se - ss) / 2;
    st[si] = constructSTUtil(arr, ss, mid, st, 2*si + 1) + 
		     constructSTUtil(arr, mid + 1, se, st, 2*si + 2);
	return st[si];
}

int* constructST(int arr[], int n)  
{
	double log2n = log((double)n)/log((double)2);
    double height = (double)(ceil(log2n));  
	int max_size = 2*(int)pow((double)2, height) - 1;
    int *st = new int[max_size];  
    constructSTUtil(arr, 0, n-1, st, 0);  
    return st;
}

void test_segment_tree()
{
	int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr)/sizeof(arr[0]);  
	int* st = constructST(arr, n);
}

