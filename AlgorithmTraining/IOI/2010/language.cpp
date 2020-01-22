#include "stdafx.h"
#include "language.h"
#include <math.h>

namespace language
{ 
   int m = 56;
   int n = 100;
   int mod = 50021;

   int cnt[57][50505];
   int cnt2[57][50505];
   int cnt3[57][50505];
   int cnt4[57][50505];
   int lan[57];
   
   int language(int id)
   {
	   return 0;
   }

   double f(int x)
   {
       return (double)x/(x + 1);
   }
   
   int f(int a, int b)
   {
       long long ret = (long long)a << 16;
	   ret |= b;
	   ret %= mod;
	   return ret;
   }

   int f(int a, int b, int c)
   {
 	   long long ret = (long long)f(a, b) << 16;
	   ret |= c;
	   ret %= mod;
	   return ret;
   }
 
   int f(int a, int b, int c, int d)
   {
 	   long long ret = (long long)f(a, b, c) << 16;
	   ret |= d;
	   ret %= mod;
	   return ret;
   } 

   void excert(int *arr)
   {
	   double max = 0;
       int idx = 0;
       for (int i=0;i<m;i++)
	   {
           double now = 0;
           for (int j=0;j<n;j++)
		   {
			   now += f(cnt[i][arr[j]]);
               if (j > n-1) continue;
               now += f(cnt[i][f(arr[j], arr[j+1])])*150;
			   if (j > n-2) continue;
               now += f(cnt[i][f(arr[j], arr[j+1], arr[j+1])])*100;
               if (j > n-3) continue;
               now += f(cnt[i][f(arr[j], arr[j+1], arr[j+1], arr[j+2])])*50;
		   }
		   now /= log((double)(lan[i] + 1));
		   if (now > max)
		   {
			   max = now;
			   idx = i;
		   }
	   }

       int ans = language(idx);
	   lan[ans]++;
	   for (int i = 0; i < n; i++)
	   {
           cnt[i][arr[i]]++;        
		   if(i >= n-1) continue;
		   cnt2[ans][f(arr[i], arr[i+1])]++;
		   if(i >= n-2) continue;
		   cnt3[ans][f(arr[i], arr[i+1], arr[i+2])]++;
		   if(i >= n-3) continue;
		   cnt4[ans][f(arr[i], arr[i+1], arr[i+2], arr[i+3])]++;
	   }
   }
}