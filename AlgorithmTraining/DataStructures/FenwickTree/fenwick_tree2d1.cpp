#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>

using namespace System;
using namespace std;

namespace fenwick_tree2d_1
{
	const int N = 4;
    
	void update(int** fenwick, int n, int m, int x, int y, int val)
	{
        x = x + 1;
		y = y + 1;
		while (x <= n) {
			while (y <= m) {
				fenwick[x][y] += val;
				y += y & (-y);
			}
            x += x & (-x);
		}
	}

	int get(int** fenwick, int n, int m, int x, int y)
	{
		x++; y++;
		int sum = 0;
		while (x > 0) {
			while (y > 0) {
                sum += fenwick[x][y];
                y -= y & (-y);  
			}
			x -= x & (-x);
		}
		return sum;
	}
    
	int query(int** fenwick, int n, int m, int x1, int y1, int x2, int y2)
	{
		return get(fenwick, n, m, x2, y2) 
			- get(fenwick, n, m, x2, y1 - 1)
			- get(fenwick, n, m, x1 - 1, y2)
			+ get(fenwick, n, m, x1 - 1, y1 - 1);
	}

	void main()
	{
        int mat[N][N] = {{1, 2, 3, 4}, 
                         {5, 3, 8, 1}, 
                         {4, 6, 7, 5}, 
                         {2, 4, 8, 9}};

        int fenwick[N+1][N+1];
	}
}
