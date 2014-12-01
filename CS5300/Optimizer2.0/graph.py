

# defines query tree structure
__author__ = 'Matt Carr'
import sys
from copy import deepcopy
from Translator import *


sys.path.append('C:\Python27\Lib\site-packages\graphviz-0.4.2')
from graphviz import Digraph

edges = []
cross_products = []
relations = []
selections = []
nodes = []
moveable = []
rel = []
join_moveable = []
join_rel = ()

def reset_variables():
    global edges, cross_products, relations, selections, nodes, moveable, rel, join_moveable, join_rel
    edges = []
    cross_products = []
    relations = []
    selections = []
    nodes = []
    moveable = []
    rel = []
    join_moveable = []
    join_rel = ()

def create_projection_node(dot, symbol, value):
    symbol = str(symbol)
    value = str(value)
    dot.node(symbol, "<&#928;<SUB>" + value + "</SUB>>")
    return symbol

def create_selection_node(dot, symbol, value):
    symbol = str(symbol)
    value = str(value)
    dot.node(symbol, "<&#963;<SUB>" + value + "</SUB>>")
    return symbol

def create_cross_products(dot, T, index, cross_products, edges, create_edges=True, initial=True, _join_moveable=[]):
    # Generate cross products nodes
    #---------------------------------------------------------------------------
    num_crosses = len(T.Parsed.from_clause)-1  # determine the number of cross products needed as num_relations-1

    # for each cross product, create its node and append its identifier to a list
    print index, num_crosses + index
    for i in xrange(index, num_crosses + index):
        dot.node(str(i + 2), "&#215;")  # node
        cross_products.append(str(i + 2))  # appending to list

    # if we have more than one cross product, we need to draw an edge between all of them
    cross_products = list(set(cross_products))
    cross_products = cross_products[:num_crosses]

    print 'cross', len(cross_products)
    print 'num', num_crosses
    if create_edges:
        for n in xrange(len(join_moveable)):
            dot.edge(join_moveable[n], cross[n], constraint='true')
            print '1', (join_moveable[n], cross[n])


        print num_crosses
        if num_crosses >= 2:
            for n in xrange(0, num_crosses, 2):
                #try:
                 #   dot.edge(cross_products[n], join_moveable[-1+n])
                #except IndexError:
                if _join_moveable:
                    try:
                        dot.edge(cross_products[n], _join_moveable[n-1], constraint='true')
                        edges.append(create_edge_string(cross_products[n], _join_moveable[-1+n]))
                        print '2', (cross_products[n], _join_moveable[n-1])
                    except IndexError:
                        pass
                else:
                    dot.edge(cross_products[n], cross_products[n+1], constraint='true')
                    edges.append(create_edge_string(cross_products[n], cross_products[n+1]))
                    print '3', (cross_products[n], cross_products[n+1])

    # if we have atleast one cross product in the query, draw an edge between it and its parent selection node
        if cross_products and initial:
           dot.edge(str(index-1), cross_products[0], constraint='true')
           edges.append(create_edge_string(str(index-1), cross_products[0]))
           print '4', (str(index-1), cross_products[0])
    #---------------------------------------------------------------------------

    return cross_products, edges, num_crosses

