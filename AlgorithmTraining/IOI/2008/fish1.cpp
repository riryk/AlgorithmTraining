#include "stdafx.h"
#include "islands.h"
#include <vector>  
#include <deque>
#include <algorithm> 
#include <errno.h>
#include <math.h>  

using namespace System;
using namespace std;

namespace segtree 
{
   short aint[1100009];

   void build (int nod, int st, int dr)
   {
       aint[nod] = 1;
       if (st == dr) return;
       int mij = (st + dr) >> 1, f1 = nod << 1, f2 = f1 | 1;
       build (f1, st, mij);
       build (f2, mij + 1, dr);
   }

   void change (int nod, int st, int dr, int pos, int val)
   {
       if (st == dr)
       {
           aint[nod] = val;
           return;
       }
       int mij = (st + dr) >> 1, f1 = nod << 1, f2 = f1 | 1;
       if (pos <= mij) change (f1, st, mij, pos, val);
       else change (f2, mij + 1, dr, pos, val);
       aint[nod] = ((int) aint[f1] * aint[f2]);
   }
}

namespace fish1
{
   const int maxN = 1000000;
   int N, K, mod;
   int l[maxN + 9], t[maxN + 9];
   int lst[maxN + 9], frst[maxN + 9], nxt[maxN + 9], minJ[maxN + 9];
   int f[maxN + 9], lastCovered[maxN + 9];

   void read()
   {
      scanf ("%d %d %d", &N, &K, &mod);
      vector<pair<int,int>> v;
      v.resize(N);
      for (int i=0; i<N; i++)
        scanf ("%d %d", &v[i].first, &v[i].second);
      sort (v.begin(), v.end());
      for (int i=1; i<=N; i++)
        l[i] = v[i - 1].first, t[i] = v[i - 1].second;
   } 
   
   void buildNxtLstFrst()
   {
      for (int i=1; i<=N; i++)
      {
         if (lst[t[i]] != 0)
             nxt[lst[t[i]]] = i;
         lst[t[i]] = i;
      }
      for (int i=N; i>=1; i--)
         frst[t[i]] = i;
   }

   void buildMinJ()
   {
      int j = 0;
      for (int i=1; i<=N; i++)
      {
          while (j <= N && l[j] < 2 * l[i]) j ++;
          minJ[i] = j;
      }
   }
   
   int ans = 0;

   void computeAnswer()
   {
      int i = 0;
      for (int j=1; j<=N; j++)
      {
          while (l[i + 1] * 2 <= l[j])
		  {
              i++;
			  f[t[i]]++;
			  lastCovered[t[i]] = i;
			  segtree::change(1, 1, N, lst[t[i]], f[t[i]] + 1);
		  }

		  if (lst[t[j]] == j)
          {

		  }
	  }
   }

   void solve()
   {
      read(); 
	  segtree::build (1, 1, N);  
	  buildNxtLstFrst();
	  buildMinJ();
   }
}