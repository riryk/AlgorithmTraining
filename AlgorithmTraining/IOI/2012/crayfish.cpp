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
#include "crayfish.h"

using namespace System;
using namespace std;
 
namespace crayfish
{ 
    char str[1000001];
    int dad[1000001], dadH[1000001], H[1000001];
    vector<int> v;
	int act, it;

    void init()
	{
		it = 1;
		act = 0;
		H[0] = -1;
		dad[0] = dadH[0] = 0;
		v.clear();
	}

	void type_letter(char l)
	{
        str[it] = l;
		v.push_back(it);
        it++;
	}

	void solve()
	{
        init();
        type_letter('a');
        type_letter('b');
        type_letter('d');
        type_letter('e');
        type_letter('c');
	}
}