#ifndef JANITOR_H
#define JANITOR_H

#include <iostream>
#include <string>
#include "school.h"
#include "location.h"
#include "lunch.h"
#include "trap.h"

class drink;
using namespace std;

class janitor
{
  public:
   janitor (string name, char janchar = 'J')
   :bac(.05), Bruisecount(0), WindowExits(0), deaths(0), JanLoc(-1, -1), 
            jancharacter(janchar),sober(true), dead(false), jan_name(name), 
            LunchCounter(0){}

  float GetBac(){return bac;}
  void place_me(school & skool);
  friend location rand_move(school & skool, janitor & jan, Lunch & lunch);
  friend void JanStepAnalysis(school & skool, janitor & jan, 
              drink & drank, location JanMoveTo, bool & DayOver, bool & LunchTrapped, float & AveBac); 
  friend void LunchStepAnalysis(school & skool, Lunch & lunch, janitor & jan,
               location & Loc, bool & DayOver, bool & LunchTrapped);

 // friend ostream& operator<<(ostream& fout, const janitor & jan);
  void print_me(short Days);
  private:
    float bac;
    int Bruisecount;
    int WindowExits;
    int LunchCounter;
    char jancharacter;
    int deaths;
    bool sober;
    bool dead;
    string jan_name;
    location JanLoc;
};
#endif
