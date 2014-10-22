__author__ = 'Matthew Carr'


class Statement:
    def __init__(self, attributes=(), relations=(), statement_type='SELECT'):
        self.type = statement_type
        self.attributes = attributes
        self.relations = relations

    def output_select(self):
        return self.type + ' ' + ','.join(self.attributes) + ',\n'

    def output_from(self):
        return 'FROM' + ' ' + ','.join(self.relations) + '\n'


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
