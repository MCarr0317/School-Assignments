//Programmer: MATT CARR Date: 10-12-11
//File: Hw6Header.h
//Description: This is the header file for homework 6, containing
//  all of the function prototypes

#ifndef HW6HEADER_H
#define HW6HEADER_H

#include<iostream>
#include<cstdlib>
using namespace std;

//Pre:the phrase is a string
//Post: a message is displayed
//Descr: Displays the message that is passed to the function
void Prompt(string Phrase);

//Pre: n must be positive
//Post: calculates the nth root of Num
//Calculates the nth root of a user specified number, returns answer
double NthRoot(const double Num, const short n, const double StartValue);

//Pre: n must be an integer
//Post: Calculates the value of Xn to the power n
//Descr: calculates the value of Xn to the power n, returns result
double Num_To_Exponent(const double Xn, const short n);

//Pre: x must be positive
//Post: calculates e to the power of x
//Descr: returns value of e to the power of x
double e_to_x(const double x);

//Pre: n must be a positive integer
//Post: calculates the factorial of n
//returns value of n factorial
double Factorial(const short n);

//Pre: Num must be positive
//Post: calculates the hyperbolic sine of num
//returns value of the hyperbolic sine of num
double HyperbolicSine(const double Num);

//Pre: None
//Post: calculates the value of a user-defined polynomial
//returns result of calculation of polynomial
double PolynomialVal(const double Num);

//Pre: None
//Post: calls needed punctions pertaining to user input
//Descr: reads in user input and calls needed functions
void UserInput();

#endif
