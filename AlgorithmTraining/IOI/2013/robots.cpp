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
#include "robots.h"

using namespace System;
using namespace std;
 
namespace robots
{
	int a, b, t;
	int X[50001];
	int Y[50001];

	int putaway(int A1, int B1, int T1, int X1[])
	{
        a = A1;
		b = B1;
		t = T1;

        for (int i = 0; i < a; i++) X[i] = X1[i];
        for (int i = 0; i < b; i++) Y[i] = Y1[i];
        

		return 1;
	}

    void test()
	{

	}
}

