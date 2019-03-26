#include "stdafx.h"
#include "type_printer.h"
#include <vector>  
#include <algorithm> 
#include <errno.h>
#include <math.h>  

using namespace System;
using namespace std;

struct str
{
   char s[30];
   void scan()
   {
      scanf("%s", s);     
   }
   bool operator <(const str &p)
   {
	  return strcmp(s, p.s) > 0;
   }
};

const int inf = 'z' + 1;
struct str s[25000];
int type_print_n;
vector<char> q;

bool str_comp(const str &x, const str &y)
{
   return strlen(x.s) > strlen(y.s);
}

void type_printer()
{
   scanf("%d", &type_print_n);
   for (int i = 0; i < type_print_n; i++)
   {
	   s[i].scan();
   }
   int max_el = min_element(s, s + type_print_n, str_comp) - s;
   swap(s[0], s[max_el]);
   for (int i = 1; i < type_print_n; i++)
	   for (int j = 0; s[i].s[j]; ++j)
		   if (s[0].s[j] == s[i].s[j]) s[i].s[j] = inf;

   sort(s + 1, s + type_print_n);
   char t[30] = "", p = 0;
   for (int i = type_print_n; i >= 0; i--)
   {
	   for (int j = 0; s[i].s[j]; ++j)
		   s[i].s[j] = s[0].s[j];

	   for (int j = 0; j < p; j++)
	   {
		   if (s[i].s[j] != t[j])
		   {
               while (j < p)
			   {
				   q.push_back('-');
				   --p;
			   }
			   break;
		   }
	   }

       for (int j = 0; s[i].s[j]; ++j)
	   {
		   q.push_back(t[p++] = s[i].s[j]);
	   }
	   q.push_back('P');
   }
}