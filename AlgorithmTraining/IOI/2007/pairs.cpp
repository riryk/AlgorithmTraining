#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>

using namespace System;
using namespace std;

typedef pair<int, int> pii;

int solve1(int m, int n, int d, int x[])
{
	sort(x, x + n);

	int pairs = 0;
	int l = 0;
	int r = 0;

    while (r < n)
	{
		while (l < r && x[r] - x[l] > d) l++;
		pairs += r - l;
		r++;
	}

    return pairs;
}

int bits[10000];

void pupdate(int i, int val)
{
	for (i; i <= 10000; i += i & (-i))
	    bits[i] += val;
}

int pquery(int i)
{
	int val = 0;
	for (i; i >= 0; i -= i & (-i))
		val += bits[i];
	return val;
}

int solve2(int m, int n, int d, int x[], int y[])
{
	vector<pair<int, int>> v;
	for (int i = 0; i < n; i++)
		v.push_back(pair<int, int>(x[i] + y[i], x[i] - y[i] + m + 1));
	sort(v.begin(), v.end());
    m*=3;
    
	int ans = 0;
    int l = 0;
	int r = 0;
	while (r < n)
	{
		while (v[r].first - v[l].first > d) {
			pupdate(v[l].second, -1);
			l++;
		}	

		ans += pquery(min(2*m, v[r].second + d)) - pquery(max(0, v[r].second - d - 1));
		pupdate(v[r].second, 1);
		r++;
	}
    
    return ans;
}

vector<int> bit3(13824000, 0);

void update3(int m, int i, int j, int k, int val)
{
   for (i; i <= 3*m; i += i&(-i))
     for (j; j <= 3*m; j += j&(-j))
       for (k; k <= 3*m; k += k&(-k))
	     bit3[i*3*m*3*m + j*3*m + k] += val;
}    

int query3(int m, int i, int j, int k)
{
	int sum = 0;
    for (i; i >= 0; i -= i&(-i))
       for (j; j >= 0; j -= j&(-j))
          for (k; k >= 0; k -= k&(-k))
	         sum += bit3[i*3*m*3*m + j*3*m + k];
	return sum;
}

int get3(int m, int x1, int y1, int z1, int x2, int y2, int z2)
{
	x1--, y1--, z1--;
    return query3(m, x2, y2, z2 ) 
         			- query3(m, x1, y2, z2 ) - query3(m, x2, y1, z2 ) - query3(m, x2, y2, z1 )
         			+ query3(m, x1, y1, z2 ) + query3(m, x1, y2, z1 ) + query3(m, x2, y1, z1 )
					- query3(m, x1, y1, z1 );
}

int solve3(int m, int n, int d, int x[], int y[], int z[])
{
    vector<pair<pii, pii>> v;
	for (int i = 0; i < n; i++)
		v.push_back(pair<pii, pii>(
		     pii(x[i]+y[i]+z[i], x[i]+y[i]-z[i] + m + 1),
             pii(x[i]-y[i]+z[i]+1+m, x[i]-y[i]-z[i] + m + m + 2)));

    sort(v.begin(), v.end()); 
    m*=3;

    int ans = 0;
    int l = 0;
	int r = 0;
	while (r < n)
	{
		while (v[r].first.first - v[l].first.first > d) 
		{
			update3(m, v[l].first.second, v[l].second.first, v[l].second.second, -1);
			l++;
		}
        
		int a = v[l].first.second, b = v[l].second.first, c = v[l].second.second;
        ans += get3(m, max(1, a - d), max(1, b - d), max(1, c - d), min(3*m, a + d), min(3*m, b + d), min(3*m, c + d));
        update3(m, v[l].first.second, v[l].second.first, v[l].second.second, 1);
		r++;
	}

	return ans;
}
