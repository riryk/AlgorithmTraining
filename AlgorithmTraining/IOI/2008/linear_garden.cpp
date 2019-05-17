#include "stdafx.h"
#include "type_printer.h"
#include <vector>  
#include <algorithm>
#include <iostream>
#include <errno.h>
#include <math.h>  
#include <stdlib.h>

using namespace System;
using namespace std;

namespace linear_garden
{
   #define  N  (1000005)

   int n,m;
   int dp[3][3][N];

   int solve()
   {
       char* s;
	   cin >> n >> m >> s;
       
	   for (int i = 0; i < 3; i++)
		   for (int j = 0; j < 3; j++)
              dp[i][j][n] = 1;

	   return 1;
   }
}