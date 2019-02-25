#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>
#include "sails.h"

//https://oj.uz/submission/86583

using namespace System;
using namespace std;

const int N = 15;

class IndexTree {
private:
	int data[N];
 
public:
	void Add(int ind, int val) 
	{
		data[ind] += val;
	}
 
	int Query(int ind) 
	{
		int ans = 0;
		for (int i = 1; i <= ind; i++)
		{
            ans += data[i];
		}

		return ans;
	}
};

int ns1;
IndexTree indTree;
pair<int, int> masts[N];

int binarySearchLow(int low, int high, int ind) 
{
	int ans = low;
	int sumToInd = indTree.Query(ind);
 
	while (low <= high) 
	{
		int mid = (low + high) / 2;
 
		if (indTree.Query(mid) != sumToInd) 
		{
			ans = mid + 1;
			low = mid + 1;
		}
		else 
		{
			high = mid - 1;
		}
	}
 
	return ans;
}

int binarySearchHigh(int low, int high, int ind) 
{
	int ans = high + 1;
	int sumToInd = indTree.Query(ind);
 
	while (low <= high) 
	{
		int mid = (low + high) / 2;
 
		if (indTree.Query(mid) != sumToInd) 
		{
			ans = mid;
			high = mid - 1;
		}
		else 
		{
			low = mid + 1;
		}
	}
 
	return ans;
}

int findMinInefficiency1()
{
   sort(masts, masts + ns1);

   for (int i = 0; i < ns1; i++) 
   {
	  if (i != 0 && masts[i - 1].first != masts[i].first) 
	  {
		  indTree.Add(masts[i - 1].first + 1, -indTree.Query(masts[i - 1].first));
   	  }

      int ind = masts[i].first - masts[i].second + 1;

	  if (ind != 1 && indTree.Query(ind) == indTree.Query(ind - 1)) 
	  {
          int low = binarySearchLow(1, ind - 1, ind);	
		  int high = binarySearchHigh(ind + 1, masts[i].first, ind);

          int aux = low + high - ind - 1;
			
		  indTree.Add(low, 1);
		  indTree.Add(aux + 1, -1);
			
		  if (high != masts[i].first + 1) 
		  {
			  indTree.Add(high, 1);
		  }  
	  }
	  else
	  {
          indTree.Add(ind, 1);
	  }
   }

   return 0;
}

void sails_test1()
{
	ns1 = 6;

	masts[0] = make_pair(3, 2);
	masts[1] = make_pair(5, 3);
	masts[2] = make_pair(4, 1);
	masts[3] = make_pair(2, 1);
	masts[4] = make_pair(4, 3);
	masts[5] = make_pair(3, 2);

	findMinInefficiency1();
}


/*

               -|
         -| -| -|
   -| -|  | -|  |
 |  | -|  |  | -|
-| -|  |  | -|  |

*/
