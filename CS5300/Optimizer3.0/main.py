__author__ = 'Matthew Carr/ Nick Douglas'
from trees import *


def main():
    # test sql query
    test_cases = open('test_cases.txt', 'r')  # file full of test queries
    query = ""
    for test in test_cases:
        if test.strip('\n') is not '':  # ignore blank lines
            query += test
        else:
            optimize(query)  # begin optimization
            print '-'*80  # help with layout
            query = ""  # reset for next SQL query



if __name__ == "__main__":
    main()

