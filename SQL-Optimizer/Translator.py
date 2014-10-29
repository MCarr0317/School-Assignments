__author__ = 'Matthew Carr'
#translates SQL into relational algebra
from copy import deepcopy

keywords = {'SELECT': 'PROJECT', 'FROM': '(', 'WHERE': 'SELECT', ')': '', 'JOIN': 'JOIN'}


def translate_tokens(parsed_statement):
    #keywords = {'SELECT': 'PROJECT', 'FROM': '(', 'WHERE': 'SELECT'}
    list_ = []
    for token in parsed_statement:
        if token in keywords:
            list_.append(keywords[token])
        else:
            list_.append(token)

    list_.append(')')
    return ' '.join(insert_tokens(list_))



def get_attributes(translated_statement):
    # assume no nested projections since we already weeded them out in separate_statements
    x, y = 0, 0
    for i in xrange(len(translated_statement)):
        if translated_statement[i] == 'PROJECT':
            x = i+1
        elif translated_statement[i] == '(':
            y = i

    return translated_statement[x:y]


def get_relation_tokens(translated_statement):  # returns relation tokens without parenthesis
    x, y = 0, 0
    for i in xrange(len(translated_statement)):
        if translated_statement[i] == '(':
            x = i
        elif translated_statement[i] == ')':
            y = i

    return translated_statement[x+1:y], x


def get_relations(relation_tokens):  # return only relation table names including parenthesis
    relations = []
    for i in xrange(1, len(relation_tokens)):
        if relation_tokens[i] not in keywords:
            relations.append(relation_tokens[i])
    return relations


def insert_tokens(translated_statement):
    relation_tokens, x = get_relation_tokens(translated_statement)
    relations = get_relations(relation_tokens)
    temp = deepcopy(relation_tokens)

    print get_attributes(translated_statement)
    #if not 'JOIN' in relations:
    for i in xrange(1, len(relation_tokens)):
        if relation_tokens[i] != 'JOIN' and relation_tokens[i] not in relations:
            temp.insert(i, 'X')
        elif relation_tokens[i] == 'JOIN':
            temp.insert(i-1, '(')
            temp.insert(i+3, ')')

    return translated_statement[:x] + temp


list_ = ['SELECT', 'studentID', 'Name', 'GPA', 'FROM', 'student', 'WHERE', 'GPA', '>', '3.0']

print translate_tokens(list_)
