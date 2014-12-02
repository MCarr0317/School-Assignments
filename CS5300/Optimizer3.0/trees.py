__author__ = 'Matthew Carr / Nick Douglas'
import sys
from Translator import *

sys.path.append('C:\Python27\Lib\site-packages\graphviz-0.4.2')
from graphviz import Digraph


# Global variables that store arrays that must be carried over between optimizations
edges = []
cross_products = []
relations = []
selections = []
nodes = []
moveable = []
rel = []
join_moveable = []
join_rel = ()
all_selects = []
joins = []



# This is the big, most important function that calls all the other helper functions that optimize the tree.
# requirements: a digraph object, two indices for identifiers, operator_created boolean, index for optimization
#                identifiers, and the optimization step index for each section of the optimization
def make_tree(dot, T, index, index2, operator_created, index_optimization, optimization_step):
    global edges, cross_products, relations, selections, nodes, all_selects, joins

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
        make_edge(dot, projection, selection)

        #------------------------------------------------------------------------------------------------

        create_cross_products(dot, T, index, cross_products, edges, True, True, [])
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
        selections, select_values, edges, nodes, operands = cascade_of_selections(dot, T, index_optimization)
        if nodes:
            make_edge(dot, projection, nodes[0])

        cross_products, edges, num_crosses = create_cross_products(dot, T, index, cross_products, edges, True, False, [])  # create cross product nodes and edges
        if cross_products and nodes:
            make_edge(dot, nodes[-1], cross_products[0])

        relations = create_relations(dot, T, index, index2, cross_products, True)  # create relation nodes and edges

        #if operator_created:
         #   dot.edge('A', projection, constraint='true')
          #  edges.append(create_edge_string('A', projection))

        #determine_theta_joins(cross_products, T, edges, selections, relations, index)

    elif optimization_step == 2:  # move selections onto their appropriate relations
        # in this we are keeping all the same nodes, only changing the edges
        moveable, rel, join_moveable, join_rel = find_moveable_selections(T, selections, relations)

        #print moveable, rel
        #print join_moveable, join_rel

         # Keep: projection, relations, cross_products
        projection = create_projection_node(dot, str(index), ' '.join(T.Parsed.select_clause))
        cross_products, edges, num_crosses = create_cross_products(dot, T, index, cross_products, edges, True, False, join_moveable)  # create cross product nodes and edges
        relations = create_relations(dot, T, index, index2, cross_products, False, moveable)  # create relation nodes and edges

        # perform the optimization
        selections, select_values, edges, nodes, operands = cascade_of_selections(dot, T, index_optimization, False)
        all_selects = deepcopy(selections)
        selections = [item for item in selections if item not in moveable and item not in join_moveable]  # get the relation that cant be moved, draw the edge between projection and this

        #draw edge between projection and selection that cant be moved
        if selections:
            make_edge(dot, projection, selections[0])
            #print '11', (projection, selections[0])
        else:
            if join_moveable:
                make_edge(dot, projection, join_moveable[0])
                #print '12', (projection, join_moveable[0])

        #edges between other selections that cant be moved if possible
        for i in xrange(0, len(selections)-1):
            make_edge(dot, selections[i], selections[i+1])
            #print str(13+i), (selections[i], selections[i+1])

        #draw edge between selection that cant be moved and cross product
        if selections:
            make_edge(dot, selections[-1], cross_products[0])
            #print '20', (selections[-1], cross_products[0])

        #draw edges between selection that can be moved and its relation
        relations_moved = []
        for i in xrange(len(moveable)):
            if rel[i] not in [x[1] for x in relations_moved]:
                make_edge(dot, moveable[i], rel[i])
                relations_moved.append((moveable[i], rel[i]))
                #print str(30+i), (moveable[i], rel[i])
            else:
                for n in xrange(len(relations_moved)):
                    if relations_moved[n][1] == rel[i]:
                        make_edge(dot, moveable[i], moveable[n])
                        relations_moved.append((moveable[i], moveable[n]))
                        #print str(30+i), (moveable[i], moveable[n])
                        break

        # draw edges between cross products and relations that didnt get moved
        #relations.reverse()
        rel_same = [item for item in relations if item not in rel]
        #print rel_same
        if rel_same:  # relations that did not get a selection moved to them
            make_edge(dot, cross_products[-1], rel_same[-1])
            #print '40', (cross_products[-1], rel_same[-1])
            if cross_products:
                for i in xrange(len(rel_same)-1):
                    make_edge(dot, cross_products[-i], rel_same[-i])
                    #print str(60+i), (cross_products[-i], rel_same[-i])

        #draw edges between cross product and new selections that were moved
        crosses_made = []
        for i in xrange(len(moveable)):
            if moveable[i] not in [x[0] for x in relations_moved] and (cross_products[-1], moveable[i]) not in crosses_made:
                make_edge(dot, cross_products[-1], moveable[i])
                crosses_made.append((cross_products[-1], moveable[i]))
                #print '70', (cross_products[-1], moveable[i])

            else:
                #for n in xrange(len(crosses_made)):
                if (cross_products[-1], moveable[-i-1]) not in crosses_made and moveable[-i-1] not in [x[1] for x in relations_moved]:
                    make_edge(dot, cross_products[-1], moveable[-i-1])
                    crosses_made.append((cross_products[-1], moveable[-i-1]))
                    #print '71', (cross_products[-1], moveable[-i-1])

        for i in xrange(len(join_moveable)):
            make_edge(dot, join_moveable[i], cross_products[i])
            #print '80', (join_moveable[i], cross_products[i])


    elif optimization_step == 3:
        ### keep the same original projection and relations
        moveable, rel, join_moveable, join_rel = find_moveable_selections(T, all_selects, relations)

        projection = create_projection_node(dot, str(index), ' '.join(T.Parsed.select_clause))

        # find which selections we should remove
        selects_to_remove, crosses_to_remove = determine_theta_joins(cross_products, edges, all_selects)

        #create selections only if they arent ones that we need to remove
        selections, select_values, edges, nodes, operands = cascade_of_selections(dot, T, index_optimization, False, selects_to_remove)

        # create join nodes
        joins, edges, num_joins = create_joins(dot, T, index, selects_to_remove, edges, True, join_moveable, select_values)

        print 'joins', joins
        #print 'moveable', moveable

        relations = create_relations(dot, T, index, index2, joins, True, moveable)  # create relation nodes and edges

        relations_moved = []
        for i in xrange(len(moveable)):
            if rel[i] not in [x[1] for x in relations_moved]:
                make_edge(dot, moveable[i], rel[i])
                relations_moved.append((moveable[i], rel[i]))
                #print str(30+i), (moveable[i], rel[i])
            else:
                for n in xrange(len(relations_moved)):
                    if relations_moved[n][1] == rel[i]:
                        make_edge(dot, moveable[i], moveable[n])
                        relations_moved.append((moveable[i], moveable[n]))
                        #print str(30+i), (moveable[i], moveable[n])
                        break


