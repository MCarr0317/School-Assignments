#ifndef LUNCH_H
#define LUNCH_H

#include "school.h"
#include <iostream>
using namespace std;
class janitor;
class drink;
class Trap;
class Lunch
{
  public:
   Lunch(const char LunchChar = 'L'):LunchLoc(-1, -1), LunchRep(LunchChar), TrapCounter(0){}

   void place_me(school & skool);
   friend location rand_move(school & skool, Lunch & lunch);
   friend location rand_move(school & skool, janitor & jan, Lunch & lunch);
   friend location location::CalculateAdjacent(const Lunch & lunch) const;
   friend void LunchStepAnalysis(school & skool, Lunch & lunch, janitor & jan,  
               location & Loc, bool & DayOver, bool & LunchTrapped);
   void print_me(short days);

  private:
    location LunchLoc;
    int TrapCounter;
    char LunchRep;
};
#endif
