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
vector<int> DicesWithSideNumber[Max];

long long iteration, visitedSideNumbers[Max];
int sideNumbers[Max], dices[Max];

void AddDiceToStraight(int sideNumber, int diceNumber);
void RemoveDiceFromStraight(int sideNumber);
bool findDiceWithSideNumber(int sideNumber, int iteration);
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
		   DicesWithSideNumber[sideNumber].push_back(diceNumber);
	   }
	}
}

void cleanFlowGraph()
{
	for (int i = 1; i < Max; i++) 
	{
       sideNumbers[i] = NoFlow;
       visitedSideNumbers[i] = NotVisited;
    }

    for (int j = 1; j <= NumberOfDices; j++) 
	{
       dices[j] = NoFlow;
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
			if (findDiceWithSideNumber(straightRight + 1, iteration))
			{
                straightRight++;
			}
			else
			{
				break;
			}
		}

        maxStraight = max(maxStraight, straightRight - straightLeft + 1);

		if (sideNumbers[straightLeft] != NoFlow)
		{
            RemoveDiceFromStraight(straightLeft);
		}
	}
	return maxStraight;
}

bool findDiceWithSideNumber(int sideNumber, int iteration) 
{
    visitedSideNumbers[sideNumber] = iteration;

	for (int i = 0; i < DicesWithSideNumber[sideNumber].size(); i++)
	{
        int diceNumber = DicesWithSideNumber[sideNumber][i];
		if (dices[diceNumber] == NoFlow) 
	    {
            AddDiceToStraight(sideNumber, diceNumber);
		    return true;
	    }
	}

	for (int i = 0; i < DicesWithSideNumber[sideNumber].size(); i++)
	{
        int diceNumber = DicesWithSideNumber[sideNumber][i];
        bool wasNotVisited = visitedSideNumbers[dices[diceNumber]] != iteration;
	    if (wasNotVisited) 
	    {
		    if (findDiceWithSideNumber(dices[diceNumber], iteration)) 
		    {
                AddDiceToStraight(sideNumber, diceNumber);
                return true;
		    }
	    }
	}

    return false;
}

void AddDiceToStraight(int side, int dice) 
{
    sideNumbers[side] = dice;
    dices[dice] = side;
}

void RemoveDiceFromStraight(int side)
{
    dices[sideNumbers[side]] = NoFlow;
    sideNumbers[side] = NoFlow;
}
