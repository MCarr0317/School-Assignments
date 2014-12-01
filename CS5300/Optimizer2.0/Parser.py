__author__ = 'Matthew'

import Translator


class Parser:
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
            self.Operator = Translator.contains_multiple_unnested_queries(self.parsed)

        def parse(self):
            #print self.parsed
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
                    print self.from_clause
                    self.use_aliases()
                    keyword = 'SELECT'
                    found_from = True

                elif not found_select:
                    self.select_clause = clause
                    found_select = True

        #sets the from_clause to use the relation aliases, if any exist
        def use_aliases(self):
            self.aliases = []  # make a list of relations and their aliases for later use
            for i in xrange(len(self.from_clause)):
                if 'AS' in self.from_clause[i]:
                    self.aliases.append(self.from_clause[i+1].strip(','))

            if self.aliases:
                self.from_clause = self.aliases

        def get_aliases(self):
            return self.aliases

        def output(self):
            print self.select_clause, 'select'
            print self.from_clause, 'from'
            print self.where_clause, 'where'
            print self.order_clause, 'order by'