def create_relations(dot, T, index, index2, cross_products, create_edges=True, _moveable=[]):
    # Generating relation nodes
    #--------------------------------------------------------------------
    relations = []
    symbol = None

    #for each relation, make its node and append it to a list
    for x in xrange(index2, len(T.Parsed.from_clause)+index2):
        symbol = str(x-1)  # identifier
        dot.node(symbol, T.Parsed.from_clause[x-index2])  # relation node
        relations.append(symbol)


    # if they need a cross, make an edge between the cross nodes and the relations.
    # If not, make an edge between selection node and relation
    #-------------------------------------------------------------------

    #print relations
    if create_edges:
        dot.edge(cross_products[-1], relations[0], constraint='true')
        print '5', (cross_products[-1], relations[0])
        if cross_products:
            for i in xrange(1, len(relations)-1):
                if _moveable:
                    #print 'here1'
                    dot.edge(cross_products[-i], _moveable[i], constraint='true')
                    edges.append(create_edge_string(cross_products[i], _moveable[i]))
                    print '6', (cross_products[-i], _moveable[i])
                else:
                    #print 'here2'
                    dot.edge(cross_products[-i], relations[i], constraint='true')
                    edges.append(create_edge_string(cross_products[i], relations[i]))
                    print '7', (cross_products[-i], relations[i])
            if _moveable:
                #print 'here3'
                dot.edge(cross_products[0], _moveable[-1], constraint='true')
                edges.append(create_edge_string(cross_products[-1], _moveable[-1]))
                print '8', (cross_products[0], _moveable[-1])
            else:
                #print 'here4'
                dot.edge(cross_products[0], relations[-1], constraint='true')
                edges.append(create_edge_string(cross_products[-1], relations[-1]))
                print '9', (cross_products[0], relations[-1])
        else:
            #print 'here5'
            dot.edge(str(index-1), symbol, constraint='true')
            edges.append(create_edge_string(str(index-1), symbol))
            print '10', (str(index-1), symbol)

        #dot.edge(cross_products[-1], relations[0])
    #-------------------------------------------------------------------

    return relations

