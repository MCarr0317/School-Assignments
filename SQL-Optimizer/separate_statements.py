# test sql query
sql = """SELECT studentID, Name, GPA
         FROM student, (SELECT studentID2, Name2, GPA2
         FROM student2, (SELECT studentID3, Name3, GPA3
         FROM student3 WHERE thing > 5) student3 WHERE thing2 > 15) student2
         WHERE final_thing == value;"""

def separate_statements(sql):
    x = 0
    y = 0
    individual_statements = []
    parsed = sql.split()  # split into keywords
    stripped_parsed = [x.strip(',;()') for x in parsed]  # remove other characters

    while contains_sub_select(parsed):
        for i in xrange(len(stripped_parsed)-1, -1, -1):  # search the query backwards, without the other characters
            if stripped_parsed[i] == "SELECT":  # if we see a select, this is the start of the deepest select in the query
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
            stripped_parsed.pop(x)

        remainder_of_string = ' '.join(parsed)
        parsed_remainder_of_string = remainder_of_string.split()
        stripped_parsed__remainder_of_string = [x.strip(',;()') for x in parsed_remainder_of_string]

        individual_statements.append(nested)
        if not contains_sub_select(stripped_parsed__remainder_of_string):
            individual_statements.append(' '.join(parsed))

    #return Parse_statement(' '.join(parsed))
    print len(individual_statements)
    return individual_statements


def contains_sub_select(query):  # query is a keyword-parsed list with extra chars removed
    query = [x.strip(',;()') for x in query]
    for item in query[1:]:  # exclude the first select
        if item == 'SELECT':
            return True
            
            
