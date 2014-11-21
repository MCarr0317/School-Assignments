__author__ = 'Matthew Carr'
import sys

from Query_Objects import *
from Query_tree import *

sys.path.append('C:\Python27\Lib\site-packages\graphviz-0.4.2')
from graphviz import Digraph

def main():
    # test sql query
    test_cases = open('test_cases.txt', 'r')


    for test in test_cases:
        statements = Translator.separate_statements(test)
        for statement in statements:
            T = Translator(statement)
            T.Translate()
            #print T, '\n'

            dot = Digraph(comment='query tree')
            dot.node('A', "<&#928;<SUB>" + ' '.join(T.Parsed.select_clause) + "</SUB>>")  # make projection, selection, and join nodes using unicode symbol and subscript HTML tags
            dot.node('B', "<&#963;<SUB>" + ' '.join(T.Parsed.where_clause) + "</SUB>>")
            dot.node('L', "&#215;")  # cross product node

            for x in xrange(len(T.Parsed.from_clause)):
                symbol = str(x)
                dot.node(symbol, T.Parsed.from_clause[x])
                dot.edge('L', symbol, constraint='true')

            dot.edges(['AB', 'BL'])

            print dot

        """
        tree = QueryTree()
        print test

        for statement in statements:
            T = Translator(statement)
            T.Translate()
            print T, '\n'

            if len(T.Parsed.from_clause) > 1:
                join = tree.Node('X', [tree.Node(x) for x in T.Parsed.from_clause])
                select = tree.Node(' '.join(T.Parsed.where_clause), [join])
            else:
                select = tree.Node(' '.join(T.Parsed.where_clause), [tree.Node(i) for i in T.Parsed.from_clause])

            project = tree.Node(' '.join(T.Parsed.select_clause), [select])

            tree.output()
            print
        """
        print '-'*80


if __name__ == "__main__":
    main()
