#include "stdafx.h"
#include <vector>  
#include <map>
#include <algorithm>
#include <errno.h>

using namespace System;
using namespace std;

#define min(a, b) a < b ? a : b
#define max(a, b) a > b ? a : b

struct coords {
  char x, y; 
  char* s;
  coords( int xx, int yy ) { x=xx; y=yy; }
  int id() { return 32*(int)x+(int)y; }
  friend bool operator  < ( coords a, coords b ) { return a.id()  < b.id(); }
  friend bool operator == ( coords a, coords b ) { return !(a<b) && !(b<a); }
};

struct state {
  char i, loup, hidown, loy, hiy;
  state() {}
  state( char ii, char lloup, char hhidown, char lloy, char hhiy ) 
  { i=ii; loup=lloup; hidown=hhidown; loy=lloy; hiy=hhiy; }
  int id() { return 32*(32*(32*(32*(int)i+(int)loup)+(int)hidown)+(int)loy)+(int)hiy; }
  friend bool operator < ( state a, state b ) { return a.id() < b.id(); }
};

map<state, short> memo;
vector<char> minx(32,32), maxx(32,0), miny(32,32), maxy(32,0);

int minrec(vector<coords> sorted, state s, int a, int n)
{
  if (s.i == n) return 0;
  if (memo.count(s)) return memo[s];
  
  short min = 1500;
  coords cur = sorted[s.i];
  if (minx[cur.y] == cur.x && cur.y < s.loup && cur.y > s.hidown) //left
  {  
	 state next = state(s.i + 1, s.loup, s.hidown, s.loy, s.hiy);
	 short cost = minrec(sorted, next, n) + cur.x;
	 if (cost < ret) ret = cost;
  }
  if (miny[cur.x] == cur.y && cur.y < s.loy) { //down
	 state next = state(s.i + 1, s.loup, max(cur.y, s.hidown), s.loy, s.hiy);
	 short cost = minrec(sorted, next, n) + cur.y; 
	 if (cost < ret) ret = cost;
  }
  if (maxy[cur.x] == cur.y && cur.y > s.hiy) { //up
	 state next = state(s.i + 1, min(cur.y, s.loup), s.loy, s.hiy);
	 short cost = minrec(sorted, next, n) + a - cur.y; 
	 if (cost < ret) ret = cost;
  }
  if (maxx[cur.y] == cur.x) { // right
	 state next = state(s.i + 1, s.loup, s.hidown, min(cur.y, s.loy), max(cur.y, s.hiy)); 
	 short cost = minrec(sorted, next, n) + a - cur.x; 
	 if (cost < ret) ret = cost;
  }

  return -1;
}

void minwires(vector<coords> juncs, int a, int n)
{
  vector<coords> sorted;
  for(int i = 0; i < juncs.size(); i++) {
	  minx[juncs[i].y] = min(minx[juncs[i].y], juncs[i].x);
	  maxx[juncs[i].y] = max(maxx[juncs[i].y], juncs[i].x);
	  miny[juncs[i].x] = min(miny[juncs[i].x], juncs[i].y);
      maxy[juncs[i].x] = max(miny[juncs[i].x], juncs[i].y);
  }
  sorted = juncs;
  sort(sorted.begin(), sorted.end());
  minrec(sorted, state(0, a, 0, a, 0), a, n);
}


