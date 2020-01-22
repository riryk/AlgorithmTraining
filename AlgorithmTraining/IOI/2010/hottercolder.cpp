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

namespace garage
{
   #define MAX_N 100
   #define MAX_M 2000

   int rates[MAX_N];
   int weights[MAX_M];
   
   bool occupied[MAX_N];
   int spaces[MAX_M];

   void simulate()
   {
      int n, m;
	  cin >> n >> m;

      for (int i = 0; i < n; i++)
	  {
         cin >> rates[i];
         occupied[i] = false;
	  }

	  for (int i = 0; i < m; i++)
	  {
         cin >> weights[i];
         spaces[i] = -1;
	  }

      int firstSpace = 0;
	  deque<int> q;
      int revenue = 0;

      for (int i = 0; i < 2 * m; i++)
	  {
         int x;
		 cin >> x;
		 if (x > 0)
		 {
			 x--;
			 q.push_back(x);
		 }
		 else
		 {
             x = -x - 1;
			 int spot = spaces[x];
			 occupied[spot] = false;
			 spaces[x] = -2;

			 if (spot < firstSpace)
				 firstSpace = spot;
		 }

		 while (firstSpace < n && !q.empty())
		 {
			 revenue += weights[q.front()] * rates[firstSpace];
             occupied[firstSpace] = true;
             spaces[q.front()] = firstSpace;
			 q.pop_front();

			 while (firstSpace < n && occupied[firstSpace])
                firstSpace++;
		 }
	  }
   }
}