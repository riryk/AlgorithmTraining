#include "stdafx.h"
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
#include <utility>

using namespace System;
using namespace std;
 
namespace robots
{ 
   #define x first
   #define y second
   #define TIME 12
   #define NMAX 24
   #define GMAX 12
   #define VMAX NMAX*NMAX*NMAX*NMAX*TIME

   struct vertex{
	  pair<int,int> pos[2];
	  int time;
   };

   int N[2],M[2];
   char board[NMAX][NMAX][2];
   int valid[5][NMAX][NMAX][TIME+2][2];

   int G[2];
   pair<int,int> gpos[GMAX][2];

   /*
     N:0
     W:1
     S:2
     E:3
   */
   int dir[GMAX][2];
   int len[GMAX][2];
   const pair<int,int> adj[4] = { make_pair(-1,0), make_pair(0,-1), make_pair(1,0), make_pair(0,1) };
   int ch;

   int boundary(pair<int,int> pos, int maze)
   {
       return (pos.x < 1 || pos.y < 1 || pos.x > N[maze] || pos.y > M[maze]); 
   }
   
   pair<int,int> getGuardPos(int guard, int time, int maze)
   {
	   int t;
	   pair<int,int> pos = gpos[guard][maze];
	   int d = dir[guard][maze];
       time %= (2*len[guard][maze]-2);
       if (time<0) time+=(2*len[guard][maze]-2);
       t = min(len[guard][maze]-1,time);

	   pos.x+=t*adj[d].x;
	   pos.y+=t*adj[d].y;

	   time-=t;
       d=(d+2)%4;
       pos.x+=time*adj[d].x;
	   pos.y+=time*adj[d].y;

	   return pos;
   }

   pair<int,int> moveRobot(pair<int,int> pos, int maze, int dir)
   {
	   ch = 0;
	   if (boundary(pos, maze)) return pos;
       pair<int,int> old=pos;
	   pos.x+=adj[dir].x;
       pos.y+=adj[dir].y;
	   if (!boundary(pos, maze)&&board[pos.x][pos.y][maze]=='#')return old;
	   ch=1;
	   return pos;
   }
   
   int isValid(int rel, pair<int,int> pos, int time, int maze)
   {
       if (valid[rel+1][pos.x][pos.y][time][maze]) return valid[rel+1][pos.x][pos.y][time][maze];

       valid[rel+1][pos.x][pos.y][time][maze]=0;

	   pair<int,int> guard,guard_old,old; 
	   old = rel<0?pos:make_pair(pos.x-adj[rel].x,pos.y-adj[rel].y);

       for(int i=0;i<G[maze];i++)
	   {
          guard = getGuardPos(i, time, maze);
		  guard_old = getGuardPos(i, time-1, maze);
          if (guard==pos) return 0;
          if (guard==old && guard_old==pos) return 0;
	   }
	   valid[rel+1][pos.x][pos.y][time][maze]=1;
       return 1;
   }

   int H, T;
   short dist[NMAX][NMAX][NMAX][NMAX][TIME];
   char prev[NMAX][NMAX][NMAX][NMAX][TIME];
   vertex prev_vertex[NMAX][NMAX][NMAX][NMAX][TIME];
   vertex Q[VMAX]; 
   vertex tar;

   int bfs(vertex src)
   {
	   vertex u,v;
	   Q[T++] = src;
	   dist[src.pos[0].x][src.pos[0].y][src.pos[1].x][src.pos[1].y][0] = 0;
       while(H<T)
	   {
          u = Q[H++];
		  if(boundary(u.pos[0],0)&&boundary(u.pos[1],1))
		  {
             tar=u;
			 return dist[u.pos[0].x][u.pos[0].y][u.pos[1].x][u.pos[1].y][u.time];
		  }
		  for(int i=0;i<4;i++)
		  {
			  v.time=(u.time+1)%TIME;
			  v.pos[0]=moveRobot(u.pos[0],0,i);
			  if (!isValid((ch?i:-1),v.pos[0],v.time,0)) continue;
              v.pos[1]=moveRobot(u.pos[1],1,i);
              if (!isValid((ch?i:-1),v.pos[1],v.time,1)) continue;
			  if (dist[v.pos[0].x][v.pos[0].y][v.pos[1].x][v.pos[1].y][v.time]>0) continue;

              dist[v.pos[0].x][v.pos[0].y][v.pos[1].x][v.pos[1].y][v.time] =\
                 dist[u.pos[0].x][u.pos[0].y][u.pos[1].x][u.pos[1].y][u.time] + 1;
              
              prev[v.pos[0].x][v.pos[0].y][v.pos[1].x][v.pos[1].y][v.time]=i;
              prev_vertex[v.pos[0].x][v.pos[0].y][v.pos[1].x][v.pos[1].y][v.time]=u;

			  Q[T++]=v;
		  }
	   }

       return -1;
   }

   void solve()
   {
      vertex st;
	  memset(valid,-1,sizeof(valid));

      for(int b=0;b<2;b++)
	  {
		  scanf("%d%d", &N[b],&M[b]);
          for(int i=0;i<N[b];i++)
		  {
			  for (int j=0;j<M[b];j++)
			  {
                  scanf(" %c", &board[i][j][b]);
				  if (board[i][j][b]!='X') continue;
                  board[i][j][b]='.';
				  st.pos[b]=make_pair(i,j);
		  	  }
		  }
          scanf("%d",&G[b]);
	      for (int i = 0; i < G[b]; i++)
		  {
              char c;
			  scanf("%d%d%d %c",&gpos[i][b].first,&gpos[i][b].second,&len[i][b],&c);
			  dir[i][b]=(c=='E'?3:(c=='S'?2:c=='W'));
		  }
	  }

	  st.time=0;
      int i = bfs(st);
   }
}