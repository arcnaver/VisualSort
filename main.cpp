/*************************************************************
 *************************************************************
 *
 *   MAIN
 *
 *    This Program will demonstrate sorts in a visual way.
 *    Sorting Algorithms are complex tools of varying complexity.
 *    It is a lot easier to comprehend what is happening when
 *    they are presented in a visual way.
 *
 *    The Visual Sort program will present several sorting
 *    algorithms, starting with the bubble sort, in a visual
 *    way. 
 *
 *    OLC's Pixel Game Engine is used as the Visual Element 
 *    of this program. It is the graphics library called by the
 *    classes and functions presented here.
 *    https://github.com/OneLoneCoder
 *    Part of its charm, is its retro pixelation. Therfore, any
 *    text or graphical element, will be reminiscent of a old
 *    8, 16, or 32 bit console game. 
 *
 *    Author: Adam Tipton
 *    Date: 5/14/2020
 *    Version: 0.1
 *************************************************************
 *************************************************************/

//This is the specifically for the olcPixelGameEngine
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
/*************************************************************/

/*
   We use #defines here only for convenience. Generally, it would be better
   to use const variables. 
   The PIXEL_SIZE sets the standard size of pixels used in the olc 
   graphics engine and must be set specifically. 
*/
#define SCREEN_H     800
#define SCREEN_W     400
#define PIXEL_SIZE   2

/************************************************************************
 ************************************************************************
 * INNER CLASS: USERINTERFACE
 * This inner class will define the set up for our canvas. In short it 
 * defines everything we will need to present things visually. It will 
 * inheret from the Pixel Game Engine
 ************************************************************************/
class UserInterface : public olc::PixelGameEngine
{
//These are public variables and methods. Anyone can access them directly. 
public:
   //Default constructor
   UserInterface()
   {
      //Name our app
      sAppName = "Visual Sort";
   }

   


//We put variables and functions here that we dont want others to mess with.
private:
   //Draw our HUD
   void hud()
   {
      std::string welcome  = "Welcome to the Visual Sort Program.";
      std::string select   = "Please select an algorithm to test.";
      std::string msg      = welcome + " " + select;
      std::string bs       = "Bubble Sort";
      
      //Draw the title message
      DrawString(5, 5, msg, olc::WHITE, 1);

      //Create a horizontal line
      FillRect(0, 35, ScreenWidth(), 2, olc::GREEN);

      //Make a Bubble Sort button          
      button(ScreenWidth() - 200, 20, 91, 11, "Bubble Sort", olc::WHITE, olc::BLUE);

      //light grey
      olc::Pixel lgrey(211, 211, 211);

      //Draw a graph
      graph();

      
   }

   //Draws a graph with horizontal and verticle axis
   void graph()
   {
      int x = 20;
      int y = 45;

      //Vertical bar in red
      FillRect(x, y, 2, ScreenHeight() - 65, olc::RED);
      //Height label
      DrawString(10, 45, "H", olc::WHITE, 1);
      //Horizontal bar in grey
      FillRect(x, ScreenHeight() - 20, ScreenWidth() - 50, 2, olc::GREY);
      //Width label
      DrawString(ScreenWidth() - 37, ScreenHeight() - 15, "W", olc::WHITE, 1);
   }
   //Button takes in x,y positions, widht and height, a label, and color
   void button(int xPos, int yPos, int width, int height, std::string label, olc::Pixel labelColor, olc::Pixel fillColor)
   {   

      //Create the shape of the button
      FillRect(xPos, yPos, width, height, fillColor);
      //Create the string
      DrawString(xPos + 3, yPos + 2, label, labelColor );
          

   }

//Here are necessary functions that must be declared in order for the graphics
//engine to work.
public:
   //runs once, anything we need to set up, do it here
   bool OnUserCreate() override
   {
      
      return true;
   }

   //Runs in a loop, constantly updated. It really is the workhorse of the program
   bool OnUserUpdate(float fElapsedTime) override
   {
      //make our hud appear
      hud();
      return true;
   }

};





/************************************************************************
 ************************************************************************
 * MAIN
 * This is where the program gets implimented. Everything starts from here.
 * However, OnUserCreate is the real workhorse. 
 ************************************************************************/
int main()
{
   //Create a UI object
   UserInterface UI;

   //Create the window
   if (UI.Construct(SCREEN_H, SCREEN_W, PIXEL_SIZE, PIXEL_SIZE))
   {
      UI.Start();
      return 0;
   }
}