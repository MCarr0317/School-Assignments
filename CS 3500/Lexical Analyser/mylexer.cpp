//  Author: MATT CARR
//  3/30/2015

#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;


//parses each string and returns a value 0-5 
char recognize(string s);


int main()
{
	//variables
    	string s;
	string num_input, result_word;
	int result, number;
	
	//get string count from file
    	cin >> num_input;
    	number = atoi(num_input.c_str());
	cout << number << endl;

	//main loop that runs recognize() on each string in the file
	// , reads the result, and outputs the classification 
    	for (int i = 1; i <= number; i++)
    	{
        	cin >> s;
		result = recognize(s);
		switch (result)
		{
			case 1:
				result_word = "Keyword.";
				break;
			case 2:
				result_word = "Identifier.";
				break;
			case 3:
				result_word = "Integer.";
				break;
			case 4:
				result_word = "Decimal.";
				break;
			case 5:
				result_word = "Scientific.";
				break;
			default:
				result_word = "Invalid!";
		}
		printf("%i: %s \n", i, result_word.c_str()); //output the result
    }
   
   return 0;
}


char recognize(string s)
{
	int state = 7;
    	unsigned int i = 0;

	//while we are not at the end of the string
     	while ( i < s.length() )
   	{
		//the reason for the out of order state numbers is that I made a DFA diagram
		// using a tool, and I just used the ID number given to each state in the tool.
		//Since I deleted and added things while making it, the numbers got out of order.
        	switch (state)
        	{
		//start state
        	case 7: if ( s[i] == 'w' )
                		state = 9;
                	else if (s[i] == 'i')
                    		state = 13;
                	else if (s[i] == 'e')
                    		state = 16;
                	else if (s[i] == 'f')
                    		state = 14;
			else if (isdigit(s[i]) or s[i] == '+' or s[i] == '-')
		    		state = 21;
                	else if (isalpha(s[i]))
                    		state = 19;
			else
		    		state = -1;
                	break;
				
		//Keyword states---------------------------
		// begin cases for "while" keyword
        	case 9 : if ( s[i] == 'h' )
                      		state = 10;  
                   	else if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i])) 
                      		state = 19; //identifier state
		 	else
                        	state = -1; //fail state
                	break;
        	case 10 : if ( s[i] == 'i' )
                  		state = 11;
                   	else if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i]))
                      		state = 19;
		 	else
                        	state = -1;
                	break;

        	case 11 : if ( s[i] == 'l' )
                      		state = 12;
                   	else if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i]))
                      		state = 19;
		 	else
                        	state = -1;
                	break;

        	case 12: if ( s[i] == 'e' )
                      		state = 8;
                   	else if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i]))
                      		state = 19;
		 	else
                        	state = -1;
                	break;
        
       		 //begin cases for "if" keyword
        	case 13: if ( s[i] == 'f' )
                      		state = 8;
                   	else if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i]))
                      		state = 19;
		 	else
                        	state = -1;
                	break;
                
       		 //begin cases for "for" keyword
        	case 14: if ( s[i] == 'o' )
                      		state = 15;
                   	else if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i]))
                      		state = 19;
		 	else
                        	state = -1;
                	break;

        	case 15: if ( s[i] == 'r' )
                      		state = 8;
                   	else if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i]))
                      		state = 19;
		 	else
                        	state = -1;
                	break;
                
                
       		 //begin cases for "else" keyword
        	case 16: if ( s[i] == 'l' )
                     		 state = 17;
                   	else if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i]))
                      		state = 19;
		 	else
                        	state = -1;
                	break;

        	case 17: if ( s[i] == 's' )
                      		state = 18;
                   	else if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i]))
                      		state = 19;
		 	else
                        	state = -1;
                	break;

        	case 18: if ( s[i] == 'e' )
                      		state = 8;
                   	else if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i]))
                      		state = 19;
		 	else
                        	state = -1;
                	break;
                
       		//keyword state itself
        	case 8: if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i]))
				state = 19;
                	break;
				
		//Identifier state-------------------------
		case 19: if (isdigit(s[i]) or s[i] == '_' or isalpha(s[i]))
				state = 19;
			else 
				state = -1;
			break;
		//integer state----------------------------
		case 21: if (isdigit(s[i]))
				state = 21;
			else if (s[i] == '.')
				state = 6;
			else
				state = -1;				
			break;
				
		case 6: if (isdigit(s[i]))
				state = 22;
			 else
                        	state = -1;
			break;
		//decimal state----------------------------
		case 22: if (isdigit(s[i]))
				state = 22;
			else if (s[i] == 'E')
				state = 23;
			else
				state = -1;				
			break;
				
		//scientific state-------------------------
		case 23: if (isdigit(s[i]))
				state = 24;
			else if (s[i] == '-' or s[i] == '+')
				state = 25;
			else
				state = -1;				
			break;
		case 24: if (isdigit(s[i]))
				state = 24;
			else
				state = -1;
			break;
		case 25: if (isdigit(s[i]))
				state = 24;
			else
				state = -1;				
			break;
        	default :          // failure state reached
                    	i = s.length();
                    	break;
        	}// switch
    
        	i++; 
  
	}// while

	//finally, determine if we are in successful states and if so, 
	// return the corresponding alias for its classification.
	switch (state)
	{
		case 8: return 1; break;
		case 19: return 2; break;
		case 21: return 3; break;
		case 22: return 4; break;
		case 24: return 5; break;
		default: return 0;
	}
}

