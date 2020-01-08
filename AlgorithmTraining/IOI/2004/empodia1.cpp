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
 
namespace empodia1
{ 
   #define NMAX 1100010
   
   int N;
   int A[NMAX];
   int stack[NMAX];
   int S;

   void init()
   {
       S = 0;
	   for(int i = N-1; i >= 0; --i){
		   while(S && A[stack[S-1]] > A[i]) --S;
		   sm[i] = S ? stack[S-1] : N;
           stack[S++] = i
	   }
   }

   void solve()
   {
       scanf("%d", &N);
	   for(int i = 0; i < N; i++)
          scanf("%d", &A[i]);  
	   
       
   }
}