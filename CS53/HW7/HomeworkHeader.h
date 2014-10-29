//Header file


#ifndef HOMEWORKHEADER_H
#define HOMEWORKHEADER_H

struct WillieStats
{
  int m_Bruises;
  int m_Falls;
  int m_FoundLunch;
  int m_Passouts;
};

template <class T>
bool CollisionDetection(const T& X1, const T& X2, const T& Y1, const T& Y2)
{
  if ((X1 == X2) && (Y1 == Y2))
  {
    return true;
  }
  else
  {
    return false;
  }
}









#endif
