#include "mexico.h"
#include <vector>  
#include <errno.h>
#include <math.h>  
#include <iostream>
#include <algorithm>

using namespace System;
using namespace std;

namespace mexico
{
   int n,m;
   int a,b;
   bool E[1002][1002];
   int DP[1002][1002][2];

   void read()
   {
	   cin >> n >> m;

       for (int i=1; i <= m; i++)
	   {
		   cin >> a >> b;
		   a--; b--;
           E[a][b] = 1;
		   E[b][a] = 1;
	   }
   }

   int l(int x)
   {
       return (x + 1) % n;
   }

   int r(int x)
   {
	   return (x + n - 1) % n;
   }

   int f(int a, int b, int p)
   {
	   if (a == l(b)) return 1;
        
	   int x = r(a);
       int y = l(b);
       
	   int p1, p2;

	   if (p)
	   {
           p1 = E[b][x] ? f( x, b, 0 ) : 0;
           p2 = E[b][y] ? f( a, y, 1 ) : 0;
	   }
	   else
	   {
           p1 = E[a][x] ? f( x, b, 0 ) : 0;
		   p2 = E[a][y] ? f( a, y, 1 ) : 0;
	   }
       
       if (p1)
		   DP[a][b][p] = 1;
	   else
		   DP[a][b][p] = p2 ? 2 : 0;

	   return DP[a][b][p];
   }

   void rebuild_path(int a, int b, int p)
   {
       if (p)
	   {
		   // count << (b + 1) << "\n";
	   }
	   else
	   {
           // count << (b + 1) << "\n";
	   }

	   if (a == l(b)) return;

	   if (DP[a][b][p] == 1)
	   {
           rebuild_path(r(a), b, 0);   
	   }
	   else
	   {
           rebuild_path(a, l(b), 1);          
	   }
   }
}