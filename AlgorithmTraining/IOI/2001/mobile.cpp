#include "stdafx.h"
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
#include <utility>

using namespace System;
using namespace std;
 
namespace rods
{ 
    int N;
	int x1,y1,x2,y2;

	int gridsize() { return 100; }

	int rect(int x1, int y1, int x2, int y2 ) { return 0; }
    
	int firstV(int x, int y, int x1, int y1)
	{
		int b = x;
		int e = x1;
		int mid;
		while (b != e)
		{
		    int mid = (b + e) / 2;
            if (rect(x, y, mid, y1))
               e = mid;
			else
               b = mid + 1;
		}
        return b + 1;
	}

	int lastV(int x, int y, int x1, int y1)
	{
		int b = x;
		int e = x1;
		int mid;
		while (b != e) 
		{
            mid = (b + e) / 2 + 1;
            if (rect(mid, y, x1, y1))
				b = mid;
			else 
				e = mid - 1;
		}
		return b;
	}

	int firstH(int x, int y, int x1, int y1)
	{
		int b = y;
		int e = y1;
		int mid;
		while (b != e)
		{
		    int mid = (b + e) / 2;
            if (rect(x, y, x1, mid))
               e = mid;
			else
               b = mid + 1;
		}
        return b + 1;
	}
    
	int lastH(int x, int y, int x1, int y1)
	{
		int b = y;
		int e = y1;
		int mid;
		while (b != e) 
		{
            mid = (b + e) / 2 + 1;
            if (rect(x, mid, x1, y1))
				b = mid;
			else 
				e = mid - 1;
		}
		return b;
	}

    void main()
    {
        N = gridsize();
        int R = firstV(1, 1, N, N);
        int R1 = lastV(1, 1, N, N);
        int C = firstH(1, 1, N, N);
        int C1 = lastH(1, 1, N, N);
		if (rect(R, C, R, C)) 
		{
            if (rect(R + 1, C, R + 1, C))
		    {
                int d = lastV(R, C, R1-1, C);

			}
		}
    }
}