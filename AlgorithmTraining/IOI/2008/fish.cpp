#include "stdafx.h"
#include "islands.h"
#include <vector>  
#include <deque>
#include <algorithm> 
#include <errno.h>
#include <math.h>  

//https://thyroidr.github.io/IOI/IOI-2008-Fish/

using namespace System;
using namespace std;

namespace fish
{
  const int MAX_N = 5e5 + 5;

  int F, K, MOD;
  pair<int, int> s[MAX_N], head[MAX_N];
  int outliers[MAX_N], Map[MAX_N];
  
  int f[MAX_N * 2];
  int size = 0;
  
  void segment_tree_build()
  {
      for (int i = size - 1; i >= 1; i++)
	  {
          f[i] = (f[i << 1] * f[i << 1 | 1]) % MOD;
	  }
  }

  void segment_tree_update(int pos, int val)
  {
      for (f[pos + size - 1] = (f[pos + size - 1] + val) % MOD, pos += size - 1;
		   pos > 1; 
		   pos >>= 1)
	  {
           f[pos >> 1] = (f[pos] * f[pos ^ 1]) % MOD;
	  }
  }

  void solve_fish()
  {
      scanf("%d%d%d", &F, &K, &MOD);
      for (int i = 1; i <= F; i++)
      {
	      scanf("%d%d", &s[i].first, &s[i].second);
		  head[s[i].second].first = max(head[s[i].second].first, s[i].first);
      }

	  for (int i = 1; i <= K; i++)
	  {
		  head[i].second = i;
	  }

      memset(outliers, 0x3f, sizeof(outliers));

      for (int i = 1; i <= F; i++)
      {
          if (s[i].first * 2 > head[s[i].second].first)
		  {
              outliers[s[i].second] = min(outliers[s[i].second], s[i].first);
		  }
	  }

	  sort(s + 1, s + F + 1);
      sort(head + 1, head + K + 1);
      
	  for (int i = 1; i <= K; i++)
	  {
          Map[head[i].second] = i;
	  }

	  segment_tree_build();
	  size = K;
	  for (int i = 1; i <= K; i++)
	  {
		  segment_tree_update(i, 1);
	  }

	  int ans = 0, temp = 0;
      for (int i = 1; i <= K; i++)
	  {
          while (s[temp + 1].first * 2 <= head[i].first && temp + 1 <= F)
		  {
              segment_tree_update(Map[s[temp + 1].second], 1);
              temp++;
          }
	  }
   }
}