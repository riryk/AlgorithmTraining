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
#include "cave.h"

using namespace System;
using namespace std;
 
namespace cave
{
	int N;
	int S[100];

    int tryCombination(int arr[])
	{  
        if (arr[2] == 0 && arr[1] == 0) return 1;
		if (arr[2] == 0 && arr[1] == 1 && arr[3] == 1) return 2;
		if (arr[2] == 0 && arr[1] == 1 && arr[3] == 0 && arr[0] == 1) return 3;
		if (arr[2] == 0 && arr[1] == 1 && arr[3] == 0 && arr[0] == 0) return -1;
        return 0;
	}
    
	void revert(int S[], int start, int end)
	{
        for (int i = start; i <= end; i++) S[i] ^= 1;
	}

    void exploreCave(int n)
	{
        N = n;
		int first = tryCombination(S);
		if (first != 0)
		{
            for (int i = 0; i < N; i++) S[i] ^= 1;
		}
	}

	void test()
	{
		exploreCave(4);
	}
}

