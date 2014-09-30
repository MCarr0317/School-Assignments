#ifndef DRINK_H
#define DRINK_H

#include "location.h"
#include <fstream>
#include <iostream>
class school;
class janitor;
#include "lunch.h"
#include "trap.h"
using namespace std;

class drink
{
  public:
    drink();
    void place_me(school & skool);
    friend ostream& operator<<(ostream& fout, const drink & drank);
    friend location rand_move(school & skool, janitor & jan);
    friend void JanStepAnalysis(school & skool, janitor & jan, drink & drank, location JanMoveTo, bool & DayOver, bool & LunchTrapped, float & AveBac);

  private:
    string Descr;
    float effect;
    location DrinkLoc;
    char DrinkRep;

};
#endif
