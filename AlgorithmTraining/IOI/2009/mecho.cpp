#include "stdafx.h"
#include "hill.h"
#include <vector>  
#include <deque>
#include <algorithm> 
#include <errno.h>
#include <math.h>  
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace System;
using namespace std;

namespace mecho
{
	#define MAX_N 2000

	int cx[4] = {1, -1, 0, 0};
    int cy[4] = {0, 0, 1, -1};

	int n, s;
    int dx, dy;
    int mx, my;

	char mainMap[MAX_N][MAX_N];
	int beeDistance[MAX_N][MAX_N];
	bool reachable[MAX_N][MAX_N];

	bool test(int delay)
	{
       if (delay * s >= beeDistance[mx][my])
	   {
		   return false;
	   }
       
       memset(reachable, 0, sizeof(reachable));
       deque<pair<int, pair<int, int>>> q;
	   q.push_back(make_pair(delay * s, make_pair(mx, my)));

	   while (!q.empty())
	   {
		   int distance = q.front().first;
		   int x = q.front().second.first;
		   int y = q.front().second.second;
           
		   q.pop_front();
		   if (x == dx && y == dy)
		   {
			   return true;
		   }

		   for (int i = 0; i < 4; i++)
		   {
			   int next_distance = distance + 1;
               int nx = x + cx[i];
			   int ny = y + cy[i];

			   if (nx < 0 || nx >= n 
				|| ny < 0 || ny >= n 
				|| mainMap[nx][ny] == 'T' 
				|| next_distance >= beeDistance[nx][ny]
			    || reachable[nx][ny])
			   {
				   continue;
			   }

               reachable[nx][ny] = true;
		   }
	   }
	}

    void solve()
	{
       cin >> n >> s;

       deque<pair<int, int>> bq;
       memset(beeDistance, -1, sizeof(beeDistance));
	   for (int i = 0; i < n; i++)
	   {
		   cin >> ws;
		   for (int j = 0; j < n; j++)
		   {
               cin >> mainMap[i][j];
               if (mainMap[i][j] == 'H')
			   {
				   bq.push_back(make_pair(i, j));
				   beeDistance[i][j] = 0;
			   }
			   else if (mainMap[i][j] == 'M')
			   {
				   mx = i;
				   my = j;
                   mainMap[i][j] = 'G';
			   }
			   else if (mainMap[i][j] == 'D')
               {
                   dx = i;
                   dy = j;
               }
		   }
	   }
        
	   while (!bq.empty())
	   {
		   pair<int, int> currCell = bq.front();
		   int x = currCell.first;
		   int y = currCell.second;

           for (int i = 0; i < 4; i++)
		   {
			   int nx = x + cx[i];
			   int ny = y + cy[i];

			   if (nx < 0 || nx >= n || ny < 0 || ny >= n || mainMap[nx][ny] != 'G' || beeDistance[nx][ny] != -1)
			   {
				   continue;
			   }

			   beeDistance[nx][ny] = beeDistance[x][y] + s;
			   bq.push_back(make_pair(nx, ny));
		   }
	   }

	   beeDistance[dx][dy] = n * n * s;

       int low = -1;
	   int high = 2 * n * n;

	   while (high - low > 1)
	   {
		   int mid = (low + high) >> 1;
           if (test(mid))
              low = mid;
		   else
		      high = mid;
	   }
	}
}