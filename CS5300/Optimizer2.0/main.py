__author__ = 'Matthew Carr'
from graph import *

def main():
    # test sql query
    test_cases = open('test_cases.txt', 'r')
    query = ""
    for test in test_cases:
        #reset_variables()
        if test.strip('\n') is not '':
            query += test
        else:
            create_tree(query, False)
            print '-'*80
            query = ""



if __name__ == "__main__":
    main()

