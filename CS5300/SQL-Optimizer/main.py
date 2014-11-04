__author__ = 'Matthew Carr'

from Query_Objects import *
from Query_tree import *


def main():
    # test sql query
    test_cases = open('test_cases.txt', 'r')

    for test in test_cases:
        print test
        statements = Translator.separate_statements(test)

        for statement in statements:
            T = Translator(statement)
            T.Translate()
            print T, '\n'
            tree = QueryTree()

            if len(T.Parsed.from_clause[1:]) > 1:
                join = tree.Node('X', [tree.Node(x) for x in T.Parsed.from_clause[1:]])
                select = tree.Node(' '.join(T.Parsed.where_clause), [join])
                project = tree.Node(' '.join(T.Parsed.select_clause), [select])
            else:
                select = tree.Node(' '.join(T.Parsed.where_clause), [tree.Node(i) for i in T.Parsed.from_clause[1:]])
                project = tree.Node(' '.join(T.Parsed.select_clause), [select])

            tree.output()
            print

        print '-'*80


if __name__ == "__main__":
    main()
