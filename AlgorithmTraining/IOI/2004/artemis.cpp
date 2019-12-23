#include "stdafx.h"
#include <vector>  
#include <errno.h>
#include <math.h>  
#include <algorithm> 

using namespace System;
using namespace std;
 
namespace artemis
{ 
   #define MAXN 20005

   class point
   {
      public:
		int x,y,ind;
        point() {  }
		void read(int i) { scanf("%d %d",&x,&y); ind = i; }
   } P[MAXN];

   inline bool cmp( const point &a , const point &b )
   {
	  return a.x < b.x;
   }

   int N,T;
   int alt[MAXN];
   int sol_alt[MAXN];
   void solve()
   {
      int syc,t;
      scanf("%d %d",&N,&T);
	  for(int i = 1; i <= N; i++) P[i].read(i);
	  sort(P+1,P+N+1,cmp);
	  for(int i = 1; i <= N; i++)
	  {
         alt[i]=i;
		 for(int j = 1; j <= i-1; j++)
		 {
			 if (P[i].y < P[j].y)
			 {
                alt[j]++;
				alt[i]--;
			 }
		 }
		 syc = 0;
		 sol_alt[i] = alt[i];
         for(int j = 1; j <= i-1; j++)
		 {
            t = sol_alt[i] - alt[j] - syc + sol_alt[j] + 1; 
		 }
	  }
   }
}