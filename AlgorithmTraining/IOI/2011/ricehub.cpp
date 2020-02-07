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
 
namespace ricehub
{ 
	const int N = 100 * 1000 + 228;
 
    long long sum[N];
    int x[N];

    int besthub(int n, int L, int X[], long long B){  
		for (int i = 0; i < n; i++) {
			x[i] = X[i];
		}
        for (int i = 1; i < n; i++) {
			sum[i] = sum[i-1] + x[i-1];
		}
		return 0;
	}
}