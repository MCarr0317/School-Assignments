#include "janitor.h"

void janitor::print_me(short Days)
{
  cout << "Average bruises: " << static_cast<float>(Bruisecount) / Days << endl;
  cout << "Exits: " << (static_cast<float>(WindowExits) / Days) * 100 << '%' << endl;
  cout << "Deaths: " << (static_cast<float>(deaths) / Days) * 100 << '%' << endl;
  cout << "Catches: " << (static_cast<float>(LunchCounter) / Days) * 100 << '%' << endl;
}

void janitor::place_me(school & skool)
{
  JanLoc.m_Yval = 1;
  JanLoc.m_Xval = 1;

  skool.SetNewPosition(JanLoc, jancharacter);
}

location rand_move(school & skool, janitor & jan, Lunch & lunch)
{
  location JanMoveTo;

  skool.SetNewPosition(jan.JanLoc, EMPTY);
  
  if (jan.GetBac() >= 0.08)
  {
    JanMoveTo = jan.JanLoc.FindAdjacent();
  }
  else if (jan.GetBac() > 0 && jan.GetBac() < 0.08)
  {
    if (abs(lunch.LunchLoc.m_Xval - jan.JanLoc.m_Xval) <= EyeSight &&
         abs(lunch.LunchLoc.m_Yval - jan.JanLoc.m_Yval) <= EyeSight) 
    {
      JanMoveTo = jan.JanLoc.CalculateAdjacent(lunch);
    }
    else
      JanMoveTo = jan.JanLoc.FindAdjacent();
  }

  return JanMoveTo;

}

void JanStepAnalysis(school & skool, janitor & jan, drink & drank, 
                    location JanMoveTo, bool & DayOver, bool & LunchTrapped, float & AveBac)
{
   if (DayOver == false)
   {
   switch (skool.GetNewPosition(JanMoveTo))
  {
    case EMPTY:
      jan.JanLoc = JanMoveTo;
      skool.SetNewPosition(jan.JanLoc, jan.jancharacter);
      break;
    case WALL:
      jan.Bruisecount++;
      skool.SetNewPosition(jan.JanLoc, jan.jancharacter);
      break;
    case WINDOW:
      jan.WindowExits++;
      DayOver = true;
      AveBac += jan.bac;
      jan.bac = 0.05;
      break;
    case TRAP:
      jan.JanLoc = JanMoveTo;
      skool.SetNewPosition(jan.JanLoc, jan.jancharacter);
      jan.Bruisecount += 5;
      break;
    case DRINK:
      if (JanMoveTo.m_Xval == drank.DrinkLoc.m_Xval &&
           JanMoveTo.m_Yval == drank.DrinkLoc.m_Yval)
      {
      jan.JanLoc = JanMoveTo;
      jan.bac = jan.bac + drank.effect;
      if (jan.bac >= 0.45)
      {
        jan.dead = true;
        jan.deaths++;
        DayOver = true;
        AveBac += jan.bac;
        jan.bac = 0.5;
      }
      else if (jan.bac >= 0.08 && jan.bac < 0.45)
      {
        jan.sober = false;
      }
      skool.School[drank.DrinkLoc.m_Yval][drank.DrinkLoc.m_Xval] = EMPTY;
      skool.SetNewPosition(jan.JanLoc, jan.jancharacter);
      }
      break;
    case LUNCH:
        if (LunchTrapped == true)
        {
          skool.SetNewPosition(jan.JanLoc, EMPTY);
        }
        DayOver = true;
        AveBac += jan.bac;
        jan.LunchCounter++;
      break;
   }

  }
  else
    skool.School[jan.JanLoc.m_Yval][jan.JanLoc.m_Xval] = EMPTY;
}
