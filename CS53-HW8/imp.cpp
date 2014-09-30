//Implementation file
#include "Header.h"
#include <fstream>

string RandomWord(ifstream & Stream, int Rand)
{
  string str;
  for (int i = 1;i < Rand; i++)
  {
    Stream >> str;
  }
  return str;
}
