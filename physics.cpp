/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    Savannah Harvey
 * Summary:
 *    Calculate all the maths
 ************************************************************************/

#include "physics.h"

///************************************
// * PHYSICS : Pythagorean Theorem
// * c^2 = a^2 + b^2
// ************************************/
//double Physics::pythagoreanTheorem(double a, double b)
//{
//	return sqrt((a * a) + (b * b));
//}

 /************************************
  * PHYSICS : CALC GRAVITY
  *              r
  * g = g * ( ------- ) ^2
  *            r + h
  ************************************/
Acceleration Physics::calcGravity(double height, Angle a)
{
	Acceleration gravity;
	double gravityAccel;

	gravityAccel = 9.80665 * (6378000 / (6378000 + height)) * (6378000 / (6378000 + height));

	gravity.set(a, gravityAccel);

	return gravity;
}

/************************************
 * PHYSICS : CALC GRAVITY DIRECTION
 * d = atan(xe - xs, ye - ys)
 ************************************/
Angle Physics::calcGravityDirection(int x, int y)
{
	Angle gravityDirection;

	double d = atan2(0.0 - x, 0.0 - y); // x and y are switched

	gravityDirection.setRadians(d);

	return gravityDirection;
}

/************************************
 * PHYSICS : CALC HEIGHT FROM EARTH
 * c^2 = a^2 + b^2
 ************************************/
double Physics::calcHeight(double x, double y)
{
   double height = sqrt((x * x) + (y * y));
   return height;
}