# This parses the statements, Translates them, creates the digraphs and calls make_tree on each statement
def optimize(test):
    new = []
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
        # indices used to create the specific identifiers for nodes.
        # these have to increase enough to not have any repeated identifiers in the dot code
        #   since the number of nodes is dynamic. This is a limiting factor to this code working successfully.
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
        make_tree(dot1, T, index, index2, operator_created, index_optimization, 0)
        print dot1

        dot2 = Digraph(node_attr = {'shape': 'plaintext'})
        make_tree(dot2, T, index, index2, operator_created, index_optimization, 1)
        print dot2

        dot3 = Digraph(node_attr = {'shape': 'plaintext'})
        make_tree(dot3, T, index, index2, operator_created, index_optimization, 2)
        print dot3

        dot4 = Digraph(node_attr = {'shape': 'plaintext'})
        make_tree(dot4, T, index, index2, operator_created, index_optimization, 3)
        print dot4


# takes an identifier symbol and a value and creates a projection node in DOT code, returning the identifier
def create_projection_node(dot, symbol, value):
    symbol = str(symbol)
    value = str(value)
    dot.node(symbol, "<&#928;<SUB>" + value + "</SUB>>")
    return symbol

# takes an identifier symbol and a value and creates a selection node in DOT code, returning the identifier
def create_selection_node(dot, symbol, value):
    symbol = str(symbol)
    value = str(value)
    dot.node(symbol, "<&#963;<SUB>" + value + "</SUB>>")
    return symbol

# This generates the cross product nodes, and draws the edges between them if there are more than one.
def create_cross_products(dot, T, index, cross_products, edges, create_edges=True, initial=True, _join_moveable=[]):
    # Generate cross products nodes
    #---------------------------------------------------------------------------
    num_crosses = len(T.Parsed.from_clause)-1  # determine the number of cross products needed as num_relations-1

    # for each cross product, create its node and append its identifier to a list
    #print index, num_crosses + index
    for i in xrange(index, num_crosses + index):
        dot.node(str(i + 2), "&#215;")  # node
        cross_products.append(str(i + 2))  # appending to list



    # if we have more than one cross product, we need to draw an edge between all of them
    cross_products = list(set(cross_products))
    cross_products = cross_products[:num_crosses]

    #print 'cross', len(cross_products)
    #print 'num', num_crosses
    if create_edges:
        for n in xrange(len(join_moveable)):
            make_edge(dot, join_moveable[n], cross_products[n])
            #print '1', (join_moveable[n], cross[n])


        #print num_crosses
        if num_crosses >= 2:
            for n in xrange(0, num_crosses, 2):
                if _join_moveable:
                    try:
                        make_edge(dot, cross_products[n], _join_moveable[n-1])
                        #print '2', (cross_products[n], _join_moveable[n-1])
                    except IndexError:
                        pass
                else:
                    make_edge(dot, cross_products[n], cross_products[n+1])
                    #print '3', (cross_products[n], cross_products[n+1])

    # if we have atleast one cross product in the query, draw an edge between it and its parent selection node
        if cross_products and initial:
            make_edge(dot, str(index-1), cross_products[0])
           #print '4', (str(index-1), cross_products[0])
    #---------------------------------------------------------------------------

    return cross_products, edges, num_crosses


