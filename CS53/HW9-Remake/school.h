#ifndef SCHOOL_H
#define SCHOOL_H

#include <iostream>
#include <cstdlib>
#include "location.h"
#include "drink.h"
#include "janitor.h"
using namespace std;

const int MAX = 25;
const int Size = 5;
const int EyeSight = 10;
const int MAX_DRINKS = 100;
const char LUNCH = 'L';
const char EMPTY = ' ', WALL = 'B', WINDOW = 'F', DRINK = 'D', TRAP = 'T';
enum Directions {DOWN, RIGHT, UP, LEFT, NUM_DIR};

class school
{
  public:
    school(short Windowspacing, const int gridSize = MAX);

    void Place_Traps(school & skool);
    char GetNewPosition(const location Loc) const;
    void SetNewPosition(const location Loc, const char Representation);
    location GetStartingPoint() const;
    friend ostream& operator<<(ostream& fout, const school & skool);
    int getSize()const {return ActualSize;}
    friend void JanStepAnalysis(school & skool, janitor & jan, drink & drank,
                    location JanMoveTo, bool & DayOver, bool & LunchTrapped, float & AveBac);
    void clear();
    void build(const short WindowSpacing);
    bool InsideSchool(const location Loc) const;
  private:

    char School[MAX][MAX];
    short ActualSize;
};
#endif