def create_initial(dot, T, index, index2, operator_created, index_optimization, optimization_step):
    global edges, cross_products, relations, selections, nodes

    index -= 5
    index2 += 10
    index_optimization += 30

    if not optimization_step:  # initial tree @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        # if an operator exists in the query and we haven't made the node yet, make the node
        #------------------------------------------------------------------------------------
        #if T.Parsed.Operator and not operator_created and len(relations) >= 2:
         #   dot.node('A', T.Parsed.Operator)  # operator node that will be the root of the graph
          #  operator_created = True
        #------------------------------------------------------------------------------------

        # make the projection and selection nodes. Then draw the edge between them
        #------------------------------------------------------------------------------------------------
        projection = create_projection_node(dot, str(index), ' '.join(T.Parsed.select_clause))
        selection = create_selection_node(dot, str(index-1), ' '.join(T.Parsed.where_clause))  # selection
        dot.edge(projection, selection, constraint='true')  # edge
        edges.append(create_edge_string(projection, selection))
        #------------------------------------------------------------------------------------------------

        create_cross_products(dot, T, index, cross_products, edges, True, True)
        create_relations(dot, T, index, index2, cross_products, True)

        #if operator_created:
         #   dot.edge('A', projection, constraint='true')


    elif optimization_step == 1:  # cascade of selections @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        #if T.Parsed.Operator and not operator_created and len(relations) >= 2:
         #   dot.node('A', T.Parsed.Operator)  # operator node that will be the root of the graph
          #  operator_created = True

        # Keep: projection, relations, cross_products
        projection = create_projection_node(dot, str(index), ' '.join(T.Parsed.select_clause))

        # perform the optimization
        selections, edges, nodes = cascade_of_selections(dot, T, index_optimization)
        if nodes:
            dot.edge(projection, nodes[0])  # edge between projection and first new node
            edges.append(create_edge_string(projection, nodes[0]))

        cross_products, edges, num_crosses = create_cross_products(dot, T, index, cross_products, edges, True, False)  # create cross product nodes and edges
        if cross_products and nodes:
            dot.edge(nodes[-1], cross_products[0])
            edges.append(create_edge_string(nodes[-1], cross_products[0]))
        relations = create_relations(dot, T, index, index2, cross_products, True)  # create relation nodes and edges

        #if operator_created:
         #   dot.edge('A', projection, constraint='true')
          #  edges.append(create_edge_string('A', projection))

        #determine_theta_joins(cross_products, T, edges, selections, relations, index)

    elif optimization_step == 2:  # move selections onto their appropriate relations
        # in this we are keeping all the same nodes, only changing the edges
        moveable, rel, join_moveable, join_rel = find_moveable_selections(T, selections, relations)

        # moveable, rel
        #print join_moveable, join_rel

         # Keep: projection, relations, cross_products
        projection = create_projection_node(dot, str(index), ' '.join(T.Parsed.select_clause))
        cross_products, edges, num_crosses = create_cross_products(dot, T, index, cross_products, edges, True, False, join_moveable)  # create cross product nodes and edges
        relations = create_relations(dot, T, index, index2, cross_products, False, moveable)  # create relation nodes and edges

        # perform the optimization
        selections, edges, nodes = cascade_of_selections(dot, T, index_optimization, False)

        selections = [item for item in selections if item not in moveable and item not in join_moveable]  # get the relation that cant be moved, draw the edge between projection and this

        #draw edge between projection and selection that cant be moved
        if selections:
            dot.edge(projection, selections[0], constraint='true')
            print '11', (projection, selections[0])
            edges.append(create_edge_string(projection, selections[0]))
        else:
            if join_moveable:
                dot.edge(projection, join_moveable[0])
                edges.append(create_edge_string(projection, join_moveable[0]))
                print '12', (projection, join_moveable[0])

        #edges between other selections that cant be moved if possible
        for i in xrange(0, len(selections)-1):
            dot.edge(selections[i], selections[i+1])
            edges.append(create_edge_string(selections[i], selections[i+1]))
            print str(13+i), (selections[i], selections[i+1])

        #draw edge between selection that cant be moved and cross product
        if selections:
            dot.edge(selections[-1], cross_products[0])
            edges.append(create_edge_string(selections[-1], cross_products[0]))
            print '20', (selections[-1], cross_products[0])

        #draw edges between selection that can be moved and its relation
        for i in xrange(len(moveable)):
            dot.edge(moveable[i], rel[i], constraint='true')
            edges.append(create_edge_string(moveable[i], rel[i]))
            print str(30+i), (moveable[i], rel[i])

        # draw edges between cross products and relations that didnt get moved
        #relations.reverse()
        rel_same = [item for item in relations if item not in rel]
        #print rel_same
        if rel_same:  # relations that did not get a selection moved to them
            dot.edge(cross_products[-1], rel_same[-1], constraint='true')
            edges.append(create_edge_string(cross_products[0], rel_same[-1]))
            print '40', (cross_products[-1], rel_same[-1])
            if cross_products:
                for i in xrange(len(rel_same)-1):
                    dot.edge(cross_products[-i], rel_same[-i], constraint='true')
                    edges.append(create_edge_string(cross_products[-i], rel_same[i]))
                    print str(60+i), (cross_products[-i], rel_same[-i])

        #draw edges between cross product and new selections that were moved
        for i in xrange(len(moveable)):
            dot.edge(cross_products[-1], moveable[i], constraint='true')
            edges.append(create_edge_string(cross_products[-1], moveable[i]))
            print '70', (cross_products[-1], moveable[i])


        for i in xrange(len(join_moveable)):
            dot.edge(join_moveable[i], cross_products[i], constraint='true')
            edges.append(create_edge_string(join_moveable[i], cross_products[i]))
            print '80', (join_moveable[i], cross_products[i])

