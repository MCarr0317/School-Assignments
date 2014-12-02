__author__ = 'Matthew Carr / Nick Douglas'

import Parser
import Statement
from copy import deepcopy

# Translator Object Definition.
# This is the class that translated from Parsed SQL to Relational Algebra
class Translator:
    # a dict of keywords that is used when translated from SQL to RelAlg
    keywords = {'SELECT': 'PROJECT', 'FROM': '', 'WHERE': 'SELECT', 'ORDER': '', 'GROUP': '', 'BY': '', 'JOIN': 'JOIN',
                '>': '&#62;', '<': '&#60;'}

    # flag to tell if we have translated or not.
    translated = False


    # constructor for Translator Object.
    # Defines the sql to be translated, the Parser object acting on that sql, and the statement to represent it by
    def __init__(self, sql):
        self.sql = sql
        self.Parsed = Parser.Parser(self.sql)
        self.Parse()  # parse into lines
        self.statement = Statement.Statement(self.Parsed.select_clause, self.Parsed.from_clause, self.Parsed.where_clause, self.Parsed.order_clause, self.Parsed.Operator)

    # output function if the Translator object is ever called in a print function
    def __repr__(self):
        return self.statement.__repr__()

    # Calls the parse() method in our Parser object
    def Parse(self):
        self.Parsed.parse()

    # method for replacing keywords with RelAlg ones, using the Translator keywords dict from above.
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

    # Translate method that simple replaces the keywords in all main clauses in our statement.
    # It then recombines and updates the Statement object
    def Translate(self):
        #Translator.translated = True
        self.Parsed.select_clause = self.ReplaceKeywords(self.Parsed.select_clause)
        self.Parsed.from_clause = self.ReplaceKeywords(self.Parsed.from_clause)
        self.Parsed.where_clause = self.ReplaceKeywords(self.Parsed.where_clause)
        self.Parsed.order_clause = self.ReplaceKeywords(self.Parsed.order_clause)

        self.statement = Statement.Statement(self.Parsed.select_clause, self.Parsed.from_clause, self.Parsed.where_clause, self.Parsed.order_clause, self.Parsed.Operator)


# Helper function that separates nested statements and orders them in a list
def separate_statements(sql):
    x, y = 0, 0
    individual_statements = []
    parsed = sql.split()  # split into keywords
    #stripped_parsed = [x.strip(',;()') for x in parsed]  # remove other characters

    if contains_multiple_unnested_queries(parsed):
        for n in xrange(len(parsed)):
            if "UNION" in parsed[n] or "INTERSECT" in parsed[n] or "EXCEPT" in parsed[n]:
                individual_statements.append(' '.join(parsed[:n]))
                individual_statements.append(' '.join(parsed[n+1:]))



        return individual_statements

    else:
        if not contains_sub_select(parsed):
            individual_statements.append(' '.join(parsed))

        while contains_sub_select(parsed):
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
            if not contains_sub_select(parsed):
                individual_statements.append(' '.join(parsed))


    return individual_statements

    #returns true if a query has a sub-select statement

# Helper function that returns true if a query still contains a sub-select statement.
# This is used when determining how to separate out the statements.
def contains_sub_select(query):  # query is a keyword-parsed list with extra chars removed
    found = False
    for item in query:  # exclude the first select
        if item.upper() == 'WHERE':
            found = True
        if found and 'SELECT' in item.upper():
            return True
    return False

# Helper function that returns true when a statement contains multiple queries that are un-nested,
#   such as two statements that are joined by a UNION operator.
def contains_multiple_unnested_queries(query):
    if "UNION" in query:
        return "UNION"
    elif "INTERSECT" in query:
        return "INTERSECT"
    elif "EXCEPT" in query:
        return "EXCEPT"
    else:
        return False
