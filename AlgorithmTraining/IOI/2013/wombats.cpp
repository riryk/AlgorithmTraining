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
#include <map>
#include <utility>
#include "wombats.h"

using namespace System;
using namespace std;
 
namespace wombats
{
    int R, C;
    int H[5001][201], V[5001][201];

	struct Node 
	{
	    Node *left;
	    Node *right;
	    int to[201][201];
	    Node(): left(0), right(0) 
	    {
            memset(to, 0, sizeof(to));
	    }
	};

	struct Node *root;

    void calc(int to[201][201], int s, int e);

	struct Node* make_tree(int s, int e)
	{
        struct Node *ret = new Node();
		ret->to[0][0] = 1000;

		if (e - s < 10)
		{
			calc(ret->to, s, e + 1);
			return ret;
		}
		return 0;
	}

	void combine(int a[201][201], int b[201][201], int c[201][201])
    {
        
	}
 
	void calc(int to[201][201], int s, int e)
    {
        int my_to[201][201];
		int tmp[201][201];
		int sum[201];

		for (int i = 1; i <= C; i++) 
			for (int j = 1; j <= C; j++) 
			{
				if (i == j)
					to[i][j] = 0;
				else
                    to[i][j] = 10000;
			}
        
        for (int r = s; r <= e; r++)
		{
            for (int j = 1; j <= C; j++) 
				for (int k = 1; k <= C; k++)
                    tmp[j][k] = to[j][k] + (r > s ? V[r-1][k] : 0);
              
            for (int j = 2; j <= C; j++) 
				sum[j] = sum[j-1] + H[r][j-1];  

            for (int j = 1; j <= C; j++) 
				for (int k = j; k <= C;k++)
                    my_to[j][k] = my_to[k][j] = sum[k] - sum[j];

            combine(to, tmp, my_to);
		}  
    }

    void init(int r, int c, int h[5000][200], int v[5000][200])
	{
        R = r;
		C = c;
        for (int i = 1; i <= R; i++)
			for (int j = 1; j < C; j++)
				H[i][j] = h[i-1][j-1];
	    
        for (int i = 1; i < R; i++)
			for (int j = 1; j < C; j++)
				V[i][j] = h[i-1][j-1];   

        root = make_tree(1, R-1);
	} 

	void test()
	{
		int r = 3;
        int c = 4;
		int h[4][200] = {{0,2,5},{7,1,1},{0,4,0}};
		int v[3][200] = {{0,0,0,2},{0,3,4,7}};
        init(r, c, h, v);
	}
}

