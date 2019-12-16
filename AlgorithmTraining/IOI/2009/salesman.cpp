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
    const int XMX=500001;
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
		long long mmax(int v, int s, int e, int l, int r) {
            if (l>e || r<s) return linf;
			if (s<=l && r<=e) return tree[v];
			int m=(s+e)>>1;
            return max(mmax(v<<1,s,m,l,r), mmax((v<<1)+1,m+1,e,l,r));
		}
        long long max(int l, int r) {
			if (r<l) return linf;
			return mmax(1,1,n,l,r); 
		}
	} US, DS;

	int comp(struct shop s1, struct shop s2)
	{
		if (s1.t==s2.t) return s1.x<s2.x;
		return s1.t<s2.t;
	}
    
	long long get(int x)
	{
		long long update_max = US.max(x,XMX)+u*x;
		long long down_max = DS.max(1,x)-d*x;
		return max(update_max, down_max);
	}

	long long T[MX];
    long long X[MX], Y[MX];

	void check(int l, int r)
	{
        for (int i=l; i<=r; i++) 
			T[i]=get(S[i].x);

		X[l]=T[l]+S[l].a;
		Y[r]=T[r]+S[r].a;
        
		for(int i=l+1; i<=r; i++)
           X[i]=max(X[i-1]-d*(S[i].x-S[i-1].x), T[i])+S[i].a;

        for(int i=r-1; i>=l; i--)
           Y[i]=max(Y[i+1]-u*(S[i+1].x-S[i].x), T[i])+S[i].a;

        for (int i=1; i<=r; i++)
		{
			US.upt(S[i].x, max(X[i], Y[i]) - u*S[i].x);
            DS.upt(S[i].x, max(X[i], Y[i]) + d*S[i].x);
		}
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
        int pos=1;
        while(pos<=n){
           int l=pos,r=pos;
		   while(r<n && S[r+1].t==S[l].t) r++;
           check(l,r);
           pos=r+1;
		}
	}
}