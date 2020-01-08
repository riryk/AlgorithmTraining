#include "stdafx.h"
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
 
namespace phidias
{    
    int n, m;
    int C[602][602];
	int DP[602][602];
    int k, x, y;

    int solve()
    {
       cin >> n >> m >> k;
	   for (int i = 0; i < k; i++){
		   cin >> x >> y;
		   C[x][y]=1;
	   }
	   for(int x = 1; x <= n; x++){
		   for(int y = 1; y <= m; y++){
			   if (C[x][y]) continue;
			   DP[x][y] = x*y;
			   for (int xx = 1; xx <= x/2; xx++){
                  DP[x][y] = min(DP[x][y], DP[xx][y]+DP[x-xx][y]);
			   }
               for (int yy = 1; yy <= y/2; yy++){
                  DP[x][y] = min(DP[x][y], DP[x][yy]+DP[x][y-yy]);
			   }
		   }
	   }
	   return DP[m][m];
    }
}