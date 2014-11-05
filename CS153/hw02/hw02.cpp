#include <iostream>
#include "hw02.hpp"
using namespace std;

int main()
{
    const int UG = 5;
    const int GR = 6;
    const int DS = 6;
    int *NumExams, *ExamArray, NumStudents, ID, *Grades;
    string StudentName;
    Student *s;
    
    cin >> NumStudents;

    s = new Student[NumStudents];
 
    for (int i = 0;i < NumStudents;i++)
    {
        ID = cin.peek();
        cin >> StudentName;
        NumExams = new int[NumStudents];
        switch (ID)
        {
            case 1:
              NumExams[i] = UG;
              ExamArray = new int[UG];
              s[i] = new Undergrad(ID, StudentName, NumExams[i]);
              break;
            case 2:
              NumExams[i] = GR;
              ExamArray = new int[GR];
              s[i] = new Graduate(ID, StudentNAme, NumExams[i]);
              break;
            case 3:
              NumExams[i] = DS;
              ExamArray = new int[DS];
              s[i] = new Distance(ID, StudentName, NumExams[i]);
              break;
            default:
              cout << "Error reading ID number" << endl;
        }
        for (int k = 0;k < NumExams[i];k ++)
        {
          cin >> ExamArray[k];
        }

        for (int k = 0;k < NumExams;k++)
        {
          s[i].setExam(NumExams[i], ExamArray[k]);
        }


    }
    
    return 0;
}

