__author__ = 'Matthew Carr'


class Parser:
    def __init__(self, sql):
        self.attributes = []
        self.relations = []
        self.conditionals = []
        self.sql = sql
        self.parsed = None

    def parse(self):
        self.parsed = self.sql.split()
        self.parsed = [x.strip(',;()') for x in self.parsed]
        self.extract_attributes()
        self.extract_relations()
        self.extract_conditionals()

    def extract_attributes(self):
        from_reached = False
        for token in self.parsed:
            if token == 'FROM':
                from_reached = True

            if token != 'SELECT' and token != 'FROM':
                if not from_reached:
                    self.attributes.append(token)

    def extract_relations(self):
        from_reached = False
        for token in self.parsed:
            if token == 'FROM':
                from_reached = True
                continue
            elif token == 'WHERE':
                break
            if from_reached:
                self.relations.append(token)

    def extract_conditionals(self):
        where_reached = False
        for token in self.parsed:
            if token == 'WHERE':
                where_reached = True
                continue
            if where_reached:
                self.conditionals.append(token)

    def output(self):
        print '\nStatement to parse: ', self.sql, '\n' + '-'*80
        print '\tTokens: ', self.parsed
        print '\tAttributes: ', self.attributes
        print '\tRelations: ', self.relations
        print '\tConditions: ', self.conditionals, '\n'
