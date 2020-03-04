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
 
namespace ring
{ 
	int const MAXN = 1000000;
    int n;
	bool quadruplication = 0;
	int numcycles = 0;

	// If numcycles==1, here we store the length of the only
    // cycle
	int cycle_length;  

	// -1 if the node is not an endpoint, otherwise the other endpoint
	int other_endpoint[4][MAXN];  
    vector<int> neighbours[MAXN];

	// The destroyed node of each graph (only if quadruplication==TRUE)
	int destroyed[4];  
	int degree[4][MAXN];

	// Whether each graph is linear or not
	bool islinear[4];

	void init(int k)
	{
		n = k;
		for (int i = 0; i < n; i++) 
           other_endpoint[0][i] = i;  
	}
    
	void add_new_edge(int x, int y)
	{
        // Adds an edge in case of quadruplication
        for (int i = 0; i < 4; i++)
		{
			if (!islinear[i]) continue;
            if (x == destroyed[i] || y == destroyed[i]) continue;
            
			degree[i][x]++;
            degree[i][y]++;

            if (degree[i][x] == 3 || degree[i][y])
			{
                islinear[i] = 0;
				continue;
			}

            if (other_endpoint[i][x] == y)
			{
                islinear[i] = 0;
				continue;
			}

			int a = other_endpoint[i][x];
            int b = other_endpoint[i][y];

            other_endpoint[i][x] = -1; 
            other_endpoint[i][y] = -1;

            other_endpoint[i][a] = b;
            other_endpoint[i][b] = a;
		}
	}

	void quadruplicate(int x)
	{
        quadruplication = 1;

        destroyed[0] = x;
        destroyed[1] = neighbours[x][0];
        destroyed[2] = neighbours[x][1];
        destroyed[3] = neighbours[x][2];

        for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < n; j++)
			{
                other_endpoint[0][i] = i;  
				degree[i][j] = 0;
			}
		}

        for (int i = 0; i < 4; ++i) 
		{
            islinear[i] = 1;
        }

		for (int k = 0; k < n; k++)
		{
			for (vector<int>::iterator it = neighbours[k].begin(); 
				 it != neighbours[k].end();
				 it++)
			{
                if (k < *it) add_new_edge(k, *it);
			}
		}
	}

	void link(int xx, int yy)
	{
		int x = xx;
		int y = yy;

		if (quadruplication == 0)
		{
			neighbours[x].push_back(y);
            neighbours[y].push_back(x);

            degree[0][x]++;
            degree[0][y]++;
            
            // If a node has degree 3, only it or its neighbours can be critical. 
			// So we can keep track of each of the 4 graphs obtained by removing one of these 4 nodes.
            if (degree[0][x] == 3)
			{
                quadruplicate(x);
                return;
			}

            if (degree[0][y] == 3)
			{
                quadruplicate(y);
                return;
			}

            // If their degree is < 3, then they were necessarily endpoints!
			// A longer path is formed            
            if (other_endpoint[0][x] != y) 
			{ 
                int a = other_endpoint[0][x];
                int b = other_endpoint[0][y];
 
                other_endpoint[0][x] = -1;
                other_endpoint[0][y] = -1;
                other_endpoint[0][a] = b;
                other_endpoint[0][b] = a;        
 		    }
			else
			{
                numcycles++;
                if (numcycles == 1) 
				{
                    int length = 1;
                    int previous_node = x;
                    int current_node = neighbours[x][0];

                    while (current_node != x) 
					{
                        int possibility = neighbours[current_node][0];
                        if (possibility == previous_node)
                            possibility = neighbours[current_node][1];

						previous_node = current_node;
						current_node = possibility;

						length++;
					}

					cycle_length = length;
				}
			}
		}
		else
		{
			add_new_edge(x, y);
		}
	}

    int CountCritical() 
	{
        if (quadruplication == 0) 
		{
            switch (numcycles) 
			{
                case 0:
                    return n;
 
                case 1:
                    return cycle_length;
 
                default:
                    return 0;
            }
        } 
		else 
		{
            int answer = 0;
            for (int i = 0; i < 4; ++i) 
			{
                if (islinear[i]) answer++;
            }
            return answer;
        }
    }

	void main()
	{
                
	}
}