#include "stdafx.h"
#include "teleporters.h"
#include <vector>  
#include <algorithm> 
#include <errno.h>
#include <math.h>  

using namespace System;
using namespace std;

namespace teleporters
{
   #define MAX_X 2000000

   int ans;
   int N, M;
   int right[MAX_X+1];
   bool vst[MAX_X+1];
   vector<int> cycles;

   void dfs(int x, long long y) {
       while(1) {
		   if (vst[x]) {
			   cycles.push_back(y);
			   return;
		   }  
		   if (x == MAX_X+1) {
			   ans += y;
			   return;
		   }
		   if (right[x] != x + 1) y++;
           x = right[x];
	   }
   }

   void solve()
   {
	   scanf("%d%d", &N, &M);
	   for (int i = 0; i < MAX_X+1; i++) right[i] = i + 1;
	   for (int i = 0; i < N; i++) {
          int a, b;
          scanf("%d %d", &a, &b);
          right[a - 1] = b; right[b - 1] = a;
	   }
	   for (int i = 0; i < MAX_X+1; i++) {
		  if (vst[i]) continue;
		  dfs(i, 0);
	   }
	   sort(cycles.begin(), cycles.end());
	   while(M-- > 0){ 
		  if (!cycles.empty()){
			  ans+= 2 + cycles.back();
			  cycles.pop_back();
		  } else {
			  cycles.push_back(1);
			  ans++;
		  }
	   }
   }
}