# This generates Theta join nodes, and draws edges between them
#                                  or selections that have been moved down the tree, if necessary.
def create_joins(dot, T, index, selects_to_remove, edges, create_edges, _join_moveable, select_values):
    joins = []
    num_joins = len(selects_to_remove)

    for i in xrange(len(selects_to_remove)):
        dot.node(str(i+100), "<&#10781;<SUB>" + select_values[i] + "</SUB>>")
        joins.append(str(i+100))

    joins = list(set(joins))
    joins = joins[:num_joins]

    if create_edges:
        for n in xrange(len(join_moveable)):
            make_edge(dot, join_moveable[n], joins[n])

        #print num_crosses
        joins.reverse()
        if num_joins >= 2:
            for n in xrange(num_joins-1):
                make_edge(dot, joins[n], joins[n+1])
                print 2, joins[n], joins[n+1]

    # if we have atleast one cross product in the query, draw an edge between it and its parent selection node
        if joins:
            make_edge(dot, str(index), joins[0])
            print 3, str(index), joins[0]
    #---------------------------------------------------------------------------

    return joins, edges, num_joins


# Generates nodes for each relation in the statement, and given an object_list of either cross products or joins,
#                         draws edges between them and possible selections that have moved down the tree
def create_relations(dot, T, index, index2, object_list, create_edges=True, _moveable=[]):
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

    #print 2222, object_list[-1]
    #print 3333, relations[0]
    if create_edges:
        if len(object_list) == 1:
            make_edge(dot, object_list[0], relations[0])
        elif len(object_list) > 1:
            make_edge(dot, object_list[-1], relations[0])

        #print '5', (cross_products[-1], relations[0])
        if object_list:
            for i in xrange(1, len(relations)-1):
                if len(_moveable) > 1:
                    #print 'here1'
                    make_edge(dot, object_list[-i], _moveable[i])
                    #print '6', (cross_products[-i], _moveable[i])
                else:
                    #print 'here2'
                    make_edge(dot, object_list[-i], relations[i])
                    #print '7', (cross_products[-i], relations[i])
            if _moveable:
                #print 'here3'
                make_edge(dot, object_list[0], _moveable[-1])
                #print '8', (cross_products[0], _moveable[-1])
            else:
                #print 'here4'
                make_edge(dot, object_list[0], relations[-1])
                #print '9', (cross_products[0], relations[-1])
        else:
            #print 'here5'
            make_edge(dot, str(index-1), symbol)
            #print '10', (str(index-1), symbol)

    #-------------------------------------------------------------------

    return relations


# This splits up cascading selections into independent nodes.
def cascade_of_selections(dot, _T, index_optimization, create_edges=True, selects_to_remove=[]):
    edges = []
    selections = []
    nodes = []
    select_values = []
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
        if str(index_optimization) not in selects_to_remove:
            nodes.append(str(index_optimization))
            selections.append(create_selection_node(dot, str(index_optimization), each))  # make a node for each operand
        else: select_values.append(each)
        index_optimization += 1
    #-------------------------------------------------------------

    if create_edges:
        for i in xrange(len(nodes)-1):
            make_edge(dot, nodes[i], nodes[i+1])

    return selections, select_values, edges, nodes, operands


# This determines which selections  and cross products that were created from cascade_of_selections need not be drawn
#       for the 4th optimization step. They are returned in a tuple
def determine_theta_joins(cross_products, edges, selections):
    #print edges
    #print cross_products
    #print selections
    selects_to_remove = []
    crosses_to_remove = []


    if cross_products:
        for i in edges:
            for op in selections:
                for cross in cross_products:
                    #print 'looking for', 'dot.edge(' + str(op) + ', ' + str(cross) + ')'
                    if 'dot.edge(' + str(op) + ', ' + str(cross) + ')' in i:
                        #print 'make ', 'dot.edge(' + str(op) + ', ' + str(cross) + ')', ' a join'
                        selects_to_remove.append(str(op))
                        crosses_to_remove.append(str(cross))


    return selects_to_remove, crosses_to_remove


# returns a string in the format of a dot.edge(x, y) statement. Edges are kept track throughout every optimization,
#           and the list of edges is used in determine_theta_joins()
def create_edge_string(x, y):
    return 'dot.edge(' + str(x) + ', ' + str(y) + ')'


# Helper function for making an edge node, and adding its string to our edges list.
def make_edge(dot, x, y):
    dot.edge(x, y, constraint='true')
    edges.append(create_edge_string(x, y))

# returns a tuple of the identifier of a selection node which can be moved,
#               and the relation identifier that it can be moved to
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

