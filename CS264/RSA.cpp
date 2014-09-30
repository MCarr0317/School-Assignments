////////////////////////////////////////////////////////
//Written by Matt Carr and Nick Douglas --> 9/31/2013 //                                                     
//                                                    //
//An implementation of RSA encryption                 //
//                                                    // 
//                                                    //
////////////////////////////////////////////////////////







#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <gmp.h>
using namespace std;




int main()
{
//Compute d and N given p, q, and e
  string PQE;
  string DN;//private key pair
  string X;
  string EX;
  string C;
  string DC;
  int b;
  int k;
  char answer;
  fstream inputPQE, inputX, inputC;
  fstream outputDN, outputEX, outputDC;
  mpz_t p, q, e, d, n, fin, x, c, z, gcd, one, phi; //All of the variables used with the GMP library
  mpz_init(p);                                      //
  mpz_init(q);                                      //
  mpz_init(e);                                      //
  mpz_init(d);                                      //
  mpz_init(n);                                      //
  mpz_init(fin);                                    //
  mpz_init(x);                                      //
  mpz_init(c);                                      //
  mpz_init(z);                                      //
  mpz_init(gcd);                                    //
  mpz_init(one);                                    //

//initializing and seeding the random number generator. Seed is the system time
  unsigned long int seed;
  gmp_randstate_t randState;
  seed = time(NULL);
  gmp_randinit_mt (randState);
  gmp_randseed_ui(randState, seed);




  //let the user choose to enter a number k or use premade files
  printf("do you want to generate p and q?");
  cin >> answer;

/*if they want to use their own files*/
if (answer == 'n')
{
//Get file names and number of bits for N///////////////////////////////////////////////////////////////////////////////
  printf("Enter the name of the file that contains p, q, and e: ");
  cin >> PQE;

  inputPQE.open(PQE.c_str()); //read p, q, e from file
  inputPQE >> p >> q >> e;    //
  inputPQE.close();           //

  cout << "p is " << p << endl << " q is " << q << endl << " e is " << e << endl;

  printf("Enter the output file name to store d and N: "); 
  cin >> DN;
}

/*if they want the program to generate values for p, q, and e*/
else if (answer == 'y')  
{
  printf("Enter the number of bits of N: ");
  cin >> k;
  mpz_urandomb(p, randState, k/2); //if k was 1024 bit, p and q would be 512 bit each
  mpz_urandomb(q, randState, k/2); //
  mpz_nextprime(p, p); //takes the next prime, then next prime it again 
  mpz_nextprime(q, q); // so that it is 2 primes above the original
  mpz_nextprime(p, p); //
  mpz_nextprime(q, q); //

  //generating e 
  mpz_set_d(one, 1); //create a variable for subtracting 1
  
  mpz_t p1, q1;  //p1 and q1 are p-1 and q-1, respectively
  mpz_init(p1);
  mpz_init(q1);

  mpz_sub(p1, p, one); //sets p1 to p-1
  mpz_sub(q1, q, one); //sets q1 to q-1
  mpz_mul(phi, p1, q1); //creates phi = (p-1)(q-1)

  mpz_mul(n, p, q);


//while the above process created the variables used in generating e, the loop below
//actually finds e such that 1<e<phi and that e and phi are coprimes.
  do
  {
    mpz_t n1; 
    mpz_init(n1);
    mpz_sub(n1, n, one); //n1 becomes n-1, to create random values that are less than n
    mpz_urandomm(e, randState, n1);
    mpz_gcd(gcd, e, phi); //calculates the gcd of e and phi

  } while (mpz_cmp(gcd, one)); //keep running loop if gcd != 1
  
  cout << "p is " << p << endl << endl << endl << "q is " << q << endl << endl << endl << "e is " << e << endl << endl << endl;
  cout << "phi is " << phi << endl << endl << endl << "n is " << n << endl << endl << endl;

}

 

//Compute d and N using the given p, q, and e
  mpz_mul(n, p, q);
  mpz_sub_ui(p, p, 1UL);
  mpz_sub_ui(q, q, 1UL);
  mpz_mul(fin, p, q);
  mpz_invert(d, e, fin);

  cout << "d is " << d << endl << endl << endl << "n is " << n << endl << endl << endl;


//output d and n to file

  outputDN.open(DN.c_str());
  outputDN << d << endl << n;
  outputDN.close();



//Encrypt x and output the value//////////////////////////////////////////////////////////////////////////////////////

//Get file names
  printf("Enter the name of the file that contains x to be encrypted: ");
  cin >> X;
  inputX.open(X.c_str());
  inputX >> x;
  inputX.close();
  cout << "the value to be encrypted is " << x << endl;
  printf("Enter the output file name to store E(x): ");
  cin >> EX;


//Encrypt x
  mpz_powm_ui(c, x, mpz_get_ui(e), n);

cout << "the cipher is " << c << endl;
 
//output cipher to file
outputEX.open(EX.c_str());
outputEX << c;
outputEX.close();

//Decrypt c////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Get file names
  printf("Enter the name of the file that contains c to be decrypted: ");
  cin >> C;
  inputC.open(C.c_str());
  inputC >> c;
  inputC.close();
  cout << "the value to be decrypted is " << c << endl;
  printf("Enter the output file name to store D(c): ");
  cin >> DC;
  
  
//Decrypting c
  mpz_powm_ui(x, c, mpz_get_ui(d), n);
 
cout << "the decrypted value is " << x << endl;


//output message to file
outputDC.open(DC.c_str());
outputDC << d << endl << c; 
outputDC.close();



  return 0;
}
