//Programmer: MATT CARR  DATE: 9-29-11 
//PURPOSE: This program keeps a log of occupied lockers and displays their information as requested.
//
//



#include <iostream>
using namespace std;



struct LockerContents 
{    
  bool m_Occupied;         //Keeps track of occupied lockers
  short m_NumBooks;        //Stores the number of books
  string m_LastName;       //Stores the last names
  float m_Money;           //Stores the money
};

int main()
{
short NumLockers = 0, LockerNumber;          //Variable Declarations
short LockerDisplay, LockerDelete;           //
bool quit = false, OverMoneyLimit = false;   // 
char MenuChoice;                             //
const short AMNTOFLOCKERS = 101;             // 
const short LOCKERMAX = 201;                 //
const short LOCKERMIN = 101;                 //
const short MONEYMAX = 150;                  //
float MoneyCount = 0;                        //
LockerContents Locker[AMNTOFLOCKERS];

//resets the variables before using them
for (int i = 0;i < AMNTOFLOCKERS;i++)
{
  Locker[i].m_Occupied = false; 
  Locker[i].m_NumBooks = 0;
  Locker[i].m_LastName = ""; 
  Locker[i].m_Money = 0; 
}

//Opening
cout<<endl<<"Tooty fruit, ohhh root.  Tooty fruit, oh root. tooty fruit, ooh "
    <<"root!"<<endl<<endl<<endl;

//main program
do
{  
   
  cout<<"Menu\n------\n"
      <<"1. Add a locker\n"
      <<"2. Print contents of a locker\n"
      <<"3. Output all locker contents\n"
      <<"4. Delete a locker\n"
      <<"5. Quit\n"
      <<"There are "<<NumLockers<<" occupied lockers.\n\n"
      <<"Pick an option from above\n";
  cin>>MenuChoice;
  
//option 1
  if ((MenuChoice == '1') || (MenuChoice == 'a'))
  {
    do
    {
      cout<<"Please enter your desired lockerNumber between 101 and 201\n";
      cin>>LockerNumber;
      cout<<endl<<endl;
    } while ((LockerNumber < LOCKERMIN) || (LockerNumber > LOCKERMAX));
    if (Locker[LockerNumber - AMNTOFLOCKERS].m_Occupied == false)
    {
    cout<<"Please enter your last name"<<endl;
    cin>>Locker[LockerNumber - AMNTOFLOCKERS].m_LastName;
    cout<<"How many textbooks are in your locker?"<<endl;
    cin>>Locker[LockerNumber - AMNTOFLOCKERS].m_NumBooks;
    cout<<"How much money is in your locker?"<<endl<<"$";
    cin>>Locker[LockerNumber - AMNTOFLOCKERS].m_Money;
    Locker[LockerNumber - AMNTOFLOCKERS].m_Occupied = true;
    NumLockers++;
    }
    else
    cout<<"That locker is already taken"<<endl;

   
for (int i = 0; i < AMNTOFLOCKERS;i++)
  if (Locker[i].m_Occupied == true)
    {
    MoneyCount = MoneyCount + Locker[i].m_Money;

  if (MoneyCount > MONEYMAX)
    {
    OverMoneyLimit = true;
    MoneyCount = 0;
    Locker[i].m_Money = 0;
    }
  }
if (OverMoneyLimit == true)
{
cout<<"Oh no! Willie has stolen the money from all the lockers! He just made $"<<MoneyCount<<"!!!"<<endl;
OverMoneyLimit = false;
}

  }

  //option 2
  if ((MenuChoice == '2') || (MenuChoice == 'p'))
  {
  do{
  cout<<"Enter a locker number to display(Between 101 and 201)"<<endl;
  cin>>LockerDisplay;
  }while ((LockerDisplay < LOCKERMIN) || (LockerDisplay > LOCKERMAX));

  cout<<"Locker Number "<<LockerDisplay<<endl<<"-------------"<<endl;
if (Locker[LockerDisplay - AMNTOFLOCKERS].m_Occupied == true)
{
  if (Locker[LockerDisplay - AMNTOFLOCKERS].m_LastName == "")
  {
  cout<<"No Name"<<"\t";
  cout<<Locker[LockerDisplay - AMNTOFLOCKERS].m_NumBooks<<" books\t";
  cout.setf(ios::fixed);               //
	cout.setf(ios::showpoint);     //Formats the money
	cout.precision(2);             //
  cout<<"$"<<Locker[LockerDisplay].m_Money<<endl<<endl;
  }
  else{
    cout<<Locker[LockerDisplay - AMNTOFLOCKERS].m_LastName<<"\t";
    cout<<Locker[LockerDisplay - AMNTOFLOCKERS].m_NumBooks<<" Book(s)\t";
    cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
    cout<<"$"<<Locker[LockerDisplay - AMNTOFLOCKERS].m_Money<<endl<<endl;
   }
  }
else
  cout<<"That locker is not occupied."<<endl;
 }
  //Option 3
  if ((MenuChoice == '3') || (MenuChoice == 'o'))
  {
  if (NumLockers == 0)
  {
    cout<<"There are no occupied lockers."<<endl;
  }
  for (int i = 0;i < AMNTOFLOCKERS;i++)
  
  if (Locker[i].m_Occupied == true)
    {
    cout<<"Locker "<<i + AMNTOFLOCKERS<<"\t";
    cout<<Locker[i].m_LastName<<"\t";
    
    cout<<Locker[i].m_NumBooks<<" Book(s)"<<"\t";
    cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
    cout<<"$"<<Locker[i].m_Money<<endl<<endl;
    }
   }

  //Option 4
  if ((MenuChoice == '4') || (MenuChoice == 'd'))
  {
  cout<<"Enter a locker number you wish to delete"<<endl;
  cin>>LockerDelete;
  if (Locker[LockerDelete - AMNTOFLOCKERS].m_Occupied == false)
    cout<<"That locker is not occupied"<<endl;
  else 
  {
    Locker[LockerDelete - AMNTOFLOCKERS].m_LastName = "";       //
    Locker[LockerDelete - AMNTOFLOCKERS].m_NumBooks = 0;        //Resets
    Locker[LockerDelete - AMNTOFLOCKERS].m_Money = 0;           //Them
    Locker[LockerDelete - AMNTOFLOCKERS].m_Occupied = false;    //
    NumLockers--;
    cout<<"that locker has now been deleted"<<endl;
  }
  }

//Option 5
  if ((MenuChoice == '5') || (MenuChoice == 'q'))
  {
    quit = true;
    cout<<"thank you for using the locker registration system. Bye!"<<endl;
  }


   
}while (!quit);
   
return 0;
}
