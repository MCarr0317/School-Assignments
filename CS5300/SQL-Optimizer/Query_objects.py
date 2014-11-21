__author__ = 'Matthew Carr'

from copy import deepcopy
##############################################################################
# Currently works on a query of the form SELECT-FROM-WHERE-ORDER BY/GROUP BY #
##############################################################################


class Translator:
    keywords = {'SELECT': 'PROJECT', 'FROM': '', 'WHERE': 'SELECT', 'ORDER': '', 'GROUP': '', 'BY': '', 'JOIN': 'JOIN'}
    translated = False

    def __init__(self, sql):
        self.sql = sql
        self.Parsed = self.Parser(self.sql)
        self.Parse()  # parse into lines
        self.statement = self.Statement(self.Parsed.select_clause, self.Parsed.from_clause, self.Parsed.where_clause, self.Parsed.order_clause)


    def __repr__(self):
        return self.statement.__repr__()

    def Parse(self):
        self.Parsed.parse()

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
                    self.use_aliases()
                    keyword = 'SELECT'
                    found_from = True

                elif not found_select:
                    self.select_clause = clause
                    found_select = True

        #sets the from_clause to use the relation aliases, if any exist
        def use_aliases(self):
            aliases = {}  # make a list of relations and their aliases for later use
            for i in xrange(len(self.from_clause)):
                if 'AS' in self.from_clause[i]:
                    aliases[self.from_clause[i-1]] = self.from_clause[i+1]

            self.from_clause = aliases.values()



        def output(self):
            print self.select_clause, 'select'
            print self.from_clause, 'from'
            print self.where_clause, 'where'
            print self.order_clause, 'order by'

    class Statement:
        def __init__(self, _SelectClause, _FromClause, _WhereClause, _OrderClause):
            self.From = self.Clause(_FromClause)
            self.Select = self.Clause(_SelectClause)
            self.Where = self.Clause(_WhereClause)
            self.Order = self.Clause(_OrderClause)

        def __repr__(self):
            if Translator.translated:
                return self.Select.__repr__() + '\n' + self.Where.__repr__() + '\n' + self.From.__repr__()
            else:
                if len(self.Order.tokens) > 0:
                    return self.Select.__repr__() + '\n' + self.From.__repr__() + '\n' + self.Where.__repr__() + '\n' + self.Order.__repr__()
                else:
                    return self.Select.__repr__() + '\n' + self.From.__repr__() + '\n' + self.Where.__repr__()

        class Clause:
            def __init__(self, token_list):
                self.tokens = token_list

            def __repr__(self):
                return ' '.join(self.tokens)

    def ReplaceKeywords(self, clause, add_parens=False):
        new = deepcopy(clause)
        for i in xrange(len(new)):
            #print word.upper()
            if new[i].upper().strip('()') in Translator.keywords:
                Translator.translated = True
                new[i] = Translator.keywords[new[i].upper()]

        #print new
        if add_parens: new = ['('] + new + [')']

        return new

    def Translate(self):
        #Translator.translated = True
        self.Parsed.select_clause = self.ReplaceKeywords(self.Parsed.select_clause)
        self.Parsed.from_clause = self.ReplaceKeywords(self.Parsed.from_clause)
        self.Parsed.where_clause = self.ReplaceKeywords(self.Parsed.where_clause)
        self.Parsed.order_clause = self.ReplaceKeywords(self.Parsed.order_clause)

        self.statement = self.Statement(self.Parsed.select_clause, self.Parsed.from_clause, self.Parsed.where_clause, self.Parsed.order_clause)

    # separates nested statements and orders them in a list
    @staticmethod
    def separate_statements(sql):
        x, y = 0, 0
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


            nested = nested.translate(None, '();')
            parsed = parsed[:x] + parsed[y+2:]

            individual_statements.append(nested)
            if not Translator.contains_sub_select(parsed):
                individual_statements.append(' '.join(parsed))


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

