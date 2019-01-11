#include "stdafx.h"
#include "Leet62.h"
#include <vector>  
#include <errno.h>
#include <math.h>  

int uniquePaths(int m, int n) {
   int paths[100][100];
   
   for (int i = 0; i < m; i++) paths[i][0] = 1;
   for (int j = 0; j < n; j++) paths[0][j] = 1;

   for (int i = 1; i < m; i++) 
      for (int j = 1; j < n; j++) 
        paths[i][j] = paths[i-1][j] + paths[i][j-1];

   return paths[m-1][n-1];
}

void uniquePaths_test() {
   int res1 = uniquePaths(3, 2);
   int res2 = uniquePaths(7, 3);
}