#include "stdafx.h"
#include "aliens.h"
#include <vector>  
#include <errno.h>
#include <math.h>  

int findEdge(int x0, int y0, int dx, int dy);

bool isRed(int x, int y) 
{ 
   return 1;
}

int findCenter(int n, int x0, int y0)
{
   int xr = findEdge(x0, y0, 1, 0);
   return -1;
}

int findEdge(int x0, int y0, int dx, int dy) 
{
   int i = 0;
   while (isRed(x0 + (1 << i) * dx, y0 + (1 << i) * dy)) 
	   i++;
   
   int lo = 1 << (i - 1);
   int hi = 1 << i;

   while (lo < hi) 
   {
      int mid = (lo + hi) / 2;
	  if (isRed(x0 + mid * dx, y0 + mid * dy))
		  lo = mid + 1;
	  else 
		  hi = mid;
   }

   return lo - 1;
}