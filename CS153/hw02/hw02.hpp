//
// What follows is the declaration of a base class 'Student' and
// 3 derived classes, 'Undegrad', 'Graduate' and 'Distance' designed
// to represent the 3 kinds of students mentioned in the problem.
//
// Notice that all field (data members) are "protected", therefore
// there will be accessed only through methods (member functions)
//
#include <string>
using namespace std;

// ------------------------------------------------------------------
class Student {
protected:
	int id;				// Id Number
	string name; 		// Name of student
	int no_exams;       // Number of exams
	int *exams;         // Array of grades of exams

public:
	Student(int i, string n, int ne);
	/* Constructor
	   Assigns i, n and ne to id, name and no_exams respectively.
	   Initializes the *exams array
	*/
        Student();

	~Student();
	/* Destructor
	*/

	void setExam(int i, int g);
	/* assigns a grade of g to the i'th exam
	*/

        void GetExams(int ExamArray[])
        {
          for (int i = 0;i < no_exams;i++)
          {
            ExamArray[i] = exams[i];
          }
        }
 
        int GetNumExams()
        {
          return no_exams;
        } 

	float examAvg(int i);
	/* returns the average of all exams
	*/
	void print();
 	/* Outputs to cout the id and name of the student.
	*/
};


Student::Student(int i, string n, int ne)
{
    id = i;
    name = n;
    no_exams = ne;
}

Student::~Student()
{
    delete exams;
}

void Student::setExam(int i, int g)
{
    exams = new int[i];
    for (int k = 0; k < i; k++)
    {
        exams[k] = g;
    }
}

void Student::print()
{
    cout << id << ' ' << name;
}

float Student::examAvg(int i)
{
    int *Exams, NumExams;
    Exams = new int[i];

    GetExams(Exams);
    NumExams = GetNumExams();
    float Counter = 0;
    for (int i = 0;i < NumExams; i++)
    {
        Counter += Exams[i];
    }

    return Counter;
}

// ------------------------------------------------------------------
class Undergrad : public Student {
protected:
	int progproj;		// grade of programming project
public:
 	Undergrad(int i, string n, int ne): Student(i, n, ne)
	{
          id = i;
          name = n;
          no_exams = ne;
	}

	~Undergrad()
	{
	    delete exams;
	}
	/* Constructor and destructor
	   (same function as base class)
	 */

	void setProj(int g)
	{
          progproj = g;
        }
	/* assigns a grade of g to the programming project
	*/

	float finalGrade()
	{
          float Counter = 0;
          for (int i = 0; i < no_exams; i++)
          {
            Counter += exams[i];
          }
          Counter += (Counter * 0.8);
          Counter += (progproj * 0.2);

          return Counter;
        }
	/* computes and returns the final grade
	*/
};

// ------------------------------------------------------------------
class Graduate : public Student {
protected:
	int research;		// grade of research project
	int paper;			// grade of paper presentation
public:
	Graduate(int i, string n, int ne) : Student(i, n, ne)
	{
          id = i;
          name = n;
          no_exams = ne;
	}

	~Graduate()
	{
	    delete exams;
	}
	/* Constructor and destructor
	   (same function as base class)
	 */

	void setProj(int g, int p)
	{
	    research = g;
	    paper = p;
	}
	/* assigns a grade of g to the research project
	   and a grade of p the the paper presentation
	*/
	float finalGrade()
	{
          float Counter = 0;
          for (int i = 0; i < no_exams; i++)
          {
            Counter += exams[i];
          }
          Counter += (Counter * 0.65);
          Counter += (research * 0.2);
          Counter += (paper * 0.15);

          return Counter;
	}
	/* computes and returns the final grade
	*/
};


// ------------------------------------------------------------------
class Distance : public Student {
public:
	Distance(int i, string n, int ne) : Student(i, n, ne)
	{
          id = i;
          name = n;
          no_exams = ne;
	}

	~Distance()
	{
          delete exams;
	}
	/* Constructor and destructor
	   (same function as base class)
	 */
	float finalGrade()
	{
	    float Counter = 0;
	    for (int i = 0;i < no_exams;i++)
	    {
	        Counter += exams[i];
	    }
	    Counter = (Counter/no_exams);
	    return Counter;
	}
	/* computes and returns the final grade
	*/
};

