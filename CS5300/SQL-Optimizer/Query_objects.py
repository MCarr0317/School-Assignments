__author__ = 'Matthew Carr'

from copy import deepcopy
###################################################################
# Currently works on a query of the form SELECT-FROM-WHERE-ORDER BY
###################################################################


class Translator:
    keywords = {'SELECT': 'PROJECT', 'FROM': '', 'WHERE': 'SELECT', 'ORDER': '', 'BY': '', 'JOIN': 'JOIN'}
    translated = False

    def __init__(self, sql):
        self.sql = sql
        self.individual_statements = self.separate_statements(sql)

        #### for each statement in individual statements
        self.Parsed = self.Parser(self.individual_statements[0])
        self.Parsed.parse()  # parse into lines

        self.Translate()
        #print self.Parsed.select_clause
        self.statement = self.Statement(self.Parsed.select_clause, self.Parsed.from_clause, self.Parsed.where_clause, self.Parsed.order_clause)


    def __repr__(self):
        return self.statement.__repr__()

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

        def parse(self):
            #print self.parsed
            keyword = 'ORDER'
            clause = []
            found_order = found_where = found_from = found_select = False

            while not self.select_clause:
                for i in xrange(len(self.parsed)-1, -1, -1):
                    if keyword in self.parsed[i].upper():

                        #print keyword, self.parsed[i].upper()
                        clause = self.parsed[i:]
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
                    keyword = 'SELECT'
                    found_from = True

                elif not found_select:
                    self.select_clause = clause
                    found_select = True

        def output(self):
            print self.select_clause, 'select'
            print self.from_clause, 'from'
            print self.where_clause, 'where'
            print self.order_clause, 'order by'


    class Statement:
        def __init__(self, _SelectClause, _FromClause, _WhereClause, _OrderClause):
            self.From = self.FromClause(_FromClause)
            self.Select = self.SelectClause(_SelectClause)
            self.Where = self.WhereClause(_WhereClause)
            self.Order = self.OrderClause(_OrderClause)

        def __repr__(self):
            #if Translator.translated:
            #return self.Select.__repr__() + '\n' + self.Where.__repr__() + '\n' + self.From.__repr__()
            #else:
            if self.Order.order_list:
                return self.Select.__repr__() + '\n' + self.From.__repr__() + '\n' + self.Where.__repr__() + '\n' + self.Order.__repr__()
            else:
                return self.Select.__repr__() + '\n' + self.Where.__repr__() + '\n' + self.From.__repr__()


        class FromClause:
            def __init__(self, relation_list):
                self.relation_list = relation_list

            def __repr__(self):
                return ' '.join(self.relation_list)

        class SelectClause:
            def __init__(self, table_list):
                self.table_list = table_list

            def __repr__(self):
                return ' '.join(self.table_list)

        class WhereClause:
            def __init__(self, condition_list=[]):
                self.condition_list = condition_list

            def __repr__(self):
                return ' '.join(self.condition_list)

        class OrderClause:
            def __init__(self, order_list=[]):
                self.order_list = order_list

            def __repr__(self):
                if len(self.order_list):
                    return ' '.join(self.order_list)


    class Query:
        def __init__(self, name, statement_list=()):
            self.name = name
            self.statements = statement_list

        def __repr__(self):
            output_string = ''
            for i in xrange(len(self.statements)):
                output_string += '\t'*(i+1) + self.statements[i].output_select()

            for i in xrange(len(self.statements)-1, -1, -1):
                output_string += '\t'*(i+1) + self.statements[i].output_from()

            return self.name.upper() + ':\n' + '-'*30 + '\n' + output_string


    def ReplaceKeywords(self, clause, add_parens=False):
        new = deepcopy(clause)
        for i in xrange(len(new)):
            #print word.upper()
            if new[i].upper().strip('()') in Translator.keywords:
                Translator.Translated = True
                new[i] = Translator.keywords[new[i].upper().strip('()')]

        #print new
        if add_parens:
            new = ['('] + new + [')']

        return new

    def Translate(self):
        self.Parsed.select_clause = self.ReplaceKeywords(self.Parsed.select_clause)
        self.Parsed.from_clause = self.ReplaceKeywords(self.Parsed.from_clause, True)
        self.Parsed.where_clause = self.ReplaceKeywords(self.Parsed.where_clause)
        self.Parsed.order_clause = self.ReplaceKeywords(self.Parsed.order_clause)


    # separates nested statements and orders them in a list
    @staticmethod
    def separate_statements(sql):
        x = 0
        y = 0
        individual_statements = []
        parsed = sql.split()  # split into keywords
        #stripped_parsed = [x.strip(',;()') for x in parsed]  # remove other characters

        if not Translator.contains_sub_select(parsed):
            individual_statements.append(' '.join(parsed))

        while Translator.contains_sub_select(parsed):
            for i in xrange(len(parsed)-1, -1, -1):  # search the query backwards, without the other characters
                if "SELECT" in parsed[i]:  # if we see a select, this is the start of the deepest select in the query
                    x = i  # mark this position in the string
                    break
            nested = ''
            for i in xrange(x, len(parsed)):  # look through the parsed list including the characters
                nested += parsed[i] + ' '  # add everything to the nested string
                if ')' in parsed[i]:  # if we see a ), this is the end of the nested statement, with the next element being the name of the relation this statement returns
                    y = i  # mark this position in the string
                    break
            for i in xrange(x, y+1):  # remove this statement from the query
                parsed.pop(x)

            remainder_of_string = ' '.join(parsed)
            parsed_remainder_of_string = remainder_of_string.split()
            #stripped_parsed__remainder_of_string = [x.strip(',;()') for x in parsed_remainder_of_string]

            individual_statements.append(nested)
            if not Translator.contains_sub_select(parsed_remainder_of_string):
                individual_statements.append(' '.join(parsed))

        #print len(individual_statements)
        return individual_statements

    #returns true if a query has a sub-select statement
    @staticmethod
    def contains_sub_select(query):  # query is a keyword-parsed list with extra chars removed
        found = False
        for item in query:  # exclude the first select
            if item.upper() == 'WHERE':
                found = True
            if found and 'SELECT' in item.upper():
                return True
        return False
