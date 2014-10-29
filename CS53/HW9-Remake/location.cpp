#include <cmath>
#include <cstdlib>
#include "school.h"
#include "location.h"
class lunch;


location location::FindAdjacent() const
{
  location Loc(m_Xval, m_Yval);


  int Movement = rand() % NUM_DIR;

  switch (Movement)
  {
    case DOWN:
      Loc.m_Yval++;
      break;
    case RIGHT:
      Loc.m_Xval++;
      break;
    case UP:
      Loc.m_Yval--;
      break;
    case LEFT:
      Loc.m_Xval--;
      break;
  }

  return Loc;
}

location location::CalculateAdjacent(const Lunch & lunch) const
{
  location Loc(m_Xval, m_Yval);

  int XDistance, YDistance, Movement;

  XDistance = abs(lunch.LunchLoc.m_Xval - Loc.m_Xval);
  YDistance = abs(lunch.LunchLoc.m_Yval - Loc.m_Yval);
  if (XDistance > YDistance)
  {
    if (lunch.LunchLoc.m_Xval > Loc.m_Xval)
      Loc.m_Xval++;
    else
      Loc.m_Xval--;
  }
  else if (XDistance < YDistance)
  {
    if (lunch.LunchLoc.m_Yval > Loc.m_Yval)
      Loc.m_Yval++;
    else
      Loc.m_Yval--;
  }
  else if (XDistance == YDistance)
  {
     Movement = rand() % (NUM_DIR/2);

    switch (Movement)
    {
    case 0:
      if (lunch.LunchLoc.m_Xval > Loc.m_Xval)
      {
        Loc.m_Xval++;
      }
      if (lunch.LunchLoc.m_Xval < Loc.m_Xval)
      {
        Loc.m_Xval--;
      }
      break;
    case 1:
      if (lunch.LunchLoc.m_Yval > Loc.m_Yval)
      {
        Loc.m_Yval++;
      }
      if (lunch.LunchLoc.m_Yval < Loc.m_Yval)
      {
        Loc.m_Yval--;
      }
      break;
    }
  }
  return Loc;
}
