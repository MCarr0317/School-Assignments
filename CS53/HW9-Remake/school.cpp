#include "school.h"
         

school::school(short Windowspacing, const int gridSize)
{
  if (gridSize <= MAX)
  {
    ActualSize = gridSize;
  }
  else
  {
    ActualSize = MAX;
  }
  clear();
  build(Windowspacing);
}

char school::GetNewPosition(const location Loc) const
{
  if (InsideSchool(Loc))
  {
    return School[Loc.m_Yval][Loc.m_Xval];
  }

}

void  school::SetNewPosition(const location Loc, const char Representation)
{
  if (InsideSchool(Loc))
  {
    School[Loc.m_Yval][Loc.m_Xval] = Representation;
  }
}

bool school::InsideSchool(const location Loc) const
{
  if ((Loc.m_Xval >= 0 && Loc.m_Xval < ActualSize) &&
    (Loc.m_Yval >= 0 && Loc.m_Yval < ActualSize))
  {
    return true;
  }
  else
    return false;
}

location school::GetStartingPoint() const
{
  location Loc;

  do
  {
    Loc.m_Xval = rand() % (ActualSize - 2) + 1;
    Loc.m_Yval = rand() % (ActualSize - 2) + 1;
  } while (School[Loc.m_Yval][Loc.m_Xval] != EMPTY);

  return Loc;
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
    {//try nesting a loop for the windowspacing
      School[ActualSize - 1][i] = WINDOW;
      School[0][i] = WINDOW;
      School[i][ActualSize - 1] = WINDOW;
      School[i][0] = WINDOW;
    }
    else
    {
      School[ActualSize - 1][i] = WALL;
      School[0][i] = WALL;
      School[i][ActualSize - 1] = WALL;
      School[i][0] = WALL;
    }

}
