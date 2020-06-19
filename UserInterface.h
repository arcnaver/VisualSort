/*************************************************************
 *************************************************************
 *
 *   USERINTERFACE HEADER
 *
 *    This will provide the function declarations for the 
 *    UserInterface class. It houses the visuals and algorithms.
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
 *    Date: 6/19/2020
 *    Version: 1.0 
 *************************************************************
 *************************************************************/
//We need this for the graphics engine.
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

//Other includes.
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <chrono>
#include <windows.h>    /* for sleep */
#include <stack>        /* for stack */


/************************************************************************
 ************************************************************************
 * STRUCT: BARS
 * The bars are used to store values for sorting.
 * They will have a position, origin, and size. We will use the
 * bars to also draw and animate movement. Basically, this is what
 * is shown on the screen.
 *
 * To assign values:
 *    bars b1;
 *    b1.xPos = 4;
 *
 ***********************************************************************/
struct bars
{
   //Some simple variables. X and Y position, width, height.
   int xPos = 0;
   int yPos = 0;
   int width = 0;
   int height = 0;
   //Default the color to RED.
   olc::Pixel color = olc::RED;

   /*Is it smallest or largest?
     This is purely a helper variable for the 
     colorizer function.
   */
   bool smallest = false;
   bool largest = false;

   /*Set an origin. This will aid us in our animations and swapping
     bars around.
   */
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
   int i = 0;
   int j = 0;

   int swaps = 0;

   //int high = 0;
   //int low  = 0;

   float moveSpeed = 10.0f;
   bool finished = true;
   bool iterateNextJ = true;

   bool bubbleSortSelected = false;
   //bool quickSortSelected = false;
   bool selectSortSelected = false;

   //Getters
   int getScreenWid() { return ScreenWidth(); }
   int getMin() { return min; }
   int getMax() { return max; }
   int getFinished() { return finished; }
   int getI() { return i; }
   int getJ() { return j; }
   
   int getSwaps() { return swaps; }

   //int getHigh() { return high; }
   //int getLow() { return low; }

   bool getBubbleSortSelected() { return bubbleSortSelected; }
   //bool getQuickSortSelected() { return quickSortSelected; }
   bool getSelectSortSelected() { return selectSortSelected; }
   bool getIterateNextJ() { return iterateNextJ; }

   //Setters
   void setMin(int minNum) { this->min = minNum; }
   void setMax(int maxNum) { this->max = maxNum; }
   void setFinished(bool algoState) { this->finished = algoState; }
   void setI(int index) { this->i = index; }
   void setJ(int index) { this->j = index; }
   void setIterateNextJ(bool value) { this->iterateNextJ = value; }
   void setBubbleSortSelected(bool value) { this->bubbleSortSelected = value; }
   //void setQuickSortSelected(bool value) { this->quickSortSelected = value; }
   void setSelectSortSelected(bool value) { this->selectSortSelected = value; }
   //void setHigh(int value) { this->high = value; }
   //void setLow(int value) { this->low = value; }
   void setSwaps(int value) { this->swaps = value; }

   //dynamic Arrays
   //bars* data = new bars[arr_size];
   bars data[arr_size];
   //Draw our HUD
   void hud();
   

   //Draws a graph with horizontal and verticle axis
   void graph();
   

   //Button takes in x,y positions, width and height, a label, and color
   void button(int xPos, int yPos, int width, int height, std::string label, olc::Pixel labelColor, olc::Pixel fillColor);
    
   //Resets the variables and bars after a sort has finished
   void reset() { setI(0); setJ(0); populateArray(); setSizeFlags(); colorizor(); setFinished(true); setSwaps(0); }

   //User Input
   void getUserInput(float fElapsedTime);
      
   //Bubble sort
   void bubbleSort();

   //Mover
   void mover(int a, int b);

   //Selection sort
   void selectionSort();

   //Print score
   void printScore(int score);
   
public:
/********************************************************************************
 ********************************************************************************
 *Here are necessary functions that must be declared in order for the graphics
 *engine to work. We will keep them here and not place them over in the cpp file.
 ********************************************************************************
 ********************************************************************************/

/***************************************************
***   ON USER CREATE                               *
***   A mandatory part of the OLC Pixel Game Engine*
***   It is initiated only once. It is were we do  *
***   our primary initializations.                 *
***************************************************/
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

/***************************************************
***   ON USER UPDATE                               *
***   A mandatory part of the OLC Pixel Game Engine*
***   It is constantly updating. It is the         *
***   workhorse of the program.                    *
***************************************************/
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

      printScore(swaps);

      //mover(eTime);
      getUserInput(eTime);

      if (finished == false && bubbleSortSelected)
      {         
         bubbleSort();         
      }      
      else if (finished == false && selectSortSelected)
      {         
         selectionSort();
      }


      return true;

   }

};

/***************************************************
***   POPULATE ARRAY                               *
***   Populate the array with our bars struct.     *
***   It takes in data[] and initializes the       *
***   variables.
***************************************************/
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

