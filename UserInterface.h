/*************************************************************
 *************************************************************
 *
 *   USERINTERFACE HEADER
 *
 *    This will provide the function declarations for the 
 *    UserInterface class.
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
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
//#include "olcPixelGameEngine.h" /* PixelGameEngine */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <chrono>
#include <windows.h>    /* for sleep */

/************************************************************************
 ************************************************************************
 * STRUCT: BARS
 * The bars are used to store values for sorting.
 * They will have a position and size.
 *
 * To assign values:
 *    bars b1;
 *    b1.xPos = 4;
 *
 ***********************************************************************/
struct bars
{
   int xPos = 0;
   int yPos = 0;
   int width = 0;
   int height = 0;
   //Just in case we need a color
   olc::Pixel color = olc::RED;

   //Is it smallest or largest?
   bool smallest = false;
   bool largest = false;

   //Set an origin 
   int origin;

};

/************************************************************************
 ************************************************************************
 * CLASS: USERINTERFACE
 * This class will define the set up for our canvas. In short it
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
   //Destructor
   ~UserInterface()
   {
      //Only if we use dynamic arrays
      //delete[]data;
   }

   //Populate the array with our struct. It grabs data[] and initializes the variables.
   void populateArray();
  
   //Sets the smallest/largest flags in the struct. It takes in two ints (smallest and largest)
   void setSizeFlags();
   
   //This will loop through and color the least and greatest value bar
   void colorizor();

   //This will draw the array to the screen for us
   void drawArray();
   

   //We put variables and functions here that we dont want others to mess with.
private:
   //Array Size
   const static int arr_size = 107;

   //Variables
   int min = 0;
   int max = 0;
   float moveSpeed = 10.0f;
   bool finished = true;


   //Getters
   int getScreenWid() { return ScreenWidth(); }
   int getMin() { return min; }
   int getMax() { return max; }
   int getFinished() { return finished; }

   //Setters
   void setMin(int minNum) { this->min = minNum; }
   void setMax(int maxNum) { this->max = maxNum; }
   void setFinished(bool algoState) { this->finished = algoState; }

   //dynamic Arrays
   //bars* data = new bars[arr_size];
   bars data[arr_size];
   //Draw our HUD
   void hud()
   {
      //Make the strings here
      std::string welcome = "Welcome to the Visual Sort Program.";
      std::string select = "Please select an algorithm to test.";
      std::string msg = welcome + " " + select;
      std::string bs = "Bubble Sort";

      //Draw the title message
      DrawString(5, 5, msg, olc::WHITE, 1);

      //Create a horizontal line
      FillRect(0, 35, ScreenWidth(), 2, olc::GREEN);

      //Make a Bubble Sort button          
      button(ScreenWidth() - 790, 20, 116, 11, "1: Bubble Sort", olc::WHITE, olc::BLUE);
      button(ScreenWidth() - 670, 20, 108, 11, "2: Quick Sort", olc::WHITE, olc::BLUE);
      //light grey
      olc::Pixel lgrey(211, 211, 211);

      //Draw a graph
      graph();


   }

   //Draws a graph with horizontal and verticle axis
   void graph();
   

   //Button takes in x,y positions, width and height, a label, and color
   void button(int xPos, int yPos, int width, int height, std::string label, olc::Pixel labelColor, olc::Pixel fillColor);
   

   //This will move the bars around   ******TEST FUNCTION*******
   bool mover(float fElapsedTime);
   

   //User Input
   void getUserInput(float fElapsedTime);
   

   

   /********************************************************************************
    *Here are necessary functions that must be declared in order for the graphics
    *engine to work. We will keep them here and not place them over in the cpp file.
    ********************************************************************************/
public:
   //runs once, anything we need to set up, do it here
   bool OnUserCreate() override
   {
      //Initial population of the array
      populateArray();
      //Set the size flags in the array
      setSizeFlags();
      //Color the smallest and largest bar
      colorizor();

      return true;
   }

   //Runs in a loop, constantly updated. It really is the workhorse of the program
   bool OnUserUpdate(float fElapsedTime) override
   {

      float eTime = fElapsedTime;
      //clear the screen to black each time (I believe this is automatic but better safe than sorry).
      Clear(olc::BLACK);
      //make our hud appear
      hud();
      //now draw the array to the screen
      drawArray();



      //mover(eTime);
      getUserInput(eTime);

      if (finished == false)
      {
         mover(eTime);
      }


      return true;

   }

};


