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
 
namespace twofive1
{ 
	int N;
	char W[26];
	bool used[26];
	int x[26];
	int y[26];

    int count()
	{
		return 0;
	}

    int main()
	{
		if (getchar() == 'W')
		{
            scanf("%s", &W);
            for ( int i = 1; i < 6; i++ )
            for ( int j = 1; j < 6; j++ )
            for ( int k = 0; k < 25; k++ ) 
			{
                if (used[k]) continue;
				used[k] = true;
                x[k] = i;
				y[k] = j;
				if (W[(i-1)*5+j-1] == k + 'A') break;
				N += count();
                used[k] = false;
			}
		}

		return 0;
	}
}