/***************************************************
***   SET SIZE FLAGS                               *
***   Sets the smallest/largest flags in the       *
***   bars struct. It takes in two ints            *
***   smalles and largest.                         *
***************************************************/
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

/***************************************************
***   COLORIZOR                                    *
***   Loops through the array and colors the least *
***   and greatest value bars blue and red.        *
***************************************************/
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

/***************************************************
***   DRAW ARRAY                                   *
***   This will draw the array to the screen.      *
***************************************************/
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

/***************************************************
***   HUD                                          *
***   Creates the HUD for the Visual Sort Program. *
***************************************************/
inline void UserInterface::hud()
{
   //Make the strings here
   std::string welcome = "Welcome to the Visual Sort Program.";
   std::string select = "Please select an algorithm to test.";
   std::string msg = welcome + " " + select;
   std::string swaps = "Swaps: ";
   

   //Draw the title message
   DrawString(5, 5, msg, olc::WHITE, 1);
   
   //Draw iteration score
   DrawString(ScreenWidth() - 780, ScreenHeight() - 15, swaps, olc::WHITE, 1);
   

   //Create a horizontal line
   FillRect(0, 35, ScreenWidth(), 2, olc::GREEN);

   //Make a Bubble Sort button          
   button(ScreenWidth() - 790, 20, 116, 11, "1: Bubble Sort", olc::WHITE, olc::BLUE);
   button(ScreenWidth() - 670, 20, 116, 11, "2: Select Sort", olc::WHITE, olc::BLUE);
   button(ScreenWidth() - 550, 20, 70, 11,  "R: RESET", olc::WHITE, olc::RED);
   //light grey
   olc::Pixel lgrey(211, 211, 211);

   //Draw a graph
   graph();


}

/***************************************************
***   GRAPH                                        *
***   Draws a graph for the bars to populate on    *
***************************************************/
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

/***************************************************
***   BUTTON                                       *
***   Takes in x,y positions, width and height     *
***   a lable, and color for making a button.      *
***************************************************/
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

/***************************************************
***   GET USER INPUT                               *
***   Gets the users input. Handy for selecting    *
***   buttons.                                     *
***************************************************/
inline void UserInterface::getUserInput(float fElapsedTime)
{
   {
      // Tells us that key 1 has been pressed for BubbleSort.
      if (GetKey(olc::Key::K1).bPressed)
      {
         reset();
         //Let the system know we selected BubbleSort
         setBubbleSortSelected(true);
         //Ensure no other sorts are active
         //setQuickSortSelected(false);
         //We setFinished false so our loop can begin
         //for our bubble sort.
         setFinished(false);

         //Just a debug prompt
         std::cout << "K1 PRESSED: BubbleSort" << std::endl;

      }


      // Tells us that key 3 has been pressed for SelectionSort.
      if (GetKey(olc::Key::K2).bPressed)
      {
         reset();
         //Reset the variables
         setI(0);
         setJ(1);
         //Let the system know we selected BubbleSort
         setSelectSortSelected(true);
         //Ensure no other sorts are active
         setBubbleSortSelected(false);
         
         //We setFinished false so our loop can begin
         //for our bubble sort.
         setFinished(false);

         //Just a debug prompt
         std::cout << "K3 PRESSED: SelectionSort" << std::endl;

      }

      // This will reset the playing field
      if (GetKey(olc::Key::R).bPressed)
      {
         //The reset function will clear the variables and reset the bar array.
         reset();

         //Just a debug prompt
         std::cout << "Reset PRESSED: Now Resetting." << std::endl;
      }
   }
}


/***************************************************
***   BUBBLE SORT                                  *
***   This function impliments our bubble sort     *
***   algorithm.                                   *
***************************************************/
inline void UserInterface::bubbleSort()
{
   /*this takes the place of our nested for loop which would normally be found in a 
     bubble sort alogrithm. Because we are dealing with graphics it is necessary to
     have a global i and j variable, otherwise the bars would sort before the canvas
     had a chance to draw what happened. 
   */
   if (i < arr_size)
   {
      //Just a debug prompt
      std::cout << "In I " << i << std::endl;
      //This takes the place of our second for loop. It goes through the array 
      //multiple times, shringink with each i iteration. 
      if (j < arr_size - i - 1)
      {
         //Another debug prompt
         std::cout << "In J " << j << std::endl;

         /*This helps us make our comparisons. We could do it other ways but I
           thought this was clearer than checking if(data[j].height > data[j + 1].height).
           both ways are fine.
         */
         int a = data[j].height;
         int b = data[j + 1].height;
         
         if (a > b)
         {
            //I want to see the comparison, so I change the color to red, or any other color than
            //the original color.
            //data[j].color = olc::RED;
            data[j].color = olc::CYAN;

            //We call our helper function to move bars around for us. It wants two index values.
            //The current index, and the index we're comparing against. 
            mover(j, j + 1);
            
         }
         else
         {
            //I want to reset the color to the original color, which is green. This prevents sporadic
            //bars colorization.
            data[j].color = olc::GREEN;

            //Because we have to manually iterate our global j variable, we do so here with the set function.
            setJ(j += 1);
            
         }       
      }
      else
      {
         //Basically, if we've gone through the array of bars once already, we need to reset the j variable back to 0
         setJ(0);
         //We will also need to manually set the i variable now with its set function. This lets us go to the next i index and
         //start all over again.
         setI(i += 1);
         
      }

      //After trying many ways of making the color work, this is what I came up with. This makes sure the end (finished) bars are
      //RED so we can see the sort progression much easier. 
      data[arr_size - i].color = olc::RED;
      
   }
   else if (i == arr_size)
   {
      
      //If we've gone through everything, its time to break the loop. To do so, we setFinished to true. 
      setFinished(true);
   }   
}

