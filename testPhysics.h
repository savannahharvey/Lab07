/***********************************************************************
 * Header File:
 *    Test Position : Test the Position class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the unit tests for Position
 ************************************************************************/


#pragma once

#include "physics.h"
#include "unitTest.h"
#include "angle.h"
#include "acceleration.h"

 /*******************************
  * TEST Physics
  * A friend class for Physics which contains the Physics unit tests
  ********************************/
class TestPhysics : public UnitTest
{
public:
   void run()
   {
      // Calculations
      calcGravity_0();
      calcGravity_Pi();
      calcGravity_example();
      calcGravityDirection_3_14();
      calcVelocity_0();

      report("Physics");
   }

private:
   void calcGravity_0()
   {
      // setup
      Physics phys;
      double height = 35786000.0;
      Angle angle;
      angle.radians = 0.0;

      Acceleration a;

      // exercise
      a = phys.calcGravity(height, angle);

      // verify
      assertEquals(a.ddx, 0.0);
      assertEquals(a.ddy, 0.2243913421);
      assertEquals(angle.radians, 0.0);
      assertEquals(height, 35786000.0);
      // teardown
   }

   void calcGravity_Pi()
   {
      // setup
      Physics phys;
      double height = 35786000.0;
      Angle angle;
      angle.radians = M_PI;

      Acceleration a;

      // exercise
      a = phys.calcGravity(height, angle);

      // verify
      assertEquals(a.ddx, 0.0);
      assertEquals(a.ddy, -0.2243913421);
      assertEquals(angle.radians, M_PI);
      assertEquals(height, 35786000.0);
      // teardown
   }

   void calcGravity_example()
   {
      // setup
      Physics phys;
      double height = 35786000.0;
      Angle angle;
      angle.radians = 0.523599;

      Acceleration a;

      // exercise
      a = phys.calcGravity(height, angle);
      std::cout << std::fixed << std::setprecision(10) << a.ddx << std::endl;
      std::cout << std::fixed << std::setprecision(10) << a.ddy << std::endl;

      // verify
      assertEquals(a.ddx, 0.1122);
      assertEquals(a.ddy, 0.1943);
      assertEquals(angle.radians, 0.523599);
      assertEquals(height, 35786000.0);
      // teardown
   }

   void calcVelocity_0()
   {
      // setup
      Physics phys;
      int x = 21082000;
      int y = 36515095;

      Acceleration a;
      a.ddx = 0.1121957146;
      a.ddy = 0.1943285774;

      Angle d;
      d.radians = 0.523599;

      Velocity v;

      // exercise
      v = phys.calcVelocity(d, a);
      std::cout << v.dx << endl;
      std::cout << v.dy << endl;
      std::cout << endl;

      // verify
      assertEquals(v.dx, -2690.0);
      assertEquals(v.dy, -1541.0);
      // teardown
   }

   void calcGravityDirection_3_14()
   {
      // setup
      Physics phys;
      int x = 0;
      int y = 42164000;

      Angle d;
      d.radians = 0.0;

      // exercise
      d = phys.calcGravityDirection(x, y);

      // verify
      assertEquals(d.radians, 3.14159);
      // teardown
   }
};