def create_tree(test, initial=True):
    new = []
    index = -1
    index2 = 20
    index_optimization = 50
    operator_created = False
    statements = separate_statements(test)

    #this is the lazy code for handling a nested query that also has an UNION, INTERSECT, or EXCEPT operator
    for item in statements:
        new += separate_statements(item)
    statements = new


    # we have our statements, lets make the empty digraph
    #if len(statements) >= 2:
     #   dot1 = Digraph(node_attr = {'shape': 'plaintext'})
      #  dot2 = Digraph(node_attr = {'shape': 'plaintext'})
       # dot3 = Digraph(node_attr = {'shape': 'plaintext'})

    for statement in statements:
        new = []
        index = -1
        index2 = 20
        index_optimization = 50
        # for each statement, we translate it
        #---------------------------------------
        T = Translator(statement)
        T.Translate()
        #---------------------------------------

        # calculates the operator involved between each tree
        #----------------------------------------------------------
        T.Parsed.Operator = contains_multiple_unnested_queries(test)
        #----------------------------------------------------------

        dot1 = Digraph(node_attr = {'shape': 'plaintext'})
        create_initial(dot1, T, index, index2, operator_created, index_optimization, 0)
        print dot1

        dot2 = Digraph(node_attr = {'shape': 'plaintext'})
        create_initial(dot2, T, index, index2, operator_created, index_optimization, 1)
        print dot2

        dot3 = Digraph(node_attr = {'shape': 'plaintext'})
        create_initial(dot3, T, index, index2, operator_created, index_optimization, 2)
        print dot3


        # indices used to create the specific identifiers for nodes.
        # these have to increase enough to not have any repeated identifiers in the dot code
        #   since the number of nodes is dynamic. This is a limiting factor to this code working successfully.

def cascade_of_selections(dot, _T, index_optimization, create_edges=True):
    edges = []
    selections = []
    nodes = []
    last_operator_was_and = False

    # split up the selection from the initial tree
    #----------------------------------------------------------------------------
    # since AND is a binary operation, make a list element for each AND we find
    operands = []
    for i in xrange(1, len(_T.Parsed.where_clause), 2):
        if 'AND' in _T.Parsed.where_clause[i]:
            if not last_operator_was_and:
                operands.append(_T.Parsed.where_clause[i-1])
                operands.append(_T.Parsed.where_clause[i+1])
            else:
                operands.append(_T.Parsed.where_clause[i+1])
            last_operator_was_and = True
        else:
            last_operator_was_and = False

    if not operands:
        print "No and statements in tree"
        return selections, edges, nodes
    #-----------------------------------------------------------------------------

    # make a node for each new selection operation
    #-------------------------------------------------------------
    for each in operands:
        nodes.append(str(index_optimization))
        selections.append(create_selection_node(dot, str(index_optimization), each))  # make a node for each operand
        index_optimization += 1
    #-------------------------------------------------------------

    if create_edges:
        for i in xrange(len(nodes)-1):
            dot.edge(nodes[i], nodes[i+1])
            edges.append(create_edge_string(nodes[i], nodes[i+1]))

    return selections, edges, nodes

def determine_theta_joins(cross_products, _T, edges, selections, relations, index):
    print edges
    if cross_products:
        for i in edges:
            for op in selections:
                for cross in cross_products:
                    if 'dot.edge(' + str(op) + ', ' + str(cross) + ')' in i:
                        print 'make ', 'dot.edge(' + str(op) + ', ' + str(cross) + ')', ' a join'

def create_edge_string(x, y):
    return 'dot.edge(' + str(x) + ', ' + str(y) + ')'

# returns a tuple of the identifier of the node which can be moved, and the relation identifier that it can be moved to
def find_moveable_selections(T, selections, relations):
    moveable = []  # the selections that can be moved
    join_moveable = []  # for selections that can only be moved to right above a cross product
    join_rel = []  # the relations that a join can be made over
    a2 = []  # the relations that selections can be moved on to
    selection_num = 0  # index for the selection list

    # determine which selections can be moved onto their relations
    for x in xrange(0, len(T.Parsed.where_clause), 2):
        a = []
        num_found = 0
        for alias in T.Parsed.from_clause:
            if alias.strip(',') in T.Parsed.where_clause[x]:
                for i in xrange(len(T.Parsed.from_clause)):
                    if alias.strip(',') in T.Parsed.from_clause[i]:
                        num_found += 1
                        a.append(relations[i])
                        if num_found == 2:
                            if selections:
                                join_moveable.append(selections[selection_num])
                                join_rel.append((relations[i], relations[i-1]))



        if len(a) == 1:
            if selections:
                moveable.append(selections[selection_num])
                a2.append(deepcopy(a[0]))
        selection_num += 1


    return moveable, a2, join_moveable, join_rel
