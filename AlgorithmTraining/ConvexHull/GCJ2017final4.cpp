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
bool checkThirdPointIsAboveFirstTwoPointsPlane(vector<Point> points, int pointA, int pointB, int pointC);
int findSecondPointOfPlanePassingOriginAndTouchingConvexHull(vector<Point> existingPoints, int firstPoint);
bool checkTrianleCoversOrigin(vector<Point> points, int pointA, int pointB, int pointC);
bool checkPointsAreOnOneSideOfPlaneContainingOrigin(vector<Point> existingPoints);

bool solve()
{
    vector<Point> existingPoints;
	  if (checkTwoPointsAndOriginOnTheSameLine(existingPoints))
	  {
        return true;    
    }
    if (checkPointsAreOnOneSideOfPlaneContainingOrigin(existingPoints))
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
		    if (!vectorsAreParallel) 
		    {
			      continue; 
  		  }
		    *isParalelWithExistingPoints = true;

		    bool vectorsAreOpposite = existingPoint.dotProduct(newPoint) < 0;
		    if (vectorsAreOpposite) 
		    {
			      return true;
		    }
	  }

	  return false;
}

bool checkPointsAreOnOneSideOfPlaneContainingOrigin(vector<Point> existingPoints)
{
    for (int firstPoint = 0; firstPoint < existingPoints.size(); firstPoint++)
    {
        int secondPoint = findSecondPointOfPlanePassingOriginAndTouchingConvexHull(existingPoints, firstPoint);

        for (int thirdPoint = 0; thirdPoint < existingPoints.size(); thirdPoint++)
        {
            if (thirdPoint == firstPoint || thirdPoint == secondPoint)
               continue;     
            
            LongDouble normThirdPointDotProduct = points[firstPoint].crossProduct(points[secondPoint])
                                                                .dotProduct(points[thirdPoint]);
            bool pointsAreOnTheSamePlane = isSmall(normThirdPointDotProduct);
            bool thirdPointIsAboveThePlane = normThirdPointDotProduct > 0;
            if (pointsAreOnTheSamePlane && checkTrianleCoversOrigin(points, firstPoint, secondPoint, thirdPoint)) 
            {
                return false;
            }
            else if (thirdPointIsAboveThePlane) 
            {
                return false; 
            }
        }
    }

    return true;
}

bool checkTrianleCoversOrigin(vector<Point> points, int pointA, int pointB, int pointC)
{
    Point normAB = points[pointA].crossProduct(points[pointB]);
    Point normAC = points[pointA].crossProduct(points[pointC]);
    return normAB.dotProduct(normAC) < 0;
}

int findSecondPointOfPlanePassingOriginAndTouchingConvexHull(vector<Point> existingPoints, int firstPoint)
{
    int secondPoint = firstPoint == 1 ? 0 : 1;   
    for (int thirdPoint = 0; thirdPoint < existingPoints.size(); thirdPoint++)
    {
        if (thirdPoint == firstPoint || thirdPoint == secondPoint)
            continue;

        if (checkThirdPointIsAboveFirstTwoPointsPlane(existingPoints, firstPoint, secondPoint, thirdPoint))
        {
            secondPoint = thirdPoint; 
        }      
    } 
    return secondPoint;
}

bool checkThirdPointIsAboveFirstTwoPointsPlane(vector<Point> points, int pointA, int pointB, int pointC) 
{
    Point planeNorm = points[pointA].crossProduct(points[pointB]);
    
    return planeNorm.dotProduct(points[pointC]) > 0;
}
