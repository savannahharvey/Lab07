/***********************************************************************
 * Header File:
 *    PHYSICS
 * Author:
 *    Savannah Harvey
 * Summary:
 *    Calculate all the maths
 ************************************************************************/

#pragma once

#include "angle.h"
#include "acceleration.h"
#include "velocity.h"
#include <cmath>

 /************************************
  * PHYSICS
  ************************************/
class Physics
{
public:
	Physics() {}

	//double pythagoreanTheorem(double a, double b); // only if we need it
	Acceleration calcGravity(double height, Angle a);
	Angle calcGravityDirection(int x, int y);
	Velocity calcVelocity(Angle a, Acceleration accel);
	double calcHeight(double x, double y);
};
