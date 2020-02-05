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
 
namespace twofive
{ 
    int sat[6];
	int sut[6];
	int satir[6];
	char A[25];
    bool used[25];

	void solve1()
 	{
		int x,y,t,s(0);
        scanf("%s", A);       
		for (int i = 0; i < 25; i++)
		{
            x = i / 5;
			y = i % 5; 
            satir[x]++;       
			t = A[i] - 'A';
			for (int j = 0; j < t; j++)
			{
                if (!used[j] && j > sat[x] && j > sut[y])
				{

				}
			}
		}
	}

	void solve2()
	{
        
	}

	void main()
	{
        memset(sat, -1, sizeof(sat));
        memset(sut, -1, sizeof(sut));
		char c;
		scanf("%c", &c);
		if (c == 'W') solve1();
		else solve2();
	}
}