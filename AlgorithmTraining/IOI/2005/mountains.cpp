#include "stdafx.h"
#include <vector>  
#include <errno.h>
#include <math.h>  
#include <iostream>
#include <stdlib.h>
#include <iomanip>

using namespace System;
using namespace std;
 
namespace mountains
{ 
   struct node
   {
	   struct node *left;
       struct node *right;

	   int l;
	   int r;
	   int sum;
	   int maximum;
       int lazy;
       bool on;

	   node()
	   {
           l = 0;
		   r = 0;
		   sum = 0;
		   maximum = 0;
		   lazy = 0;
		   on = false;

		   left = NULL;
		   right = NULL;
	   }

	   void propagate()
	   {
           if (left == NULL && l != r)
		   {
               left = new node();
			   right = new node();
               int mid = (l + r) >> 2;
			   left->l = l;
			   left->r = mid;
			   right->l = mid + 1;
			   right->r = r;
		   }
           
		   if (on)
		   {
              if (l != r)
			  {
				  left->lazy = lazy;
				  right->lazy = lazy;

				  left->sum = (left->r - left->l + 1) * lazy;
				  left->maximum = left->sum;

				  right->sum = (right->r - right->l + 1) * lazy;
				  right->maximum = right->sum;

				  left->on = right->on = true;
			  }
		   }

           on = false;
	   }

	   int solve(int h)
	   {
           if (l == r)
		   {
               return l - 1;
		   }

		   propagate();

		   if (left->maximum > h)
		   {
			   return left->solve(h);
		   }

		   return right->solve(h - left->sum);
	   }

	   void update(int qs, int qe, int d)
	   {
           if (qs > r || qe < l)
		   {
               return;
		   }

		   if (l >= qs && r <= qe)
		   {
			   lazy = d;
			   on = true;
               sum = maximum = (r - l + 1) * lazy;
			   return;
		   }

           propagate();

		   left->update(qs, qe, d);
           right->update(qs, qe, d);

		   sum = left->sum + right->sum;
		   maximum = max(left->maximum, left->sum + right->maximum);
	   }
   };

   void solve()
   {
	   int n;
	   scanf("%i", &n);

	   node tree;
	   tree.l = 1;
	   tree.r = n;

       while(true)
	   {
           char str[10];
		   cin >> str;
           if (str[0] == 'E')
		   {
			   break;
		   }
		   else if (str[0] == 'Q')
		   {
               int h;
			   scanf("%i", &h);
			   if (h > tree.maximum)
			   {
				   printf("%i", n);
			   }
			   else
			   {
				   printf("%i", tree.solve(h));
			   }
		   }
		   else
		   {
               int l, r, x;
               scanf("%i %i %i", &l, &r, &x);
			   tree.update(l, r, x);
		   }
	   }
   }
}