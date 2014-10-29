#include "trap.h"

void Trap::place_me(school & skool)
{
  TrapLoc = skool.GetStartingPoint();
  skool.SetNewPosition(TrapLoc, TrapRep);
}
