//MATT CARR
//File: main.cpp
//11/7/11
//Description: this program replaces marked words in a story with a random word from selected data files.


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string.h>
#include "Header.h"
using namespace std;


int main () 
{
  srand(time(NULL));
  const int MAX = 256;
  char str[MAX];
  int Rand;
  ifstream finStory("Story.dat"), finNoun, finNounP;
  ifstream finVerbP, finAdj, finVerb;
  ofstream fout("Output.dat");
  char nounp[MAX] = "*nounp*", verbp[MAX] = "*verbp*", adj[MAX] = "*adj*";
  char noun[MAX] = "*nouns*", verb[MAX] = "*verb*";

  //variables for special situations
  char nounQuotes[MAX] = "*nouns*!\"", nounPeriod[MAX] = "*nouns*.";
  char nounComma[MAX] = "*nouns*,";
  char nounpQuotes[MAX] = "*nounp*!\"", nounpPeriod[MAX] = "*nounp*.";
  char nounpComma[MAX] = "*nounp*,";
  char VerbQuotes[MAX] = "*verb*!", VerbPeriod[MAX] = "*verb*.";
  char VerbComma[MAX] = "*verb*,";
  char VerbpQuotes[MAX] = "*verbp*!\"", VerbpPeriod[MAX] = "*verbp*.";
  char VerbpComma[MAX] = "*verbp*,";
  char adjQuotes[MAX] = "*adj*!", adjPeriod[MAX] = "*adj*.";
  char adjComma[MAX] = "*adj*,";

  bool Done = false;

  //Echo to screen and write to ouput file
  while (finStory >> str)     
  {
    cout << str << ' ';
    fout << str << ' ';
  }
  cout << endl << endl;
  fout.close();
  finStory.close();
  finStory.open("Story.dat");

  
  cout << "Generating changed story..." << endl << endl;

 
  //Where the magic happens
  while (Done == false)
  {
    Rand = rand() % 10 + 2;
    //opening all files to reset cursor at beginning
    finNounP.open("nounp.dat");
    finNoun.open("nouns.dat");
    finVerbP.open("verbp.dat");
    finAdj.open("adj.dat");
    finVerb.open("verbs.dat");
    
    //preventing the 10 from being read in each file
    finNounP >> str;
    finNoun >> str;
    finVerbP >> str;
    finAdj >> str;
    finVerb >> str;

    finStory >> str;
   
   /* Replacement logic */

      //NounP
      if (strcmp(str, nounp) == 0)
      {
        cout << RandomWord(finNounP, Rand) << ' ';
      }
      else if (strcmp(str, nounpQuotes) == 0) 
      {
        cout << RandomWord(finNounP, Rand) << "!\" ";
      }
      else if (strcmp(str, nounpPeriod) == 0)
      {
        cout << RandomWord(finNounP, Rand) << ". ";
      }
      else if (strcmp(str, nounpComma) == 0)
     {
        cout << RandomWord(finNounP, Rand) << ", ";
      }

    
      //VerbP
      else if (strcmp(str, verbp) == 0)
      {
        cout << RandomWord(finVerbP, Rand) << ' ';
      }
      else if (strcmp(str, VerbpQuotes) == 0)
      {
        cout << RandomWord(finVerbP, Rand) << "!\" ";
      }
      else if (strcmp(str, VerbpPeriod) == 0)
      {
        cout << RandomWord(finVerbP, Rand) << ". ";
      }
      else if (strcmp(str, VerbpComma) == 0)
      {
        cout << RandomWord(finVerbP, Rand) << ", ";
      }

      //Adj
      else if (strcmp(str, adj) == 0)
      {
        cout << RandomWord(finAdj, Rand) << ' ';
      }
      else if (strcmp(str, adjQuotes) == 0)
      {
        cout << RandomWord(finAdj, Rand) << "!\" ";
      }
      else if (strcmp(str, adjPeriod) == 0)
      {
        cout << RandomWord(finAdj, Rand) << ". ";
      }
      else if (strcmp(str, adjComma) == 0)
      {
        cout << RandomWord(finAdj, Rand) << ", ";

      }
      //Noun
      else if (strcmp(str, noun) == 0)
      {
        cout << RandomWord(finNoun, Rand) << ' ';
      }
      else if (strcmp(str, nounQuotes) == 0)
      {
        cout << RandomWord(finNoun, Rand) << "!\" ";
      }
      else if (strcmp(str, nounPeriod) == 0)
      {
        cout << RandomWord(finNoun, Rand) << ". ";
      }
      else if (strcmp(str, nounComma) == 0)
      {
        cout << RandomWord(finNoun, Rand) << ", ";
      }

      //Verb
      else if (strcmp(str, verb) == 0)
      {
        cout << RandomWord(finVerb, Rand) << ' ';
      }
     else if (strcmp(str, VerbQuotes) == 0)
      {
        cout << RandomWord(finVerb, Rand) << "!\" ";
      }
      else if (strcmp(str, VerbPeriod) == 0)
      {
        cout << RandomWord(finVerb, Rand)  << ". ";
      }
     else if (strcmp(str, VerbComma) == 0)
     {
        cout << RandomWord(finVerb, Rand)  << ", ";
     }


    //determine when to end loop
    else if (finStory.eof())
    {
      Done = true;
    }
  
    //If not a marked word
    else
    {
      cout << str << ' ';
    }
    
  //closing streams
  finNounP.close();
  finVerbP.close();
  finAdj.close();
  finNoun.close();
  finVerb.close();
  }
  
  cout << endl << endl << "the story was succesfully changed." << endl;

  return 0;
}
