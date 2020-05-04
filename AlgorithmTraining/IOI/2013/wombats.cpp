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
	const int LEAF_SIZE = 20;

    int R, C;
    int H[5001][201], V[5001][201];

    int my_to[201][201];
	int tmp[201][201];
	int sum[201];
	int opt[202][202];

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

    void calc(struct Node *node, int s, int e);

	void combine_nodes(struct Node *node, struct Node *up_node, struct Node *down_node);  

	struct Node* make_tree(int s, int e)
	{
        struct Node *ret = new Node();
		if (e-s < LEAF_SIZE)
		{
			calc(ret, s, e + 1);
			return ret;
		}
		int m = (s+e)>>1;
		ret->left = make_tree(s,m);
		ret->right = make_tree(m+1,e);
		combine_nodes(ret, ret->left, ret->right);
		return ret;
	}

	void update(Node* node, int s, int e, int l, int r)
	{
        if (r < s || e < l) return;  
        if (e-s < LEAF_SIZE)
		{
			calc(node, s, e + 1);
			return;
		}        
        int m = (s+e)>>1;
		update(node->left, s, m, l, r);
		update(node->right, m+1, e, l, r);
        combine_nodes(node, node->left, node->right);
	}

	void combine_nodes(struct Node *node, struct Node *up_node, struct Node *down_node)
    {
        memset(opt, 0, sizeof(opt));

		for (int diff = -C+1; diff < C; diff++)
            for (int i = 1; i <= C; i++)
			{
				int j = i + diff;
				if (j < 1 || j > C) 
					continue;

				node->to[i][j] = 2e9;

				int l = opt[i][j-1] ? opt[i][j-1] : 1;
                int r = opt[i+1][j] ? opt[i+1][j] : C;

                for (int k = l; k <= r; k++)
				{
					int v = up_node->to[i][k] + down_node->to[k][j];
                    if (node->to[i][j] > v)
					{
                        node->to[i][j] = v;
						opt[i][j] = k; 
					}
				}
			}
	}

	void combine(struct Node *node)
    {
        memset(opt, 0, sizeof(opt));

		for (int diff = -C+1; diff < C; diff++)
            for (int i = 1; i <= C; i++)
			{
				int j = i + diff;
				if (j < 1 || j > C) 
					continue;

				node->to[i][j] = 2e9;

				int l = opt[i][j-1] ? opt[i][j-1] : 1;
                int r = opt[i+1][j] ? opt[i+1][j] : C;

                for (int k = l; k <= r; k++)
				{
                    int v = tmp[i][k] + my_to[k][j];
                    if (node->to[i][j] > v)
					{
                        node->to[i][j] = v;
						opt[i][j] = k; 
					}
				}
			}
	}
 
	void calc(struct Node *node, int s, int e)
    {
        memset(my_to, 0, sizeof(my_to));
        memset(tmp, 0, sizeof(tmp));
		memset(sum, 0, sizeof(sum));

		for (int i = 1; i <= C; i++) 
			for (int j = 1; j <= C; j++) 
			{
				if (i == j)
					node->to[i][j] = 0;
				else
                    node->to[i][j] = 10000;
			}
        
        for (int r = s; r <= e; r++)
		{
            for (int j = 1; j <= C; j++) 
				for (int k = 1; k <= C; k++)
                    tmp[j][k] = node->to[j][k] + (r > s ? V[r-1][k] : 0);
              
            for (int j = 2; j <= C; j++) 
				sum[j] = sum[j-1] + H[r][j-1];  

            for (int j = 1; j <= C; j++) 
				for (int k = j; k <= C;k++)
                    my_to[j][k] = my_to[k][j] = sum[k] - sum[j];

            combine(node);
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

	void changeH(int y, int x, int v)
	{
        H[y+1][x+1] = v;
		update(root, 1, R-1, y-1, y);
	}

    void changeV(int y, int x, int v)
	{
        V[y+1][x+1] = v;
		update(root, 1, R-1, y, y);
	}
    
	int escape(int t1, int t2)
	{
        return root->to[++t1][++t2];
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

