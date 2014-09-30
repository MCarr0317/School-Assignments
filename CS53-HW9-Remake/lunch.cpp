#include "lunch.h"


void Lunch::print_me(short Days)
{
  cout << "Trapped: " << (static_cast<float>(TrapCounter) / Days) * 100 << '%' << endl;
}

void Lunch::place_me(school & skool)
{
  LunchLoc.m_Xval = (skool.getSize() - 2);
  LunchLoc.m_Yval = (skool.getSize() - 2);
  skool.SetNewPosition(LunchLoc, LunchRep);
}

location rand_move(school & skool, Lunch & lunch)
{
  location LunchMoveTo;
  
  LunchMoveTo = lunch.LunchLoc.FindAdjacent();

  skool.SetNewPosition(lunch.LunchLoc, EMPTY);

  return LunchMoveTo;
}

void LunchStepAnalysis(school & skool, Lunch & lunch, janitor & jan, location & LunchMoveTo, bool & DayOver, bool & LunchTrapped)
{
  if (DayOver == false)
  {
  switch (skool.GetNewPosition(LunchMoveTo))
  {
    case EMPTY:
      lunch.LunchLoc = LunchMoveTo;
      skool.SetNewPosition(lunch.LunchLoc, lunch.LunchRep);
      break;
    case TRAP:
      lunch.TrapCounter++;
      lunch.LunchLoc = LunchMoveTo;
      skool.SetNewPosition(lunch.LunchLoc, lunch.LunchRep);
      LunchTrapped = true;
      break;
    case WALL:
    case WINDOW:
    case DRINK:
      skool.SetNewPosition(lunch.LunchLoc, lunch.LunchRep);
      break;
  }
  }
}
