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
 
namespace empodia
{ 
   int n;
   int A[100002];
   int C[100002];
   
   void solve()
   {
       cin>>n;
       for (int i=1;i<=n;i++)
		   cin>>A[i];
	   
	   int i,j;
	   for (i = n; i > 0; i--){
           int mayor = A[i];
		   for (j = i+1; j<=n && A[j] > A[i]; j++){
			   mayor = max(A[j], mayor);
			   if (A[j]==A[i]+j-i && A[j]==mayor){
                   C[i] = j;
				   break;
			   }
			   if (C[j])
				   break;
		   }
	   }
   }
}