#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>

using namespace System;
using namespace std;

int A[100000];
int N;
int dp[16][16][100000];

// supply: 1, 2, 3. 
// prev supply   000000aabb
int getScore(int prevsupply, int supply) 
{
  int a = (prevsupply >> 2);
  int b = (prevsupply & 3);
  int c = supply;
  int total = ((1 << a)|(1 << b)|(1 << c)) & 14;
  int bitcount = ((total >> 2) & 1) + ((total >> 3) & 1) + ((total >> 4) & 1);
  return bitcount;
}

int solve(int m1, int m2, int i)
{
  if (i == N) return 0;
  return min(solve(((m1 << 2)|A[i])&15, m2, i + 1) + getScore(m1, A[i]),
  	         solve(m1, ((m2 << 2)|A[i])&15, i + 1) + getScore(m2, A[i]));
}

int solvedp(int m1, int m2, int i)
{
  if (i == N) return 0;
  if (dp[m1][m2][i] != -1) return dp[m1][m2][i];
  int result = min(solve(((m1 << 2)|A[i])&15, m2, i + 1) + getScore(m1, A[i]),
  	         solve(m1, ((m2 << 2)|A[i])&15, i + 1) + getScore(m2, A[i]));
  dp[m1][m2][i] = result;
  return result;
}
