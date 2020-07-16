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
#include <map>
#include <utility>
#include "gondola.h"

using namespace System;
using namespace std;
 
namespace gondola
{
   int isValid(int n, int seq[])
   {
	   int minid = 0;

	   for (int i = 0; i < n; i++)
	   {
           if (seq[minid] > seq[i])
		   {
			   minid = i;
		   }
	   }

	   int tmp[100];

       for (int i = 0; i < n; i++)
	   {
           tmp[i] = seq[(minid + i)%n];
	   }

	   for (int i = 0; i < n; i++)
	   {
		   seq[i] = tmp[i];
	   }

	   set<long long> used;
       int last = -1;
	   for (int i = 0; i < n; i++)
	   {
		   if (used.find(seq[i]) != used.end())
		   {
			   return 0;
		   }

		   used.insert(seq[i]);

		   if (seq[i] <= n)
		   {
               last = i;
		   }
	   }

       return 0;
   }
}

