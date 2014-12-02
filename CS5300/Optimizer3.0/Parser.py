__author__ = 'Matthew Carr / Nick Douglas'

import Translator


class Parser:

        # constructor for Parser Objects.
        # makes an attribute for each possible clause and the high level operator between two queries, if it exists
        def __init__(self, single_statement):
            self.statement = single_statement
            try:
                self.parsed = self.statement.split()
            except TypeError:
                print "statement passed to parser must be a string of a single statement"
            self.from_clause = []
            self.select_clause = []
            self.where_clause = []
            self.order_clause = []

            # determining if there is an operator
            self.Operator = Translator.contains_multiple_unnested_queries(self.parsed)


        # This parses each statement into its independent clauses. The process is as follows:

        # 1. Start with the lowest clause first, which is the order by clause. This will be removed in RelAlg form,
        #       but I added it for the sake of completeness.
        # 2. Erase the part of the string we already parsed off, and move our keyword down to WHERE.
        # 3. Repeat this until we finish parsing for the SELECT keyword
        def parse(self):
            keyword = 'ORDER'
            clause = []
            found_order = found_where = found_from = found_select = False

            while not self.select_clause:
                for i in xrange(len(self.parsed)-1, -1, -1):
                    if keyword in self.parsed[i].upper() or 'GROUP' in self.parsed[i].upper():
                        #print keyword, self.parsed[i].upper()
                        clause = self.parsed[i+1:]
                        #print clause
                        self.parsed = self.parsed[:i]  # remove the clause to prepare for other other iterations
                        break

                if not found_order:
                    self.order_clause = clause
                    #print 'Order clause becomes: ', self.order_clause
                    keyword = 'WHERE'
                    found_order = True

                elif not found_where:
                    self.where_clause = clause
                    keyword = 'FROM'
                    found_where = True

                elif not found_from:
                    self.from_clause = clause
                    #self.from_clause.reverse()
                    #print self.from_clause
                    self.use_aliases()
                    keyword = 'SELECT'
                    found_from = True

                elif not found_select:
                    self.select_clause = clause
                    found_select = True

        # sets the from_clause to use the relation aliases, if any exist
        def use_aliases(self):
            self.aliases = []  # make a list of relations and their aliases for later use
            for i in xrange(len(self.from_clause)):
                if 'AS' in self.from_clause[i]:
                    self.aliases.append(self.from_clause[i+1].strip(','))

            if self.aliases:
                self.from_clause = self.aliases

        # Get function for relation aliases
        def get_aliases(self):
            return self.aliases

        # Simple output function
        def output(self):
            print self.select_clause, 'select'
            print self.from_clause, 'from'
            print self.where_clause, 'where'
            print self.order_clause, 'order by'
