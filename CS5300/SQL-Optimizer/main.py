__author__ = 'Matthew Carr'

from Query_Objects import *
from Query_tree import *


def main():
    # test sql query
    test_cases = open('test_cases.txt', 'r')

    for test in test_cases:
        table_list = []
        attribute_list = []
        statements = Translator.separate_statements(test)
        #print statements

        for statement in statements:
            T = Translator(statement)
            print T
            print
            tree = QueryTree()
            for i in xrange(1, len(T.Parsed.from_clause)):
                table_list.append(tree.Node(T.Parsed.from_clause[i]))

            for i in xrange(1, len(T.Parsed.select_clause)):
                attribute_list.append((T.Parsed.select_clause[i]))

            if len(table_list) > 1:
                join = tree.Node('X', table_list)
                select = tree.Node(' '.join(T.Parsed.where_clause), [join])
                project = tree.Node(' '.join(T.Parsed.select_clause), [select])
            else:
                select = tree.Node(' '.join(T.Parsed.where_clause), table_list)
                project = tree.Node(' '.join(T.Parsed.select_clause), [select])

            tree.output()
            print
            
        print '-'*80


if __name__ == "__main__":
    main()
