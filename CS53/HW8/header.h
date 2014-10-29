#ifndef HEADER_H
#define HEADER_H
#include <iostream>
using namespace std;


//Pre: Rand value must be between 2 and 11
//Post: A random word is extracted from a data file
//Descr: This function returns a random word that is extracted from a data file
string RandomWord(ifstream & Stream, int Rand);

#endif
