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
 *    algorithms, starting with the bubble sort, and display
 *    a set of bars on the screen of varying heights. the bars
 *    will then be sorted. 
 *
 *    OLC's Pixel Game Engine is used as the Visual Element 
 *    of this program. It is the graphics library called by the
 *    classes and functions presented here.
 *    GITHUB:     https://github.com/OneLoneCoder 
 *    CITATION:   olc::PixelGameEngine, v2.05, OneLoneCoder.com, 2020
 *
 *    Part of its charm, is its retro pixelation. Therfore, any
 *    text or graphical element, will be reminiscent of a old
 *    8, 16, or 32 bit console game. 
 *
 *    Author: Adam Tipton
 *    Date: 5/23/2020
 *    Version: 0.2
 *************************************************************
 *************************************************************/
#include "UserInterface.h"
//This is the specifically for the olcPixelGameEngine
//#define OLC_PGE_APPLICATION
//#include "olcPixelGameEngine.h"
/*************************************************************/

/*
   We use #defines here only for convenience (and because the 
   olcPixelGameEngine shows it done this way. 
   Generally, it would be better to use const variables. 
   The PIXEL_SIZE sets the standard size of pixels used in the olc 
   graphics engine and must be set specifically. 
*/
#define SCREEN_W     800
#define SCREEN_H     400
#define PIXEL_SIZE   2

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
   if (UI.Construct(SCREEN_W, SCREEN_H, PIXEL_SIZE, PIXEL_SIZE))
   {
      UI.Start();
      return 0;
   }

   
}