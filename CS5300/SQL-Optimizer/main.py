__author__ = 'Matthew Carr'

from Query_Objects import *



def main():
    # test sql query
    test_cases = open('test_cases.txt', 'r')

    for test in test_cases:
        statements = Translator.separate_statements(test)
        #print statements

        for statement in statements:
            T = Translator(statement)
            print T
            print


if __name__ == "__main__":
    main()