/***************************************************
***   MOVER                                        *
***   This helper function aids the bubble sort    *
***   function in moving the bars around.          *
***************************************************/
inline void UserInterface::mover(int a, int b)
{        
   //We need to compare the bars x positions and move them to the correct spot on the screen.   
   if (data[a].xPos != data[b].origin && data[a].xPos < data[b].origin)
   {  
      /*This will animate the bar to the next bar position.
        Seven is how many spaces in x each bar is from the other. For slower
        movement, we could decrease this amount. Greater then 7 breaks the animation.
      */
      data[a].xPos += 7; 
   }
   else if (data[a].xPos > data[b].origin)
   {
      /*Origin is a helper variable that aids our animation. 
      If we accidently overshoot, this brings us back.*/
      data[a].xPos = data[b].origin;
         
         
      //setFinished(true);
   }

   /*This is the same as above, but in reverse.*/
   if (data[b].xPos != data[a].origin && data[b].xPos > data[a].origin)
   {                
      data[b].xPos -= 7; //Less than 7 helps us see more animated frame, more than 7 breaks it. 
   }
   else if (data[b].xPos < data[a].origin)
   {  
      /*Keeps us from overshooting in case of a higher speed than 7.*/
      data[b].xPos = data[a].origin;
      
   }

   /*House Keeping
     This section resets the origin variables and readjusts the array to
     a the sorted order so far. If we don't do this, our graphics are in order 
     but our array isnt.
   */
   if (data[a].xPos == data[b].origin && data[b].xPos == data[a].origin)
   {
      /*Just a debug statement. Tells us we're done with the current comparison.*/
      std::cout << "DONE" << std::endl;
      /*a is on the right now*/
      data[a].origin = data[a].xPos;
         
         
      /*b is on the left now*/
      data[b].origin = data[b].xPos;
         

      /*Now update the array by swapping them around to their correct positions
        Basically, this is just a typical swap function. We have to do it like
        this because we are dealing with the Pixel Game Engine.
      */
      bars temp;
      temp = data[a];
      data[a] = data[b];
      data[b] = temp;
      /*At this point we need to iterate our j.*/
      setJ(j += 1);
   }

   //Update the swap score in the HUD
   setSwaps(swaps += 1);

   /* These allow you to grab a bar and move it it around
      for testing. In this case, the bar at index 30.
   if (GetKey(olc::Key::RIGHT).bHeld) data[30].xPos += 1;
   if (GetKey(olc::Key::LEFT).bHeld) data[30].xPos -= 1;
   */
   
}


/**********************************************************
***   Select SORT                                         *
***   This function impliments our Select Sort            *
***   algorithm. It takes a size value previously found.  *
***                                                       *
***   https://www.geeksforgeeks.org/selection-sort/       *
**********************************************************/
void UserInterface::selectionSort()
{
   int data_size = sizeof(data) / sizeof(data[0]);
   
   //Minimum Index
   int minIndex;
   //Here we are moving the boundaries of the subarray. However,
   //insead of a for loop, we are forced to use an if statement
   //to track i similarly to what we did in bubble sort.
   if (i < data_size - 1)
   {
      //Now we need to find the smallest element in the unsorted array.
      minIndex = i;
      for (int k = i + 1; k < data_size; k++)
      {         
         if (data[k].height < data[minIndex].height)
         {
            minIndex = k;
         }
         
      }     
      //Now we need to swap the value found in the minimum element with the first.
      //selectMover(minIndex, i);
      mover(minIndex, i);
   }
   //So we can more easily see progress, change the bar color to red when it's done.
   data[i].color = olc::RED;
   setI(i += 1);
   
   //If we've reached the end we need to finish
   if (i == data_size)
   {
      std::cout << "Finished" << std::endl;
      setFinished(true);
   }

}

/**********************************************************
***   Print Score                                         *
***   This function allows us to print our swap score to  *
***   the HUD.                                            *
**********************************************************/
void UserInterface::printScore(int score)
{
   //Create the string
   std::string swaps = std::to_string(score);
   
   //Draw the label for the score
   DrawString(ScreenWidth() - 730, ScreenHeight() - 15, swaps, olc::WHITE, 1);
}