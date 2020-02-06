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
 
namespace bus
{ 
    int V;
	int X[500];
	int Y[500];
	int idx[500];
    int D[500][500];
    int diam;
	int src, hi;

	int compare(int &i, int &j)
	{
        return D[src][i] - D[src][j]; 
	}

    void main()
	{
		scanf("%d", &V);

		for (int i = 0; i < V; i++) {
            scanf("%d %d", &X[i], &Y[i]);
			idx[i] = i;
		}

		for (int i = 0; i < V; i++) {
			for (int j = 0; j < i; j++) {
                D[i][j] = D[j][i] = abs(X[j] - X[i]) + abs(Y[i] - Y[j]);
			}
		}

		diam = 1000000000;
		for (int i = 0; i < V; i++) {
			src = i;
			sort(idx, idx + V, compare);
			for (int j = 0; j < i; j++) {
				for (int k = hi = 0; k < V; k++) {
					if (D[idx[k]][j] > D[idx[hi]][j]) {
                       int newdist = D[idx[k]][i] + D[idx[hi]][j] + D[i][j];
					   if (newdist < diam) {
						   diam = newdist;
                           hi = k;
					   }
					}
				}
			}
		}
	}
}