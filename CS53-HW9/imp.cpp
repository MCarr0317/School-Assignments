////Programmer: MATT CARR             Partners: JAMES GORDON, DANIEL MARTINEZ
//Class: CS 53 Sec e                File name: Imp.cpp
//Purpose: Function defintion for homework 9.


#include "Header.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;


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
  DrinkRep = 'D';
}

ostream& operator<<(ostream& fout, const drink & drank)
{
  fout << drank.Descr << endl;
}

void drink::place_me(school & skool)
{
  DrinkLoc = skool.GetEmptyAdjacent();
  skool.SetObjectPosition(DrinkLoc, DrinkRep);
}

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


school::school(const int gridSize, short WindowSpacing)
{
  if (gridSize <= MAX)
  {
    ActualSize = gridSize;
  }
  else
  {
    ActualSize = MAX;
  }
  WindowSpacing = SPACING;
   clear();
  build(WindowSpacing);
}

char school::GetObjectPosition(const location Loc) const
{
  if (InsideSchool(Loc))
  {
    return School[Loc.m_Yval][Loc.m_Xval];
  }

}

bool school::SetObjectPosition(const location Loc, const char Representation)
{
  bool WithinRange = false;
  if (InsideSchool(Loc))
  {
    School[Loc.m_Yval][Loc.m_Xval] = Representation;
    WithinRange = true;
  }
  return WithinRange;
}
    
bool school::InsideSchool(const location Loc) const
{

return ((Loc.m_Xval >= 0 && Loc.m_Xval < ActualSize) && (Loc.m_Yval >= 0 && Loc.m_Yval < ActualSize));
}
 
location school::GetEmptyAdjacent() const
{
  location Loc;

  do
  {
    Loc.m_Xval = rand() % (ActualSize - 2) + 1;  
    Loc.m_Yval = rand() % (ActualSize - 2) + 1;
  } while (School[Loc.m_Yval][Loc.m_Xval] != EMPTY);

  return Loc;
}

void Lunch::place_me(school & skool)
{
  LunchLoc = skool.GetEmptyAdjacent();
  skool.SetObjectPosition(LunchLoc, LunchRep);
}

void Lunch::rand_move(school & skool)
{
  location AnotherLoc;
  AnotherLoc = LunchLoc.FindAdjacent();

  skool.SetObjectPosition(LunchLoc, EMPTY);
 
  switch (skool.GetObjectPosition(AnotherLoc))
  {
    case EMPTY:
      LunchLoc = AnotherLoc;
  }
 
  skool.SetObjectPosition(LunchLoc, LunchRep);
}

ostream& operator<<(ostream& fout, const school & skool)
{
  for (int i = 0;i < skool.ActualSize;++i)
  {
    for (int j = 0;j < skool.ActualSize;++j)
    {
      fout << skool.School[i][j] << EMPTY;
    }
    fout << endl;
  }

  return fout;
}

ostream& operator<<(ostream& fout, const janitor & jan)
{
  fout << jan.jan_name <<" is "<<(jan.dead? (jan.sober? "drunk" : "sober") : "dead") << endl; 
  fout <<" and the bac is " << jan.bac;

  return fout;
}

void janitor::place_me(school & skool)
{
  JanLoc.m_Xval = JanLoc.m_Yval = (skool.getSize() / 2); 
 
  skool.SetObjectPosition(JanLoc, jancharacter);
}

void janitor::rand_move(school & skool, drink & drank)
{
  location MoveTo;
  
  MoveTo = JanLoc.FindAdjacent();

  skool.SetObjectPosition(JanLoc, EMPTY);
  
  switch (skool.GetObjectPosition(MoveTo))
  {
    case EMPTY:
      JanLoc = MoveTo;
      break;
    case WALL:
      Bruisecount++;
      break;
    case 'D':
      bac = bac + drank.effect;
      if (bac >= 0.25)
      {
        dead = true;
      }
      else if (bac >= 0.08 && bac < 0.25)
      {
        sober = false;
      }
      cout << "Willie has stepped on " << drank.Descr << "!" << endl;
      cout << "His bac is " << bac << endl;
      break;
  }

  skool.SetObjectPosition(JanLoc, jancharacter);
}

void school::clear()//clears current data in school array
{
  for (int i = 0;i < ActualSize;i++)
  {
    for (int j = 0;j < ActualSize;j++)
    {
      School[i][j] = EMPTY;
    }
  }
  return;
}

void school::build(short WindowSpacing)
{
  for (int i = 0; i < ActualSize; i++)
    if (i > 0 && i < ActualSize - 1 && i % WindowSpacing == 0)
      School[i][0] = School[i][ActualSize - 1] = School[0][i]
                   = School[ActualSize - 1][i] = WINDOW;
    else
      School[i][0] = School[i][ActualSize - 1] = School[0][i]
                   = School[ActualSize - 1][i] = WALL;
}
