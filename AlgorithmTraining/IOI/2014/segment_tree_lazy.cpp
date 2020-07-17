#include <vector>  
#include <errno.h>
#include <math.h>  
#include <algorithm> 
#include <set>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <utility>
#include "segment_tree_lazy.h"

using namespace System;
using namespace std;
 
namespace segment_tree_lazy
{
   int tree[1000];

   void build_internal(int arr[], int node, int start, int end)
   {
       if (start == end)
	   {
		   tree[node] = arr[start];
		   return;
	   }

	   int mid = (start + end) >> 1;
	   build_internal(arr, 2*node + 1, start, mid);
       build_internal(arr, 2*node + 2, mid + 1, end);
	   tree[node] = tree[2*node + 1] + tree[2*node + 2];
   }

   void update_internal(int arr[], int node, int idx, int val, int start, int end)
   {
       if (start == end)
	   {
		   arr[idx] += val;
		   tree[node] += val;
		   return;
	   }

       int mid = (start + end) >> 1;
	   if (idx <= mid)
	   {
           update_internal(arr, 2*node + 1, idx, val, start, mid);
	   }
	   else
	   {
           update_internal(arr, 2*node + 2, idx, val, mid + 1, end);
	   }

	   tree[node] = tree[2*node + 1] + tree[2*node + 2];
   }

   void build(int arr[], int n)
   {
	   build_internal(arr, 0, 0, n-1);
   }

   void update(int arr[], int n, int idx, int val)
   {
	   update_internal(arr, 0, idx, val, 0, n - 1);
   }
}

