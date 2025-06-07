/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      I did the math in the wrong order at one point. I was updating velocity before I moved position
 *      It was hard to find this bug, but we took a break from the code for a while and then I noticed it
 *      while i was reading the assignment of canvas.
 * 5. How long did it take for you to complete the assignment?
 *      not very long, probably about 3-4 hours for both of us.
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "acceleration.h"
#include "angle.h"
#include "physics.h"
#include "position.h"      // for POINT
#include "star.h"
#include <vector>
#include "test.h"
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) : ptUpperRight(ptUpperRight)
   {
      // We are doing hubble, set initial position and velocity
      ptHubble.setMetersX(0.0);
      ptHubble.setMetersY(42164000.0);
      dxHubble = -3100.0;
      dyHubble = 0.0;
      
      // put the ship at (0,0) to point at hubble.
      ptShip.setMetersX(0);
      ptShip.setMetersY(0);

      angleShip = 0.0;
      angleEarth = 0.0;
      phaseStar = 0;

      // Create 50 new stars with random positions
      for (int i = 0; i < 50; i++)
      {
         ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
         ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

         Star newStar;
         newStar.reset(ptStar);
         starVect.push_back(newStar);
      }
   }

   Position ptHubble;
   double dxHubble;
   double dyHubble;
   Position ptShip;
   Position ptStar;
   Position ptUpperRight;

   unsigned char phaseStar;
   double angleShip;
   double angleEarth;

   vector<Star> starVect;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Demo* pDemo = (Demo*)p;

   //
   // accept input
   //

   // move by a little
   if (pUI->isUp())
      pDemo->ptShip.addPixelsY(1.0);
   if (pUI->isDown())
      pDemo->ptShip.addPixelsY(-1.0);
   if (pUI->isLeft())
      pDemo->ptShip.addPixelsX(-1.0);
   if (pUI->isRight())
      pDemo->ptShip.addPixelsX(1.0);


   //
   // perform all the game logic
   //
   Physics phys;
   // position
   double x = pDemo->ptHubble.getMetersX();
   double y = pDemo->ptHubble.getMetersY();
   double height = phys.calcHeight(x, y); // should be 35786000.0;
   double t = 48;
   
   // set gravity
   Acceleration gravity( phys.calcGravity(height, phys.calcGravityDirection(x, y)) );

   // update position
   //   d = d0 + (v * t) + (a/2 * t * t) - distance formula, d = distance, d0 is starting point.
   x = pDemo->ptHubble.getMetersX() + (pDemo->dxHubble * t) + ((gravity.getDDX()/2) * t * t);
   y = pDemo->ptHubble.getMetersY() + (pDemo->dyHubble * t) + ((gravity.getDDY()/2) * t * t);
   
   // set position
   pDemo->ptHubble.setMetersX(x);
   pDemo->ptHubble.setMetersY(y);
   
   // update velocity
   // dx = dx + ddx * t
   // dy = dy + ddy * t
   pDemo->dxHubble = pDemo->dxHubble + (gravity.getDDX() * t);
   pDemo->dyHubble = pDemo->dyHubble + (gravity.getDDY() * t);

   // rotate the earth
   double td = 24 * 60;
   double rotationSpeed = -(2 * M_PI / 30) * (td / 86400 ); // should be 0.00349
   
   pDemo->angleEarth += rotationSpeed;
   pDemo->angleShip += rotationSpeed;
   pDemo->phaseStar++;

   //
   // draw everything
   //

   Position pt;
   ogstream gout(pt);
   
   // draw the earth
   gout.drawEarth(pt, pDemo->angleEarth);
   
   // draw satellites
   gout.drawHubble    (pDemo->ptHubble,     pDemo->angleShip);
   gout.drawShip      (pDemo->ptShip,       pDemo->angleShip, pUI->isSpace());

   // draw the stars
   for (int i = 0; i < 50; i++)
      pDemo->starVect[i].draw(gout);

   pt.setMeters(0.0, 0.0);
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{

   testRunner();

   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}
