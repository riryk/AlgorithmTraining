
#include "stdafx.h"
#include <vector>  
#include <errno.h>
#include <math.h>  

using namespace System;
using namespace std;

typedef long double LongDouble;

const LongDouble smallDouble = 1e-9;

bool isSmall(LongDouble number) 
{
    return fabsl(number) < smallDouble;
}

typedef struct Point 
{
  LongDouble x, y, z;

  Point add(const Point& point) const 
  {
      Point newPoint;

	  newPoint.x = x + point.x;
	  newPoint.y = y + point.y;
	  newPoint.z = z + point.z;

      return newPoint;
  }

  Point substract(const Point& point) const 
  {
      Point newPoint;

	  newPoint.x = x - point.x;
	  newPoint.y = y - point.y;
	  newPoint.z = z - point.z;

      return newPoint;
  }

  LongDouble dotProduct(const Point& point) const 
  {
	  return x * point.x + y * point.y + z * point.z;
  }

  Point multiply(LongDouble constant) const 
  {
      Point newPoint;

	  newPoint.x = x * constant;
	  newPoint.y = y * constant;
	  newPoint.z = z * constant;

      return newPoint;
  }

  Point crossProduct(const Point& point) const 
  {
	  Point newPoint;

	  newPoint.x = y * point.z - z * point.y;
	  newPoint.y = z * point.x - x * point.z;
	  newPoint.z = x * point.y - y * point.x;

      return newPoint;
  }

  LongDouble distance() const 
  {
	  return sqrt((*this).dotProduct(*this));
  }

  LongDouble distance2() const 
  {
	  return (*this).dotProduct(*this);
  }

  Point normalize() const 
  {
      LongDouble dist = distance();

      Point newPoint;
	  newPoint.x = x / dist;
      newPoint.y = y / dist;
      newPoint.z = z / dist;

      return newPoint;
  }
};

int pointNumber;
vector<Point> points;

bool checkTwoPointsAndOriginOnTheSameLine(vector<Point> existingPoints);
bool isPointOnTheSameLineWithOneOfExistingPoints(vector<Point> existingPoints, Point newPoint, bool* isParalelWithExistingPoints);

int main(array<System::String ^> ^args)
{
	solve();

    return 0;
}

bool solve()
{
    vector<Point> existingPoints;
	if (checkTwoPointsAndOriginOnTheSameLine(existingPoints))
	{
        return true;    
	}
	return false;
}

bool checkTwoPointsAndOriginOnTheSameLine(vector<Point> existingPoints)
{
    existingPoints.push_back(points[0]);

    for (int i = 1; i < pointNumber; ++i)
	{
		bool isParalelWithExistingPoints = false;
		if (isPointOnTheSameLineWithOneOfExistingPoints(existingPoints, points[i], &isParalelWithExistingPoints))
		{
			return true;
		}
        
		if (!isParalelWithExistingPoints )
		{
            existingPoints.push_back(points[i]);
		}
	}

	return false;
}

bool isPointOnTheSameLineWithOneOfExistingPoints(vector<Point> existingPoints, Point newPoint, bool* isParalelWithExistingPoints)
{
    for (int pointIndex = 0; pointIndex < existingPoints.size(); pointIndex++)
	{
        Point existingPoint = existingPoints[pointIndex];

        bool vectorsAreParallel = isSmall(existingPoint.crossProduct(newPoint).distance2());
		if (vectorsAreParallel)
		{
			bool vectorsAreOpposite = existingPoint.dotProduct(newPoint) < 0;
			if (vectorsAreOpposite) 
			{
				return true;
			}
			*isParalelWithExistingPoints = true;
		}
	}

	return false;
}


