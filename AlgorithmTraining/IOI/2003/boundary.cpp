#include "stdafx.h"
#include <vector>  
#include <errno.h>
#include <math.h>  
#include <algorithm> 
#include <set>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

using namespace System;
using namespace std;
 
namespace boundary
{ 
   int r,n,x,y;

   pair<double,double> getp(int x1,int y1,int x2,int y2){
       x2 -= x1;
	   y2 -= y1;
	   double t = 1e10, k = 1e10;
	   if(x2!=0){
		   t=((x2>0?(double)n:0)-x1)/x2;
	   }
	   if(y2!=0){
		   k=((y2>0?(double)n:0)-y1)/y2;
	   }
       pair<double,double> f;
	   if (k <= t) {
		   f = y2>0 ? make_pair(x1+x2*k,n) : make_pair(x1+x2*k,0);  
	   } else {
		   f = x2>0 ? make_pair(n,y1+y2*t) : make_pair(0,y1+y2*t);  
	   }

	   return f;
   }

   void solve()
   {
	   cin>>r>>n>>x>>y;
	   for (size_t i=0;i<r;i++){
           int p;
		   cin>>p;
		   for (size_t j=0;j<p;j++){
              int a,b;
			  cin>>a>>b;
              pair<double, double> np = getp(x, y, a, b);
		   }
	   }
   }
}