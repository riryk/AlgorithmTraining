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

namespace raisins
{
    #define MAX 50

    int r, c;
    int chocolate[MAX][MAX];
	int raisins[MAX][MAX];
    int best[MAX][MAX][MAX][MAX];

	int solve(int r1, int c1, int r2, int c2)
	{
        if (best[r1][c1][r2][c2] != -1)
		{
            return best[r1][c1][r2][c2];
		}
        
        if (r1 == r2 && c1 == c2)
		{
			best[r1][c1][r2][c2] = 0;
			return 0;
		}

		int bestPayment = INT_MAX;

		for (int r = r1 + 1; r <= r2; r++)
		{
            int payment = solve(r1, c1, r - 1, c2) + solve(r, c1, r2, c2);
			if (payment < bestPayment)
			{
				bestPayment = payment;
			}
		}

		for (int c = c1 + 1; c <= c2; c++)
		{
            int payment = solve(r1, c1, r2, c - 1) + solve(r1, c, r2, c2);
			if (payment < bestPayment)
			{
				bestPayment = payment;
			}
		}

        int raisinsPayment = raisins[r2][c2] 
		    - (r1 > 0) ? raisins[r1 - 1][c2] : 0 
			- (c1 > 0) ? raisins[r2][c1 - 1] : 0
			+ (r1 > 0 && c1 > 0) ? raisins[r1 - 1][c1 - 1] : 0;

		return bestPayment + raisinsPayment;
	}

	int calculateMinCost()
	{
       cin >> r >> c;

       for (int i = 0; i < r; i++)
	     for (int j = 0; j < c; j++)
		   cin >> chocolate[i][j];

	   memset(raisins, -1, sizeof(raisins));
       memset(best, -1, sizeof(best));

       raisins[0][0] = chocolate[0][0];

	   for (int i = 1; i < r; i++)
		   raisins[i][0] = raisins[i - 1][0] +  chocolate[i][0];

       for (int i = 1; i < c; i++)
		   raisins[0][i] = raisins[0][i - 1] +  chocolate[0][i];

	   for (int i = 1; i < r; i++)
		   for (int j = 1; j < c; j++)
			   raisins[i][j] = raisins[i - 1][j] + raisins[i][j - 1] - raisins[i - 1][j - 1] + chocolate[i][j];

       return solve(0, 0, r - 1, c - 1);
	}
}