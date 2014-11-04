# defines query tree structure
__author__ = 'Matt Carr'


class QueryTree:
    node_list = []
    current_tree_repr = []

    def __init__(self, name=''):
        self.name = name

    def __repr__(self):
        return self.name

    @staticmethod
    def output():
        print QueryTree.node_list[-1]  # printing the root prints everything

    class Node(object):
        def __init__(self, value, children=[]):
            self.value = value
            self.children = children
            QueryTree.node_list.append(self)

        def __repr__(self, level=0):
            ret = "\t" * level + str(self.value) + "\n"
            for child in self.children:
                ret += child.__repr__(level+1)
            return ret


