//Programmer: MATT CARR             Partners: JAMES GORDON, DANIEL MARTINEZ
//Class: CS 53 Sec e                File name: Header.h
//Purpose: Header file for homework 9.

#ifndef HEADER_H
#define HEADER_H
#include <iostream>
using namespace std;

const int MAX = 25;
const int Size = 10;
const int MAX_DRINKS = 100;
const short SPACING = 4;
const char EMPTY = ' ', WALL = 'B', WINDOW = 'F', ERROR = '\0';;
enum Directions {DOWN, RIGHT, UP, LEFT, NUM_DIR};

struct location
{
  location():m_Xval(0), m_Yval(0){}
  location(const short X, const short Y):m_Xval(X), m_Yval(Y){}
  location FindAdjacent() const;
  
  int m_Xval;
  int m_Yval;
};

class school
{
  public:
    school(const int gridSize = MAX, short WindowSpacing = SPACING);

    char GetObjectPosition(const location Loc) const;
    bool SetObjectPosition(const location Loc, const char Representation);
    location GetEmptyAdjacent() const;
    friend ostream& operator<<(ostream& fout, const school & skool);
    //Get function
    int getSize()const {return ActualSize;}

  private:
    void build(const short WindowSpacing);
    bool InsideSchool(const location Loc) const;
    void clear();

    char School[MAX][MAX];
    short ActualSize;
};

class Lunch
{
  public:
   Lunch(const char LunchChar = 'L'):LunchLoc(-1, -1), LunchRep(LunchChar){}

   void place_me(school & skool);
   void rand_move(school & skool);
  private:
    location LunchLoc;
    char LunchRep;
};

class drink;
class janitor
{
  public:
   janitor (string name, char janchar = 'J')
   :bac(.05), Bruisecount(0), JanLoc(-1, -1), jancharacter(janchar), 
   sober(true), dead(false), jan_name(name){}
  

  void place_me(school & skool);
  void rand_move(school & skool, drink & drank);

  friend ostream& operator<<(ostream& fout, const janitor & jan); 
 
  private:
    float bac;
    int Bruisecount;
    char jancharacter;
    bool sober;
    bool dead;
    string jan_name;
    location JanLoc;
};

class drink
{
  public:
    drink();
    void place_me(school & skool);
    friend ostream& operator<<(ostream& fout, const drink & drank);
    friend void janitor::rand_move(school & skool, drink & drank);
  private:
    string Descr;
    float effect;
    location DrinkLoc;
    char DrinkRep;

};


#endif
