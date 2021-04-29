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

using namespace System;
using namespace std;

namespace raisins
{
    void calculateSum(int n, int m, int grid[][201], int sum[][201])
	{
        sum[1][1] = grid[0][0];
        for (int i = 0; i < n; i++) sum[1][i+1] = grid[0][i] + sum[1][i];
        for (int i = 0; i < n; i++) sum[i+1][1] = grid[i][0] + sum[i][1];
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)   
		  sum[i+1][j+1] = grid[i][j] + sum[i][j+1] + sum[i+1][j] - sum[i][j];
	}
    
	int get_sum(int sum[][201], int i1, int j1, int i2, int j2)
	{
		if (i1 == i2) return sum[i1+1][j2+1] - sum[i1+1][j1];
		if (j1 == j2) return sum[i2+1][j2+1] - sum[i1][j2+1];
		return sum[i2+1][j2+1] - sum[i1][j2+1] - sum[i1+1][j2] + sum[i1][j2];
	}

    int computeDp(int n, int m, int grid[][201])
	{
        int sum[201][201];
        calculateSum(n, m, grid, sum);
        int dp[20][20][20][20];

        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) dp[i][i][j][j] = grid[i][j];

        for (int i = 0; i < n; i++)
		   for (int d = 1; d < m; d++)
              for (int j = 0; j + d < m; j++)
                 for (int t = j; t < j+d; t++)
					dp[i][j][i][j+d] = min(dp[i][j][i][j+d], get_sum(sum,i,j,i,j+d) + dp[i][j][i][t] + dp[i][t+1][i][j+d]);

        for (int j = 0; j < m; j++)
		   for (int d = 1; d < m; d++)
              for (int i = 0; i + d < n; j++)
                 for (int t = i; t < i+d; t++)
					dp[i][j][i+d][j] = min(dp[i][j][i+d][j], get_sum(sum,i,j,i+d,j) + dp[i][j][t][j] + dp[t+1][j][i+d][j]);

		for (int i1 = 0; i1 < n; i1++)
           for (int j1 = 0; j1 < m; j1++)
			   for (int d1 = 0; i1 + d1 < n; d1++)
				   for (int d2 = 0; j1 + d2 < m; d2++)
				   {
					   int i2 = i1 + d1;
                       int j2 = j1 + d2;
					   for (int t = i1; t < i2; t++)
                          dp[i1][j1][i2][j2] = min(dp[i1][j1][i2][j2], get_sum(sum,i1,j1,i2,j2) + dp[i1][j1][t][j2] + dp[t+1][j1][i2][j2]);
				   }

		return 0;
	}
}