//Populate the array with our struct. It grabs data[] and initializes the variables.
void UserInterface::populateArray()
{
   {
      //Max and min numbers
      int max = 0;
      int min = arr_size;
      //Counter
      int counter = 0;

      //Seed random number
      srand(time(NULL));
      //Populate Array      
      for (int i = 0; i < arr_size; i++)
      {
         //plug random number the ran variable
         int ran = rand() % 330 + 5;

         //Now, set the min and max variable
         if (ran < min)
         {
            min = ran;
            setMin(ran);
         }
         if (ran > max)
         {
            max = ran;
            setMax(ran);
         }

         //Just debugging to console to confirm our random number is correct
         std::cout << "Rand: " << ran << std::endl;
         //Variables
         int height = ran;                  //we stuff a random number in here
         int width = 5;                    //we want our bars to be 5 wide
         /*int yLevel     = 45;   this is more of a reminder of where the top level is
                                  we don't want our bars higher than this*/
         int bottom = ScreenHeight() - 22;  //We have to work upside down and subtract 22 from the height
         int barPos = bottom - height;    //the y bar position
         int initialPos = 24;                   //the x bar position
         int offset = width + 2;            //this spaces the bars


         //If i is 0 we need to draw it slightly differently, so the variables (initialPos)
         //is slightly different.
         if (i == 0)
         {
            //We grab the variables and stuff them into the struct
            data[i].xPos = initialPos;
            data[i].yPos = barPos;
            data[i].width = width;
            data[i].height = height;
            data[i].color = olc::GREEN;
            data[i].smallest = false;
            data[i].largest = false;
            data[i].origin = initialPos;

         }
         //Otherwise we stuff them like this
         else
         {
            //We grab the variables and stuff them into the struct
            data[i].xPos = initialPos + (i * offset);                 //This variable has on offset
            data[i].yPos = barPos;
            data[i].width = width;
            data[i].height = height;
            data[i].color = olc::GREEN;
            data[i].smallest = false;
            data[i].largest = false;
            data[i].origin = initialPos + (i * offset);

         }


         //Increment the counter for debugging
         counter++;
         //this is only for debugging to the console
         std::cout << "Struct " << i << " xPos: " << data[i].xPos
            << " yPos:  " << data[i].yPos
            << " width: " << data[i].width
            << " height: " << data[i].height
            << std::endl;
      }
      //Just for debuggin, lets us know our count
      std::cout << "Array Count: " << counter << std::endl;
      std::cout << "Min: " << min << std::endl;
      std::cout << "Max: " << max << std::endl;

   }
}

//Sets the smallest/largest flags in the struct. It takes in two ints (smallest and largest)
inline void UserInterface::setSizeFlags()
{
   {
      int smallest = getMin();
      int largest = getMax();

      //Check the array for the smallest and largest number and set the flags
      for (int i = 0; i < arr_size; i++)
      {
         //Check the height, if it matches smallest, set the flag true.
         if (data[i].height == smallest)
         {
            data[i].smallest = true;
         }
         else if (data[i].height == largest)
         {
            data[i].largest = true;
         }
         else
         {
            data[i].smallest = false;
            data[i].largest = false;
         }
      }
   }
}

//This will loop through and color the least and greatest value bar
inline void UserInterface::colorizor()
{

   {
      for (int i = 0; i < arr_size; i++)
      {
         //Color the minimum struct blue 
         if (data[i].smallest == true)
         {
            data[i].color = olc::BLUE;
         }
         //Collor the maximum struct red
         else if (data[i].largest == true)
         {
            data[i].color = olc::RED;
         }
      }
   }
}

//This will draw the array to the screen for us
inline void UserInterface::drawArray()
{
   {
      //Loop through the array arr_size times
      for (int i = 0; i < arr_size; i++)
      {
         FillRect(data[i].xPos, data[i].yPos, data[i].width, data[i].height, data[i].color);
      }
   }
}

//Draws a graph for the bars to populate on
inline void UserInterface::graph()
{
   {
      int x = 20;
      int y = 45;

      //Vertical bar in dark grey
      FillRect(x, y, 2, ScreenHeight() - 65, olc::DARK_GREY);
      //Height label
      DrawString(10, 45, "H", olc::WHITE, 1);
      //Horizontal bar in grey
      FillRect(x, ScreenHeight() - 20, ScreenWidth() - 49, 2, olc::GREY);
      //Width label
      DrawString(ScreenWidth() - 37, ScreenHeight() - 15, "W", olc::WHITE, 1);
   }
}

//Button takes in x,y positions, width and height, a label, and color
inline void UserInterface::button(int xPos, int yPos, int width, int height, std::string label, olc::Pixel labelColor, olc::Pixel fillColor)
{
   {

      //Create the shape of the button
      FillRect(xPos, yPos, width, height, fillColor);
      //Create the string
      DrawString(xPos + 3, yPos + 2, label, labelColor);


   }
}

//Test function to see how to move bars around
inline bool UserInterface::mover(float fElapsedTime)
{
   {
      bool isDone = false;
      if (data[10].height >= data[100].height)
      {
         if (data[10].xPos != data[100].origin)
         {
            data[10].color = olc::CYAN;
            data[10].xPos += 1 * int(moveSpeed);
         }
         else
         {
            data[10].color = olc::GREEN;
            isDone = true;
            setFinished(true);
         }
         if (data[100].xPos != data[10].origin)
         {
            data[100].color = olc::MAGENTA;
            data[100].xPos -= 1 * int(moveSpeed);
         }
         else
         {
            data[100].color = olc::GREEN;
         }
      }

      //data[0].xPos += 1;
      if (GetKey(olc::Key::RIGHT).bHeld) data[30].xPos += 1;
      if (GetKey(olc::Key::LEFT).bHeld) data[30].xPos -= 1;

      return isDone;
   }
}

//Gets the user input, handy for selecting buttons.
inline void UserInterface::getUserInput(float fElapsedTime)
{
   {
      // Get the mouse coordinates
      if (GetKey(olc::Key::K1).bPressed)
      {
         setFinished(false);
         std::cout << "PRESSED" << std::endl;

      }

      /*while (!getFinished())
      {
         mover(fElapsedTime);
      }*/
   }
}

