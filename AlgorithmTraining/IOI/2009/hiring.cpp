#include "stdafx.h"
#include "hill.h"
#include <vector>  
#include <deque>
#include <algorithm> 
#include <errno.h>
#include <math.h>  
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace System;
using namespace std;

namespace hiring
{
   #define MAX_N 500000
   
   class candidate
   {
      public:
        double s, q, r;
        int i;

        bool operator < (const candidate &c) const
        {
           return r < c.r;
        }
   };
    
   candidate c[MAX_N];
   int n;
   long long w;

   int best = 0;
   int bestIndex = 0;
   double bestCost = 1000000000;

   void solve()
   {
       scanf("%d %lld", &n, &w);
       for (int i = 0; i < n; i++)
	   {
		   scanf("%lf %lf", &c[i].s, &c[i].q);
		   c[i].r = c[i].s / c[i].q;
	   }
	   sort(c, c + n);

	   double totalQual = 0;
	   vector<double> heapQuals;
	   heapQuals.reserve(n);
       for (int i = 0; i < n; i++)
	   {
		   heapQuals.push_back(c[i].q);
		   push_heap(heapQuals.begin(), heapQuals.end());
		   totalQual += c[i].q;
		   double maxQual = w / c[i].r;
		   while (totalQual > maxQual)
		   {
               totalQual -= heapQuals[0];
               pop_heap(heapQuals.begin(), heapQuals.end());
			   heapQuals.pop_back();
		   }
           
		   int num = (int)heapQuals.size();
		   double cost = totalQual * c[i].q;
		   if (num > best || (num == best && cost < bestCost))
		   {
               bestIndex = i;
               bestCost = cost;
               best = num;
		   }
	   }

	   vector<pair<double, int>> heap;
       bool usedCandidate[MAX_N];
       memset(usedCandidate, 0, n + 1);

       totalQual = 0;
	   for (int i = 0; i <= bestIndex; i++)
	   {
		   heap.push_back(make_pair(c[i].q, c[i].i));
           push_heap(heap.begin(), heap.end());
		   totalQual += c[i].q;
		   usedCandidate[i] = true;
	   }

	   double maxQual = w / c[bestIndex].r;
       while (totalQual > maxQual)
       {
           totalQual -= heap[0].first;
           usedCandidate[heap[0].second] = false;
           pop_heap(heap.begin(), heap.end());
           heap.pop_back();
       }
   }
}