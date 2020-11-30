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

using namespace System;
using namespace std;
 
namespace combo_deal
{
    int items;
    int items_price[20];
	int totalMenus;
	int menus[20][11];
    int menu_price[20];
	int needed[10];

	int solve(int pos, int x1, int x2, int x3, int x4, int x5, int x6)
	{
		if (pos == totalMenus)
		{
		   if (x1 == needed[0] 
		    && x2 == needed[1] 
		    && x3 == needed[2]
		    && x4 == needed[3]
		    && x5 == needed[4]
		    && x6 == needed[5])
		   {
              return 0;
		   }

		   return 1000000;
		}

        int ret = solve(pos + 1, x1, x2, x3, x4, x5, x6);

        int xx1 = x1 + menus[pos][0];
        int xx2 = x2 + menus[pos][1];
        int xx3 = x3 + menus[pos][2];
        int xx4 = x4 + menus[pos][3];
        int xx5 = x5 + menus[pos][4];
        int xx6 = x6 + menus[pos][5];  
        
		if (xx1 <= needed[0] 
		 && xx2 <= needed[1]
		 && xx3 <= needed[2]
		 && xx4 <= needed[3]
		 && xx5 <= needed[4]
		 && xx6 <= needed[5])
	    {
           ret = min(ret, solve(pos + 1, xx1, xx2, xx3, xx4, xx5, xx6) + menu_price[pos]);
		}

		return ret;
	}

    void main()
    {
        scanf("%d", &items);

        for (int i = 0; i < items; i++)
		{
            int a;
            scanf("%d", &a);
            items_price[i] = a;
		}

        scanf("%d", &totalMenus);
        
        for (int i = 0; i < totalMenus; i++)
		{
            for (int j = 0; j < items; j++)
			{
			    int a;
                scanf("%d", &a);
                menus[i][j] = a;  
			}

            int a;
            scanf("%d", &a);
            menu_price[i] = a;  
		}

        for (int i = 0; i < items; i++)
		{
            menus[totalMenus][i] = 1;
            menu_price[totalMenus] = items_price[i];
            totalMenus++;
		}

		memset(needed, 0, sizeof(needed));

        for (int i = 0; i < items; i++)
		{
            int a;
            scanf("%d", &a);
            needed[i] = a;  
			printf("%d\n", solve(0,0,0,0,0,0,0));
		}
    }
}

