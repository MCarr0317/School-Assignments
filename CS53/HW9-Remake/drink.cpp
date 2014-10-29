#include "drink.h"
#include <cstdlib>

drink::drink()
{
  bool Pos_or_neg;
  Pos_or_neg = rand() % 2;

  if (Pos_or_neg == 0)
  {
    effect = ((float)rand()/(float)RAND_MAX)/20.0 + 0.05;
    Descr = "Whiskey";
  }
  else
  {
    effect = 0 - (((float)rand()/(float)RAND_MAX)/1000.0 + 0.001);
    Descr = "Coffee";
  }
  DrinkRep = DRINK;
}

ostream& operator<<(ostream& fout, const drink & drank)
{
  fout << drank.Descr << endl;
}

void drink::place_me(school & skool)
{
  DrinkLoc = skool.GetStartingPoint();
  skool.SetNewPosition(DrinkLoc, DrinkRep);
}
