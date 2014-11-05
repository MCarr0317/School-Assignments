//  
// This class represents a poster. 
// It has member variables for name, author and an array of string
// tags that describe the painting.  
//
// For hw01, implement all of the fields (data members) 
// and methods (member functions) of this class definition.
//
using namespace std;

class Poster {
public:
	string name;
    string author;
	int no_tags;
	string *tags;
	
	Poster():name(""), no_tags(0){}	//default constructor
	Poster(const Poster & rhs) //copy constructor
        {
          for (int i = 0;i < no_tags;i++)
          {
            name = rhs.name;
            author = rhs.author;
            no_tags = rhs.no_tags;
            tags = new string[no_tags];
            for (int i = 0;i < no_tags;)
            {
              tags[i] = rhs.tags[i];
            }
          }
        }	
	~Poster()  //default destructor
		{
			delete [] tags;
		}
	
	//overloading assignment
	const Poster & operator=(const Poster & rhs);
			
	void set(string n, string a);		//Sets the name and author to n and a
	 	  								// respectively
};

void Poster::set(string n, string a)
{
  name = n;
  author = a;
}



const Poster & Poster::operator=(const Poster & rhs)
{
  for (int i = 0;i < no_tags;i++)
  {
    name = rhs.name;
    author = rhs.author;
    no_tags = rhs.no_tags;
    tags = new string[no_tags];
    for (int i = 0;i < no_tags;)
    {
      tags[i] = rhs.tags[i];
    }
  }
  return *this;
}
