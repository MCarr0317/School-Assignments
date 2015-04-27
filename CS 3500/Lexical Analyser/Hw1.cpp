#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

bool recognize(string s);


int main()
{
    ifstream fin("input.txt");
    string s, num_input;
    
    fin >> num_input;
    num_input = atoi(num_input.c_str());
    cout << num_input;
    
    for (int i = 0; i < 12; i++)
    {
        fin >> s;
        if (recognize(s))
            cout << "keyword" << endl;
    }
   
   return 0;
}

//need a case entry for [7, 8, ]
bool recognize(string s)
{
    int state = 1;
    int i = 0;

     while ( i < s.length() )
    {
        switch (state)
        {
        case 7: if ( s[i] == 'w' )
                    state = 9;
                else if (s[i] == 'i')
                    state = 13;
                else if (s[i] == 'e')
                    state = 16;
                else if (s[i] == 'f')
                    state = 14;
                else
                    state = 7;
                break;
        case 9 : if ( s[i] == 'h' )
                      state = 10;  
                   else 
                      state = 19; //identifier state
                break;
        case 10 : if ( s[i] == 'i' )
                      state = 11;
                   else 
                      state = 19;
                break;
        case 11 : if ( s[i] == 'l' )
                      state = 12;
                   else 
                      state = 19;
                break;
        case 12: if ( s[i] == 'e' )
                      state = 8;
                   else 
                      state = 19;
                break;;
        
        //begin cases for "if" keyword
        case 13: if ( s[i] == 'f' )
                      state = 8;
                   else 
                      state = 19;
                break;
                
        //begin cases for "for" keyword
        case 14: if ( s[i] == 'o' )
                      state = 15;
                   else 
                      state = 19;
                break;
        case 15: if ( s[i] == 'r' )
                      state = 8;
                   else 
                      state = 19;
                break;
                
                
        //begin cases for "else" keyword
        case 16: if ( s[i] == 'l' )
                      state = 17;
                   else 
                      state = 19;
                break;
        case 17: if ( s[i] == 's' )
                      state = 18;
                   else 
                      state = 19;
                break;
        case 18: if ( s[i] == 'e' )
                      state = 8;
                   else 
                      state = 19;
                break;
                
        //keyword state
        case 8: state = 19;
                break;
        default :          // failure state reached
                    i = s.length();
                    break;
        }// switch
    
        i++;
  
    }// while

    if ( i == s.length() && state == 8 )
         return true;
  
    return false;
    }
