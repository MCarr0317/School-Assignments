#ifndef LOCATION_H
#define LOCATION_H
class Lunch;

struct location
{
  location():m_Xval(0), m_Yval(0){}
  location(const short X, const short Y):m_Xval(X), m_Yval(Y){}
  location FindAdjacent() const;
  location CalculateAdjacent(const Lunch & lunch) const;

  int m_Xval;
  int m_Yval;
};
#endif
