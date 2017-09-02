// AlgorithmTraining.cpp : main project file.

#include "stdafx.h"
#include <vector>  
#include <errno.h>

using namespace System;
using namespace std;

const int Max = 1000010;
const int NoFlow = -1;
const int NotVisited = -1;

int NumberOfDices;
int DiceSides[Max][7];
vector<int> DiceSideBipartiteGrapgh[Max];

long long iteration, visitedSideNumbers[Max];
int leftFlow[Max], rightFlow[Max];

void AddFlow(int sideNumber, int diceNumber);
void RemoveFlow(int sideNumber);
bool depthFirstSearch(int sideNumber, int iteration);
void cleanFlowGraph();
void readDicesFromFileAndBuildGraph();
int findMaxStraight();

void findAndPrintMaxStraight()
{
	readDicesFromFileAndBuildGraph();
    cleanFlowGraph();
	findMaxStraight();
}

void readDicesFromFileAndBuildGraph()
{
	FILE* file = fopen("D:\\Logs\\input.txt", "r");
	if (file == NULL)
	{
	    printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
	}
    //freopen("input.txt", "r", stdin);
	fscanf(file, "%d", &NumberOfDices);

	for (int diceNumber = 1; diceNumber <= NumberOfDices; diceNumber++) 
	{
       for (int side = 0; side < 6; side++) 
	   {
           int sideNumber;
           fscanf(file, "%d", &sideNumber);  
		   DiceSides[diceNumber][side] = sideNumber;
		   DiceSideBipartiteGrapgh[sideNumber].push_back(diceNumber);
	   }
	}
}

void cleanFlowGraph()
{
	for (int i = 1; i < Max; i++) 
	{
       leftFlow[i] = NoFlow;
       visitedSideNumbers[i] = NotVisited;
    }

    for (int j = 1; j <= NumberOfDices; j++) 
	{
       rightFlow[j] = NoFlow;
    }
}

int findMaxStraight()
{
	int straightRight = 0;
	int iteration = 0;
	int maxStraight = 0;
	for (int straightLeft = 1; straightLeft < Max; straightLeft++) 
	{
        straightRight = max(straightRight, straightLeft - 1);     
        while (true)
		{
            iteration++;
			if (iteration == 4)
			{
                iteration = iteration;
			}
			if (depthFirstSearch(straightRight + 1, iteration))
			{
                straightRight++;
			}
			else
			{
				break;
			}
		}

        maxStraight = max(maxStraight, straightRight - straightLeft + 1);

		if (leftFlow[straightLeft] != NoFlow)
		{
            RemoveFlow(straightLeft);
		}
	}
	return maxStraight;
}

bool depthFirstSearch(int sideNumber, int iteration) 
{
    visitedSideNumbers[sideNumber] = iteration;

	for (int i = 0; i < DiceSideBipartiteGrapgh[sideNumber].size(); i++)
	{
        int diceNumber = DiceSideBipartiteGrapgh[sideNumber][i];

		if (rightFlow[diceNumber] == NoFlow) 
	    {
            AddFlow(sideNumber, diceNumber);
		    return true;
	    }
	}

	for (int i = 0; i < DiceSideBipartiteGrapgh[sideNumber].size(); i++)
	{
        int diceNumber = DiceSideBipartiteGrapgh[sideNumber][i];
        bool wasNotVisited = visitedSideNumbers[rightFlow[diceNumber]] != iteration;
	    if (wasNotVisited) 
	    {
		    if (depthFirstSearch(rightFlow[diceNumber], iteration)) 
		    {
                AddFlow(sideNumber, diceNumber);
                return true;
		    }
	    }
	}

    return false;
}

void AddFlow(int sideNumber, int diceNumber) 
{
    leftFlow[sideNumber] = diceNumber;
    rightFlow[diceNumber] = sideNumber;
}

void RemoveFlow(int sideNumber)
{
    rightFlow[leftFlow[sideNumber]] = NoFlow;
    leftFlow[sideNumber] = NoFlow;
}
