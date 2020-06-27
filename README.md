# VisualSort
A visual representation of sorting algorithms. 

The olcPixelGameEnginer is used as the graphics driver for this program.
https://github.com/OneLoneCoder

Visual Sort will offer a visual representation of several sorting algorithms, starting with bubble sort. The viewer will be presented with a graph and set of unsorted bars, which will then be sorted into their correct positions. 

Bubble Sort has been implemented.
Selection Sort has been implemented.

# Purpose
This is a personal portfolio project. I am trying to increase my knowledge of known sorting algorithms and hone my coding skills. 

# Code
The code is heavily commented. Unless the function is obvious, expect some sort of description of what each element does. Perhaps you can learn something as well along the way. 

# Lessons Learned
I'd really would've liked to have fully implimented cpp files with my headers. However, when I attempted to do so, I also ran into strange errors. I beleive this was due to the OneLoneCoder file, but I cannot be for sure. Everytime I tried to move code into a cpp file from the header, it broke everything. Therefore, you will see that the UserInterface.h has no companion .cpp. In the future, I would like to solve this issue, but for the purposes of this project I am satisfied. 

I was able to impliment two solid sorting algorithms in the code. The BubbleSort was the most challenging. Once I had gotten working I was worried I had done something wrong as it ran really slowly. However, I learned that all was well and that the Bubble Sort is inherently a very slow algorithm. You can see what I mean when you compare it to the speed of the Selection Sort, which is blazing fast in comparison.

Originally, I was going to impliment a Quick Sort, however, this proved to be too challenging for the purposes of this project. Quick Sort has some intricicies that make it difficult to deal with. I just couldn't get the algorithm straight because of the recursive nature of the algorithm and the way the OneLoneCoder code worked (Not OLC's fault, mine). The main issue had to do with redrawing the array at the appropriate time. A secondary issue was getting the algorithm to solve correctly, which it wouldn't for some unkown reason. Bars would dissappear from the HUD, shorter ones likely being obscured by taller ones, as it iterated through. I will have to dogear this for a futer implimentation. 

I'd like to have several more algorithms in the next iteration of this project. For now, however, I am proud of what I've created. See if you can improve on it. It shouldn't be too difficult. 

# Sources
OLC's Pixel Game Engine is used as the Visual Element 
     of this program. It is the graphics library called by the
     classes and functions presented here.
     GITHUB:     https://github.com/OneLoneCoder 
     CITATION:   olc::PixelGameEngine, v2.05, OneLoneCoder.com, 2020
     
Bubble Sort:
https://editor.p5js.org/codingtrain/sketches/3HVrL9m36
https://www.geeksforgeeks.org/bubble-sort/

Select Sort:
https://editor.p5js.org/codingtrain/sketches/vic6Qzo-j 
https://www.geeksforgeeks.org/selection-sort/ 
