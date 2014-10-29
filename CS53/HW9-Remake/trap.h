#ifndef TRAP_H
#define TRAP_H



#include "location.h"
#include "school.h"
class janitor;
class drink;
class Lunch;

struct Trap
{
  location TrapLoc;
  char TrapRep;
  int TrapCounter;
  public:
    Trap()
    {
      TrapRep = 'T';
      TrapCounter = 0;
    }
    void place_me(school & skool);
    friend void LunchStepAnalysis(school & skool, Lunch & lunch, location & LunchMoveTo, Trap & trap, bool & DayOver);
    friend void JanStepAnalysis(school & skool, janitor & jan, drink & drank, location JanMoveTo, Trap & trap, bool & DayOver);

};  

#endif
