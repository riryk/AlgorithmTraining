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

namespace hill
{
   int cache[1000][1000];

   long long query(int x, int y)
   {
       if (cache[x][y] == -1)
       {
           cout << "0 " << x + 1 << " " << y + 1 << endl;
           cout.flush();

           cin >> cache[x][y];
       }

       return cache[x][y];
   }

   void identify_hill(int x, int y)
   {
       cout << "1 " << x + 1 << " " << y + 1 << endl;
       cout.flush();

       exit(0);
   }

   int solve()
   {
       int n,m;
	   cin >> n >> m;

       for (int i = 0; i < n; i++)
	      for (int j = 0; j < m; j++)
              cache[i][j] = -1;
       
       int x1 = 0, x2 = n - 1, y1 = 0, y2 = m - 1;
	   int curBest = -1;
	   int bestX = -1, bestY = -1;

	   while (x1 != x2 && y1 != y2)
	   {
           int w = x2 - x1;
		   int h = y2 - y1;

		   if (w > h)
		   {
			   int mid = (x1 + x2) / 2;
               int bestH = -1;
			   int bY = -1;
			   for (int y = y1; y <= y2; y++)
			   {
				   int curH = query(mid, y);
				   if (curH > bestH)
				   {
					   bestH = curH;
					   bY = y;
				   }
			   }

			   int bX = mid;
			   if (mid-1 >= x1 && query(mid-1, bY) > bestH)
			   {
                   bestH = query(mid-1,bY);
                   bX = mid-1; 
			   }
			   if (mid+1 <= x2 && query(mid+1, bY) > bestH)
			   {
				   bestH = query(mid+1, bY);
                   bX = mid+1;
			   }
               
			   if (bX == mid && bestH > curBest)
			   {
                   identify_hill(mid, bY);

			   }

               if (bestH > curBest)
			   {
				   curBest = bestH;
                   bestX = bX;
				   bestY = bY;
			   }

			   if (bestX > mid)
			   {
				   x1 = mid + 1;
			   }
			   else
			   {
				   x2 = mid - 1;
			   }
		   }
	   }

	   return 1;
   }
}