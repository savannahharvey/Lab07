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
#include <cmath>

 /************************************
  * PHYSICS
  ************************************/
class Physics
{
public:
	Physics() {}

	Acceleration calcGravity(double height, Angle a);
	Angle calcGravityDirection(int x, int y);
	double calcHeight(double x, double y);
};
