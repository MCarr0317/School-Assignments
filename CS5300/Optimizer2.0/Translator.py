__author__ = 'Matthew'

import Parser
import Statement
from copy import deepcopy

class Translator:
    keywords = {'SELECT': 'PROJECT', 'FROM': '', 'WHERE': 'SELECT', 'ORDER': '', 'GROUP': '', 'BY': '', 'JOIN': 'JOIN',
                '>': '&#62;', '<': '&#60;'}
    translated = False

    def __init__(self, sql):
        self.sql = sql
        self.Parsed = Parser.Parser(self.sql)
        self.Parse()  # parse into lines
        self.statement = Statement.Statement(self.Parsed.select_clause, self.Parsed.from_clause, self.Parsed.where_clause, self.Parsed.order_clause, self.Parsed.Operator)

    def __repr__(self):
        return self.statement.__repr__()

    def Parse(self):
        self.Parsed.parse()

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

        self.statement = Statement.Statement(self.Parsed.select_clause, self.Parsed.from_clause, self.Parsed.where_clause, self.Parsed.order_clause, self.Parsed.Operator)

# separates nested statements and orders them in a list

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

def contains_sub_select(query):  # query is a keyword-parsed list with extra chars removed
    found = False
    for item in query:  # exclude the first select
        if item.upper() == 'WHERE':
            found = True
        if found and 'SELECT' in item.upper():
            return True
    return False


def contains_multiple_unnested_queries(query):
    if "UNION" in query:
        return "UNION"
    elif "INTERSECT" in query:
        return "INTERSECT"
    elif "EXCEPT" in query:
        return "EXCEPT"
    else:
        return False
