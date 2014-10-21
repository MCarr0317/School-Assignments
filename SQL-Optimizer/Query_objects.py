class Statement:
    def __init__(self, attributes=[], relations=[], statement_type='SELECT'):
        self.type = statement_type
        self.attributes = attributes
        self.relations = relations

    def output_select(self):
        return self.type + ' ' + ','.join(self.attributes) + ',\n'

    def output_from(self):
        return 'FROM' + ' ' + ','.join(self.relations) + '\n'



class Query:
    def __init__(self, name, *statement_list):
        self.name = name
        self.statements = statement_list

    def __repr__(self):
        output_string = ''
        for i in xrange(len(self.statements)):
            output_string += '\t'*(i+1) + self.statements[i].output_select()

        for i in xrange(len(self.statements)-1, -1, -1):
            output_string += '\t'*(i+1) + self.statements[i].output_from()

        return output_string






test = separate_statements(sql)
#print test

statement1 = Parser(test[0])
statement1.parse()

statement2 = Parser(test[1])
statement2.parse()

statement3 = Parser(test[2])
statement3.parse()


first = Statement(statement1.attributes, statement1.relations)  # create a statement object
second = Statement(statement2.attributes, statement2.relations)
third = Statement(statement3.attributes, statement3.relations)

test_query = Query('query1', third, second, first)  # pass them in reverse order since our statement list
                                                    # from separate_statements returns the deepest query first
print test_query
