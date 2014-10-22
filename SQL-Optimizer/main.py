__author__ = 'Matthew Carr'

from Parser import *
from Query_Objects import *
from separate_statements import *


def main():
    # test sql query
    sql = """SELECT studentID, Name, GPA
            FROM student, (SELECT studentID2, Name2, GPA2
            FROM student2, (SELECT studentID3, Name3, GPA3
            FROM student3) student3) student2;"""

    # for every sql statement in our file
    individual_statements = separate_statements(sql)
    statements = []

    for statement in individual_statements:
        x = Parser(statement)
        x.parse()
        x.output()

        statements.append(Statement(x.attributes, x.relations))

    final_query = Query('Final Query', statements)
    print final_query


if __name__ == "__main__":
    main()
