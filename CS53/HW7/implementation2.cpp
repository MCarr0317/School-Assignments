 #include<iostream>
using namespace std;
#include<cstdlib>
#include<ctime>
#include "HomeWorkHeader.h"
int main()
{

  const int X = 17;
  const int Y = 17;
  const int NUMDAYS = 1;
  short StepCounter = 1;
  WillieStats Stats;
  srand(time(NULL));
  bool DayIsOver[NUMDAYS];
  const char Window = 'R';
  const char Wall = 'B';
  const char Lunch = 'S';
  const char Willie = 'J';
  short WillieXPos = 9;
  short WillieYPos = 9;
  short LunchXPos, LunchYPos;
  short WillieMovement;
  char School[Y][X];
  int Columns, Rows;
  Stats.m_Bruises = 0;
  Stats.m_Falls = 0;
  Stats.m_FoundLunch = 0;
  Stats.m_Passouts = 0;

  for (int i = 0;i < NUMDAYS;i++)
  {
    DayIsOver[i] = false;
  }

/*Making the school*/
  for (int Days = 0;Days < NUMDAYS;Days++)
  {
    do
    {
      LunchXPos = (rand() % 15) + 1;
      LunchYPos = (rand() % 15) + 1;
    } while (CollisionDetection(LunchXPos, LunchYPos, WillieXPos, WillieYPos) == true);
    StepCounter = 1;

        while (DayIsOver[Days] == false)
        {
        //Columns
          for (Columns = 0;Columns < Y;Columns++)
          {
            if (Columns % 5 == 0)
            {
              School[Columns][0] = Window;
            }
            else
            {
              School[Columns][0] = Wall;
            }
        
        //Rows
          for (Rows = 1;Rows < X;Rows++)
          {
            if (((Rows % 5 == 0) && (Columns == 0)) || ((Rows % 5 == 0) && (Columns == 16)))
            {
              School[Columns][Rows] = Window;
            }
            else if (((Rows % 5 != 0) && (Columns == 0)) || ((Rows % 5 != 0) && (Columns == 16)))
            {
              School[Columns][Rows] = Wall;
            }
            else if ((Columns == WillieYPos) && (Rows == WillieXPos))
            {
              School[Columns][Rows] = Willie;
            }
            else if ((Columns == LunchYPos) && (Rows == LunchXPos))
            {
              School[Columns][Rows] = Lunch;
            }
            else
            {
              School[Columns][Rows] = '\t';
            }
            cout << School[Columns][Rows] << ' ';
        }
     cout << endl;
     WillieMovement = rand() % 4;
     StepCounter++;

     switch (WillieMovement)
     {
       case 0:
         WillieYPos++;
         if  (CollisionDetection<short>(WillieXPos, WillieYPos, LunchXPos, LunchYPos) == true)
         {
           Stats.m_FoundLunch++;
           DayIsOver[Days] = true;
         }

         else if (School[WillieYPos][WillieXPos] == Wall)
         {
           Stats.m_Bruises++;
           WillieYPos--;
         }
         else if ((School[WillieYPos][WillieXPos] == Window) && (DayIsOver[Days] == false))
         {
           Stats.m_Falls++;
           WillieXPos = 9;
           WillieYPos = 9;
           DayIsOver[Days] = true;
         }
         else if ((StepCounter == 42) && (DayIsOver[Days] == false))
         {
           Stats.m_Passouts++;
           DayIsOver[Days] = true;
         }

         break;

       case 1:
         WillieXPos++;
         if  (CollisionDetection<short>(WillieXPos, WillieYPos, LunchXPos, LunchYPos) == true)
         {
           Stats.m_FoundLunch++;
           DayIsOver[Days] = true;
         }
         else if (School[WillieYPos][WillieXPos] == Wall)
         {
           Stats.m_Bruises++;
           WillieXPos--;
         }
         else if ((School[WillieYPos][WillieXPos] == Window) && (DayIsOver[Days] == false))
         {
           Stats.m_Falls++;
           WillieXPos = 9;
           WillieYPos = 9;
           DayIsOver[Days] = true;
         }
         else if ((StepCounter == 42) && (DayIsOver[Days] == false))
         {
           Stats.m_Passouts++;
           DayIsOver[Days] = true;
         }
         break;

       case 2:
         WillieYPos--;
         if  (CollisionDetection<short>(WillieXPos, WillieYPos, LunchXPos, LunchYPos) == true)
         {
           Stats.m_FoundLunch++;
           DayIsOver[Days] = true;
         }

         else if (School[WillieYPos][WillieXPos] == Wall)
         {
           Stats.m_Falls++;
           WillieYPos++;
         }
         else if ((School[WillieYPos][WillieXPos] == Window) && (DayIsOver[Days] == false))
         {
           Stats.m_Falls++;
           WillieXPos = 9;
           WillieYPos = 9;
           DayIsOver[Days] = true;
         }
         else if ((StepCounter == 42) && (DayIsOver[Days] == false))
         {
           Stats.m_Passouts++;
           DayIsOver[Days] = true;
         }
         break;

       case 3:
         WillieXPos--;
         if  (CollisionDetection<short>(WillieXPos, WillieYPos, LunchXPos, LunchYPos) == true)
         {
           Stats.m_FoundLunch++;
           DayIsOver[Days] = true;
         }

         else if (School[WillieYPos][WillieXPos] == Wall)
         {
           Stats.m_Bruises++;
           WillieXPos++;
         }
         else if ((School[WillieYPos][WillieXPos] == Window) && (DayIsOver[Days] == false))
         {
           Stats.m_Falls++;
           WillieXPos = 9;
           WillieYPos = 9;
           DayIsOver[Days] = true;
         }
         if ((StepCounter == 42) && (DayIsOver == false))
         {
           Stats.m_Passouts++;
           DayIsOver[Days] = true;
         }
         break;
      }
     }
    }
   }

/*Displaying data*/
cout<<"Bruises: "<<Stats.m_Bruises<<endl;
cout<<"Falls: "<<Stats.m_Falls<<endl;
cout<<"Passouts: "<<Stats.m_Passouts<<endl;
cout<<"Found lunch: "<<Stats.m_FoundLunch<<endl;









  return 0;
}
