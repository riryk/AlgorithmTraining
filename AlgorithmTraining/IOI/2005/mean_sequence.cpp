#include "stdafx.h"
#include <vector>  
#include <errno.h>
#include <math.h>  

using namespace System;
using namespace std;
 
namespace garden
{ 
   #define MAXN 255

   int K,M,N,S;
   pair<int, int> P[10005];
   int A[MAXN][MAXN];
   int L[MAXN], R[MAXN];
   int result(12222222222);

   void read()
   {
	  scanf("%d %d",&M,&N); // M - length of the garden, N - width
	  scanf("%d %d",&S,&K); // S - number if roses, K - min num of roses.
	  for (int i = 1; i <= S; i++) {
		 scanf("%d $d", &P[i].first, &P[i].second);
	  }
   }

   void solve()
   {
      memset(A, 0, sizeof A);

	  for (int i = 1; i <= S; i++) 
		  A[P[i].first][P[i].second]++;

      for (int i = 1; i <= M; i++) 
		  for (int j = 1; j <= N; j++)
			  A[i][j] += A[i-1][j] + A[i][j-1] - A[i-1][j-1];
       
      for (int y1 = 1; y1 <= N; y1++)
		  for (int y2 = y1; y2 <= N; y2++)
		  {
              int x1, x2;
			  x1 = x2 = 1;
              int mini = 10000000;
			  while (1)
			  {
				  int t = A[x2][y2] - A[x2][y2-1] - A[x2-1][y2] + A[x2-1][y2-1];
				  if (t < K) x1++;
				  else if (t > K) x2--;
				  else
				  {
					  mini = min(mini, x2 - x1 + 1 + y2 - y1 + 1);
				  }
				  if (x1 > x2) x2++;
				  if (x2 == M + 1) break;
			  }

			  if (mini < R[y1]) R[y1] = mini;
			  if (mini < L[y2]) L[y2] = mini;
		  }
       
       for (int i = 2; i <= N; i++) 
          L[i] = min(L[i], L[i-1]);

	   for (int i = N-1; i >= 0; i--)
	      R[i] = min(R[i], R[i+1]);

       for (int i = 1; i <= N; i++)
          result = min(result, L[i] + R[i]);
   }

   void main()
   {
       read();
	   solve();
	   swap(N, M);
       
	   for (int i = 1; i < S; i++)
		   swap(P[i].first, P[i].second);

	   solve();
   }
}