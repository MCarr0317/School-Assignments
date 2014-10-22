__author__ = 'Matthew Carr'
#translates SQL into relational algebra


def translate_tokens(parsed_statement):
    keywords = {'SELECT': 'PROJECT', 'FROM': '(', 'WHERE': 'SELECT'}
    list_ = []
    for token in parsed_statement:
        if token in keywords:
            list_.append(keywords[token])
        else:
            list_.append(token)

    list_.append(')')
    return list_


def get_attributes(translated_statement):
    # assume no nested projections since we already weeded them out in separate_statements
    x, y = 0, 0
    for i in xrange(len(translated_statement)):
        if translated_statement[i] == 'PROJECT':
            x = i+1
        elif translated_statement[i] == '(':
            y = i

    return translated_statement[x:y]

def get_relations(translated_statement):
    x, y = 0, 0
    for i in xrange(len(translated_statement)):
        if translated_statement[i] == '(':
            x = i+1
        elif translated_statement[i] == ')':
            y = i

    return translated_statement[x:y]


def insert_tokens(translated_statement):
    relations = []
    x, y = 0, 0
    for i in xrange(len(translated_statement)):
        if translated_statement[i] == '(':
            x = i+2
        if x and translated_statement[i] == ')':
            y = i
        if y:
            relations = translated_statement[x:y+1]

    if not 'JOIN' in relations:
        for i in xrange(0, len(relations), 2):
            relations.insert(i, 'X')

    return translated_statement[:x] + relations




list = ['SELECT', 'studentID', 'Name', 'GPA', 'FROM', 'student', 'student2']

print ' '.join(insert_tokens((translate_tokens(list))))

