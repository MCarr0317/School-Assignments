//Programmer: MATT CARR             Partners: JAMES GORDON, DANIEL MARTINEZ
//Class: CS 53 Sec e                File name: main.cpp
//Purpose: Driver to test code for homework 9.

#include "Header.h"
#include<iostream>
#include <ctime>
#include <cstdlib>
using namespace std;



int main()
{
  srand(time(NULL));

  school Skool(10);//creates a school 10 units wide
  
  janitor Willie("Willie");//creates a janitor object
 

  drink Drank[5];//creates 5 drink objects
  Lunch lunch;//creates a lunch object
  

  cout << Skool;//outputs an empty school
  cout << endl << Willie << endl;//outputs the stats of the janitor

  Willie.place_me(Skool);
  /*-sets the janloc x and y positions to the size/2, in this case 5
    -calls SetObjectPosition in skool class
    -it determines if the position passed(JanLoc) is within the range of the
     school
    -if true, sets the school array position to JanLoc
   */

  lunch.place_me(Skool);
  /*-calls Skool.getemptyadjacent
    -this returns a random empty spot in the school
    -sets this to LunchLoc
    -calls SetObjectPosition to set that position in the array to LunchLoc
  */

  for (int i = 0;i < MAX_DRINKS;i++)
  {
    Drank[i].place_me(Skool);
    /*-sets DrinkLoc to a random empty spot in the school
      -Calls SetObjectPosition to set it's DrinkLoc position in the school
    */
  }


for (int i = 0;i < 100;i++)
{
  Willie.rand_move(Skool, Drank[i]);
  /*-finds a random empty adjacent spot
    -the position JanLoc is in gets cleared 
    -looks at the new position and compares it to possible cases
    -sets the position after changing affected parts
  */
  lunch.rand_move(Skool);//same thing pretty much

  cout << Skool << endl;//outputs a school with everything inside it
}
  return 0;
}
