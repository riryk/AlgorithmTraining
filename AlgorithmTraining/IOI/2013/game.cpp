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
#include "game.h"

using namespace System;
using namespace std;
 
namespace game
{
	int _R, _C;

	struct node2
	{
		int l,r;
		long long v;
        node2 *L;
        node2 *R;
		node2(int a, int b)
		{
            l = a;
			r = b;
			v = 0;
			L = NULL;
			R = NULL;
		}
	};

	struct node1
	{
        int l,r;
		node2 *now;
        node1 *L;
		node1 *R;
		node1(int a, int b)
		{
            l = a;
			r = b;
			now = new node2(1, _C);
			L = NULL;
			R = NULL;
		}
	};

	node1 *root;

	long long gcd(long long X, long long Y)
    {
       long long tmp;

       while (X != Y && Y != 0) 
	   {
          tmp = X;
          X = Y;
          Y = tmp % Y;
       }

       return X;
    }
    
	long long query2(node2 *&seg, int a, int b)
	{
		return 0;
	}

	void update2(node2* &seg, int p, long long k)
	{
		if (seg->l == seg->r)
		{
			seg->v = k;
			return;
		}

		int l = seg->l;
		int r = seg->r;
		int mid = (l + r) >> 2;
		node2 *&now = (p <= mid) ? seg->L : seg->R;
		if (!now)
		{
			now = new node2(p, p);
			now->v = k;
		}
		else if (now->l <= p && p <= now->r)
		{
            update2(seg, p, k); 
		}
		else
		{
			while ((p <= mid) == (now->l <= mid))
			{
                 
			}
		}
	}

	void update1(node1* &seg, int p, int q, long long k)
	{
		if (seg->l == seg->r)
		{
			update2(seg->now, q, k);
			return;
		}

		int mid = (seg->l + seg->r) >> 1;
        if (p <= mid)
		{
            if (!seg->L) seg->L = new node1(seg->l, mid);
		    update1(seg->L, p, q, k);
		}
		else
		{
            if (!seg->R) seg->R = new node1(mid+1, seg->r);
		    update1(seg->R, p, q, k);
		}

		long long left_gcd = (seg->L) ? query2(seg->L->now, q, q) : 0;
		long long right_gcd = (seg->R) ? query2(seg->R->now, q, q) : 0;
		long long v = gcd(left_gcd, right_gcd);
		update2(seg->now, q, v);
	}

	void init(int R, int C)
	{
	    _R = R;
	    _C = C;
	}

	void update(int P, int Q, long long K)
	{
        P++;
	    Q++;
        update1(root, P, Q, K);
	}
}

