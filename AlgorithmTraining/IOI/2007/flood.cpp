#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>

using namespace System;
using namespace std;

const int N = 20;
int visited[N * 2][2];

int n;
int m; 

int p[N];
pair<int, int> coord[N];
int from[N];
int to[N];

int e[N][4]; // 1 - north, 3 - south, 2 - east, 0 - west.

void add(int u, int v, int id)
{
	if (coord[u].first == coord[v].first) {
		if (coord[u].second < coord[v].second) e[u][1] = id; else e[u][3] = id;
	} else {
		if (coord[u].first < coord[v].first) e[u][2] = id; else e[u][0] = id;
	}
}

bool sortPoint(int i, int j)
{ 
	return coord[i] < coord[j]; 
}

vector<int> getNotDestroyedWalls()
{
	vector<int> notdestroyed; 

	for (int i = 0; i < m; i++) {
		add(from[i], to[i], i);
        add(to[i], from[i], i);
	}

	sort(p + 1, p + 1 + n, sortPoint);
    
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		while (1) {
            bool found = 0;
			int u = p[i], d = 2;
			for (int j = 0; j < 4; ++j) {    // 0 - west, 1 - north, 2 - east, 3 - south
				int id = e[u][j];
				found |= id && !visited[id][j < 2];
			}
			if (!found) break;

			++cnt;
			vector<int> buffer;

			while (1) {
				for (int j = 0; j < 4; ++j) {
					int k = (d + j + 3) % 4; 
					int id = e[u][k];
					if (id && !visited[id][k < 2]) {
						u = from[id] + to[id] - u;
						d = k; 
						visited[id][k < 2] = cnt; 
						buffer.push_back(id); 
						break;
					}
				}
				if (u == p[i]) break;
			}

			for (int i = 0; i < buffer.size(); i++) {
				int id = buffer[i];
				if (!visited[id][0]) visited[id][0] = -1;
				if (!visited[id][1]) visited[id][1] = -1;
			}
		}
	}
    
	cnt = 0;
	for (int i = 1; i <= m; ++i) {
		if (visited[i][0] == visited[i][1]) cnt++;
	}

	return notdestroyed;
}

void flood_test()
{
	n = 15;

	p[1] = 1;
	p[2] = 2;
	p[3] = 3;
	p[4] = 4;
	p[5] = 5;
	p[6] = 6;
	p[7] = 7; 
	p[8] = 8;
	p[9] = 9;
	p[10] = 10;
	p[11] = 11;
	p[12] = 12;
	p[13] = 13;
	p[14] = 14;
	p[15] = 15;

	coord[1] = make_pair(1, 1);
	coord[2] = make_pair(8, 1);
	coord[3] = make_pair(4, 2);
	coord[4] = make_pair(7, 2);
	coord[5] = make_pair(2, 3);
	coord[6] = make_pair(4, 3);
	coord[7] = make_pair(6, 3);
	coord[8] = make_pair(2, 5);
	coord[9] = make_pair(4, 5);
	coord[10] = make_pair(6, 5);
	coord[11] = make_pair(4, 6);
	coord[12] = make_pair(7, 6);
	coord[13] = make_pair(1, 8);
	coord[14] = make_pair(4, 8);
	coord[15] = make_pair(8, 8);

	m = 17;
   
	from[1] = 1;
    from[2] = 2;
    from[3] = 15;
    from[4] = 14;	 
	from[5] = 13;
    from[6] = 14;
	from[7] = 11;
    from[8] = 12;
	from[9] = 4;
    from[10] = 3;
	from[11] = 6;
    from[12] = 5;
	from[13] = 8;
    from[14] = 9;
    from[15] = 9;
    from[16] = 10;
    from[17] = 7;

    to[17];

	to[1] = 2;
	to[2] = 15;
	to[3] = 14;
	to[4] = 13;
	to[5] = 1;
	to[6] = 11;
	to[7] = 12;
	to[8] = 4;
	to[9] = 3;
	to[10] = 6;
	to[11] = 5;
	to[12] = 8;
	to[13] = 9;
	to[14] = 11;
	to[15] = 10;
	to[16] = 7;
	to[17] = 6;

	vector<int> walls; 
	walls = getNotDestroyedWalls();
}