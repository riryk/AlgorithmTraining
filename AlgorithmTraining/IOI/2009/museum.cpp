#include "stdafx.h"
#include "hill.h"
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

namespace museum
{
	 pair<int, int> order[1000];

     void calculate(int n) {
         int bits = 0;
         int cur = n;
         while (cur > 0) {
         	cur >> 1;
			bits++;
         }
        
         for (int i = 0; i < n; i++) {
         	int reversed = 0;
         	int cur = i + 1;
         	int pointer = bits - 1;

         	while (cur > 0) {
               if (cur & 1) 
                  reversed += (1 << pointer);
			   cur >>= 1;
               pointer--;
         	}

			order[i] = make_pair(reversed, i + 1);
         }

         sort(order, order + n);
     }
}