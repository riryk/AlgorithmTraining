#include "stdafx.h"
#include "pyramid.h"
#include <vector>  
#include <errno.h>
#include <math.h>  

const int MAXC = 1001;   

#define FOR()

int F;  // n - number of rows
int C;  // m - number of columns
int a; // a - height of rectangle base, number of rows it occuepies. 
int b; // b - width of rectangle base, number of columns it occupies.
int c; // c - height of chamber, number of rows it occuepies. 
int d; // d - width of chamber, number of columns it occupies.
int T[MAXC][MAXC]; // T[i][j] will contain rectangle sum of rectangle (0,0)->(i,j)
int value[MAXC]; 

int sum(int x1, int y1, int x2, int y2)
{
	return T[x2][y2] - T[x1][y2] - T[x2][y1] + T[x1][y1];
}

int findMaxBasement(int f, int c, int x1, int y1, int x2, int y2, int* height[])
{
   F = f; C = c; a = x1; b = y1; c = x2; d = y2;
   for (int i = 1; i < f; i++)
      for (int j = 1; j < c; j++)
		  T[i][j] = height[i][j] + T[i-1][j] + T[i][j-1] - T[i-1][j-1];
    
   for (int i = c + 1; i < F - 1; i++) {

      for (int j = d; j < C ; j++) 
         value[j] = sum(i - c, j - d, i, j);  

	  for (int j = C; j >= d + 1; j--) {
         
	  }
   }


   return 0;
}
