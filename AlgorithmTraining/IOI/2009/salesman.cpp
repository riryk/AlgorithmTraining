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
#include "salesman.h"

using namespace System;
using namespace std;

namespace salesman
{
	const int MX=500010;
	const long long linf=(1LL<<60);

	int n, d, u, s; 
    struct shop {
       int t, x, a;
    } S[MX];
    
	struct Seg {
        static const int MX=(1<<20);
        long long tree[MX]; 
		int n;  
		void init(int sz){
			n=sz;
            for(int i=1; i<MX;i++) tree[i]=-linf;
		}
		void upt(int v, int s, int e, int pos, long long val) {
            if(pos<s || pos>e) return;
			if(s==e){
               tree[v]=val;
			   return;
			}
			int m=(s+e)>>1;
			upt(v<<1,s,m,pos,val);
            upt((v<<1)+1,m+1,e,pos,val);
            tree[v]=max(tree[v<<1],tree[(v<<1)+1]);
		}
		void upt(int pos, long long val){
           upt(1,1,n,pos,val);
        }
	} US, DS;

	int comp(struct shop s1, struct shop s2)
	{
		if (s1.t==s2.t) return s1.x<s2.x;
		return s1.t<s2.t;
	}

    void solve()
	{
        cin>>n>>u>>d>>s;
		for(int i=1; i<=n; i++)
		{
           int t,x,a;
		   cin>>t>>x>>a;
           struct shop s;
		   s.t = t;
		   s.x = x;
		   s.a = a;
		   S[i] = s;
		}
		sort(S+1,S+n+1,comp);
		DS.init(500001);
        US.init(500001);
		US.upt(s, -u*s);
        DS.upt(s, d*s);
	}
}