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
 
namespace iowari
{ 
	enum RESULT 
	{
		UNKNOWN = -1,
		WIN,
        TIE,
		LOOSE
	};

	struct sstate
	{
		char pits[7];
        char bank;
		int sum() {
			return pits[0] + pits[1] + pits[2] + pits[3] + pits[4] + pits[5] + pits[6];
		}
	};

	typedef struct sstate state;

	char answer[6][6][6][6][6][6][6][21];
	char mymove[6][6][6][6][6][6][6][21];

	char get_answer(state s)
	{
		return answer[s.pits[0]][s.pits[1]][s.pits[2]][s.pits[3]][s.pits[4]][s.pits[5]][s.pits[6]][s.bank];
	}

    char get_mymove(state s)
	{
		return mymove[s.pits[0]][s.pits[1]][s.pits[2]][s.pits[3]][s.pits[4]][s.pits[5]][s.pits[6]][s.bank];
	}

    void make_move(state &s, int pit) 
	{
		s.bank = 20 - s.sum() - s.bank;
		int hand = s.pits[pit];
		s.pits[pit] = 0;
		for (pit = ++pit%7; hand > 0; pit = ++pit%7)
		{
           
		}
	}

	int solve(state s)
	{
	   if (s.sum() == 0) 
	   {
		   if (s.bank > 10) return WIN;
		   if (s.bank < 10) return LOOSE;
		   return TIE;
	   }
       
	   for (int i = 0; i < 7; i++) {
		   if (s.pits[i] != 0) {
               state next = s;
               make_move(next, i);
		   }
	   }

	   return 0;
	}

    void main()
	{
       state board;
	   for (int i = 0; i < 7; i++) scanf("%d", &board.pits[i]);

	   memset(answer, -1, sizeof(answer));
	   for(;;) 
	   {
		   if (board.sum() == 0) break;
           solve(board);
	   }
	}
}