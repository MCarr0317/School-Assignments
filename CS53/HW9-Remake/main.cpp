#include <ctime>
#include <cstdlib>
#include "school.h"
#include "janitor.h"
#include "lunch.h"
#include "drink.h"
#include <fstream>
#include "trap.h"

int main()
{
  ifstream fin("config.dat");
 
  short Grid;
  short Num_drinks;
  short Num_traps;
  short Num_days;
  short Spacing;
  float AveBac = 0, Bac;

 fin >> Grid;
 fin >> Num_drinks;
 fin >> Num_traps;
 fin >> Num_days;
 fin >> Spacing;
 fin.close();

 srand(time(NULL));
  bool DayOver = false, LunchTrapped = false;

  school Skool(Spacing, Grid);//creates a school grid units wide

  janitor Willie("Willie");//creates a janitor object

  location NewJanLoc, NewLunchLoc;

  Trap T[Num_traps];

  drink Drank[Num_drinks];//creates 5 drink objects
  Lunch lunch;//creates a lunch object

  Willie.place_me(Skool);

  lunch.place_me(Skool);


for (int k = 0;k < Num_days;++k)
{
  Skool.clear();
  Skool.build(Spacing);

  /*placing everything*/
  Willie.place_me(Skool);            
  lunch.place_me(Skool);            
  for (int i = 0;i < Num_traps;i++) 
  {                                 
    T[i].place_me(Skool);           
  }                                 
                                    
  for (int i = 0;i < Num_drinks;i++)
  {
    Drank[i].place_me(Skool);
  }
  

   while (DayOver == false)
   {
     NewJanLoc = rand_move(Skool, Willie, lunch);
     for (int i = 0;i < Num_drinks;i++)
     {
       JanStepAnalysis(Skool, Willie, Drank[i], NewJanLoc, DayOver, LunchTrapped, AveBac);
     } 
      if (LunchTrapped == false)
      {
        NewLunchLoc = rand_move(Skool, lunch);
      }

     LunchStepAnalysis(Skool, lunch, Willie, NewLunchLoc, DayOver, LunchTrapped);
      

  if (DayOver == false)
  {
     cout << '\f';
     cout << "Day: " << 1 + k << endl;
     Bac = Willie.GetBac();
     cout << "Bac: " << Bac << endl;
     cout << Skool << endl;//outputs a school with everything inside it
     sleep(1);
  }
    
  }
  DayOver = false;
  LunchTrapped = false;
}
cout << "stats: " << endl;
Willie.print_me(Num_days);
cout << "Average bac: " << (AveBac / Num_days) << endl;
cout << endl;
cout << "lunch stats: " << endl;
lunch.print_me(Num_days);
  return 0;
}
