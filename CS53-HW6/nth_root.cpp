//Programmer: MATT CARR Date: 10-12-11
//File: Hw6Implementation.cpp
//Description: This is the implementation file for Homework 6,                                                                              
//  containing all of the function definitions


#include "Hw6Header.h"

void Prompt(string Phrase)
{
  cout<<Phrase;
  return;
}

void UserInput()
{
  double Num = 0;  //contains the number the user inputs.
  double n;        //contains the exponent or root for pertinent functions
  double StartValue1, StartValue2, StartMean; //stores the random number values
  bool Quit = false;     //used for quitting the program
  char MenuChoice;       //holds the menu choice

  Prompt("Hello! Please choose an option from below\n\n");

  do 
  {
    Prompt("Menu\n--------\n"
           "1. Enter a Number\n"
           "2. Display your number to the nth power\n"
           "3. Display nth root of yout number\n"
           "4. calculate e to the power of your number\n"
           "5. Find the hyperbolic sine of your number\n"
           "6. Find the value of a polynomial while X = your number.\n"
           "7. Quit\n\n"
           "Your choice is:   ");

    cin>>MenuChoice;

    switch (MenuChoice)
    {
      case '1':                              //Option 1: Inputting a number
      case 'a':                              //
        do 
        {
          Prompt("Enter a positive real number:   ");
          cin>>Num;
        } while (Num <= 0);
      break;

      case '2':                              //Option 2: X^n
      case 'b':                              //
        if (Num > 0)
        {
          do
          {
            Prompt("Enter a value for n (must be positive):   ");
            cin>>n;
          } while (n <= 0);

          Prompt("The number is ");
          cout<<Num_To_Exponent(Num, n)<<endl;
        }
        else
          Prompt("You must enter a number via option 1 first.\n\n");
      break;

      

      case '3':                              //Option 3: X^1/n
      case 'c':                              //
        if (Num > 0)
        {
          do 
          {
            Prompt("Enter a value for n(must be positive):    ");
            cin>>n;
          } while (n <= 0);
        
        /* initialize random seed: */
          srand ( time(NULL) );

          do                           
          {                                  //This was used to determine 
                                             //an average of two numbers, 
                                             //to create a good starting value.
            StartValue1 = (rand() % 501);    // 
            StartValue2 = (rand() % 501);    // 
                        
          } while (StartValue1 >= Num && StartValue2 <= Num);  

          StartMean = (StartValue1 + StartValue2) / 2;
          Prompt("Your number is ");
          cout<<NthRoot(Num, n, StartMean)<<endl;
        }
        else
          Prompt("You must enter a number via option 1 first.\n\n");
      break;

      case '4':                              //Option 4: e^X
      case 'd':                              //
        if (Num > 0) 
        {
          Prompt("e to the power ");
          cout<<Num<<" is "<<e_to_x(Num)<<endl;
        }
        else
          cout<<"you must first enter a positive real number" 
                " via option 1.\n\n"<<endl;
      break;

      case '5':                              //Option 5: Hyperbolic sine
      case 'e':                              //
        if (Num > 0)
        {
          Prompt("The hyperbolic sin of ");
          cout<<Num<< " is "<<HyperbolicSine(Num)<<endl;
        }
        else
          Prompt("You must first enter a number via option 1.\n\n");
      break;

      case '6':                              //Option 6: Polynomial
      case 'f':                              //
        if (Num > 0)
        {
          cout<<"The value is "<<PolynomialVal(Num)<<endl;
        }
        else
          Prompt("you must first enter a number via option 1.\n\n");
      break;

      case '7':                              //Option 7: Quit
      case 'g':                              //
        Prompt("Goodbye!\n");
        Quit = true;
      break;
    }
  } while (Quit == false);

  return;
}

double NthRoot(const double Num, const short n, const double StartMean)
{
/* I really hated the fact that inputting higher numbers would go way outside
   of the range of a double and produce incorrect answers, 
   so I used a different definition of the formula 
       Xn+1 = Xn - F(Xn) / F'(Xn)  */
  
  const short ITERATIONS = 20;
  double Xn_Plus_1, Xn = StartMean;
  double Divisor;
  for (int i = 1; i <=ITERATIONS ; i++)
  {
    Divisor = Num_To_Exponent(Xn, (n - 1));
    Xn_Plus_1 = (((n-1) * Xn) + (Num/ Divisor))/n;
    Xn = Xn_Plus_1;
  }

  return Xn_Plus_1;
}



double Num_To_Exponent(const double Xn, const short n)
{
  double Result = 1;
  for (int i = 0;i < n ;i++)
  {
    Result = Result * Xn;
  }

  return Result;
}

double e_to_x(const double x)
{
  const short ITERATIONS = 11;
  double Estimate = 1;
  for (int i = 1;i <= ITERATIONS;i++)
  {
    Estimate += (Num_To_Exponent(x, i) / Factorial(i));
  }

  return Estimate;
}

double HyperbolicSine(const double Num)
{
  double Sinh = 0.5 * (e_to_x(Num) - e_to_x(-Num));

  return Sinh;
}

double PolynomialVal(const double Num)
{
/* I couldn't figure out a way to have the size of the array 
   defined by the user during run-time without using pointers 
   or something so I just limited it to 10 variables */
  const short NumVariables = 10;
  short Coefficients[NumVariables]; //stores the coefficients for each variable
  double Result = 0;         //stores result of operation
  short Degree;              //this degree value is inserted into the array
  Prompt("What is the degree of the polynomial?   ");
  cin>>Degree;

  for (int i = Degree;i > 0;i--)
  {
    Prompt("What is the coefficient for X^");
    cout<<i<<":   "<<endl;
    cin>>Coefficients[i];
  }

  Prompt("For the polynomial ");

  for (int i = Degree; i > 0;i--)
  {
    cout<<Coefficients[i]<<"X^"<<i<<((i > 1)?  " + ": " ");
  }


  //calculating value
  for (int i = Degree; i > 0; i--)
  {
    Result += Coefficients[i] * Num_To_Exponent(Num, i);
  }

  return Result;
}

double Factorial(const short n)
{
  double Result = n;
  for (int i = n;i > 1;i--)
    Result *= i - 1;

  return Result;
}
