#include <iostream>
#include <string>
#include "hw01.hpp"
using namespace std;



int main()
{
  int NumPosters = 0, NumQueries = 0;
  string Title, Author;
  string *Queries;
  Poster *P;
  Poster *Q;
  cin >> NumPosters;

  P = new Poster[NumPosters];

  for (int k = 0;k < NumPosters;k++)
  {
    cin.ignore();
    getline(cin, Title);
    getline(cin, Author);

    P[k].set(Title, Author);

    cin >> P[k].no_tags;
    P[k].tags = new string[P[k].no_tags];

    for (int i = 0;i < P[k].no_tags;i++)
    {
      cin >> P[k].tags[i];
    }

  }

  cin >> NumQueries;
  cin.ignore();

  Queries = new string[NumQueries];

  for (int i = 0;i < NumQueries;i++)
  {
    getline(cin, Queries[i]);
  }

  int Counter = 0;

  for (int i = 0;i < NumQueries;i++)
  {
    cout << '#' << i << ':';
    for (int n = 0;n < NumPosters;n++)
    {
      for (int k = 0;k < P[n].no_tags; k++)
      { 
        if (Queries[i].compare(P[n].tags[k]) == 0)
        {
          cout << P[n].name << " by " << P[n].author << endl;
        }
      }
    }
    cout << endl;
  }


  delete [] Queries;
  delete [] P;

  return 0;
}
