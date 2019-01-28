#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>

using namespace System;
using namespace std;

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, -1, 0, 1};

char visited[2001][2001];
int cellnum = 0;

void dfs(int r, int c)
{
	if (visited[r][c])
		return;

    cellnum++;    
}

int calculateArea(int rr, int cc)
{
    return -1;
}

