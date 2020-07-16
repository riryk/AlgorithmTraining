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

	   int tmp[n];

       for (int i = 0; i < n; i++)
	   {

	   }

       return 0;
   }
}

