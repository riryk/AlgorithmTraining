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
#include <queue>

using namespace System;
using namespace std;
 
namespace crocodile_graph
{ 
    #define MAX 10000
    #define INF 1000000000000 
	
	int N, M, K;
	vector<pair<int, int>> graph[MAX];
	long long dist[2][MAX];
	bool done[MAX];
	int cnt[MAX];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int travel_plan(int N, int M, int R[][2], int L[], int K, int P[])
	{
		for (int i = 0; i < M; i++) {
			graph[R[i][0]].push_back(make_pair(R[i][1], L[i]));
            graph[R[i][1]].push_back(make_pair(R[i][0], L[i]));
		}
		for (int i = 0; i < K; i++) {
            dist[0][P[i]] = dist[1][P[i]] = 0;          
			pq.push(make_pair(0, P[i]));
		}
		while (!pq.empty()) {
		 	pair<int, int> item = pq.top();
			if (done[item.second]) continue;
			int curr = item.second;
			done[curr] = 1;
			for (int i = 0; i < graph[curr].size(); i++) {
                pair<int,int> next = graph[curr][i];
				long long new_dist = dist[1][curr] + next.second;
				if (new_dist < dist[0][next.first]){
					dist[1][next.first] = dist[0][next.first];
					dist[0][next.first] = new_dist;
					cnt[next.first]++;
					if (cnt[next.first] == 2) {
						pq.push(make_pair(dist[1][next.first], next.first));
					}
				}
				else if (new_dist < dist[1][next.first]){
                    dist[1][next.first] = new_dist;
					cnt[next.first]++;
					if (cnt[next.first] == 2) {
						pq.push(make_pair(dist[1][next.first], next.first));
					}
				}
			}
		}
		return dist[1][0];
	}
}