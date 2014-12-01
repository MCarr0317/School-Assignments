__author__ = 'Matthew'


class Statement:
        def __init__(self, _SelectClause, _FromClause, _WhereClause, _OrderClause, _Operator):
            self.From = self.Clause(_FromClause)
            self.Select = self.Clause(_SelectClause)
            self.Where = self.Clause(_WhereClause)
            self.Order = self.Clause(_OrderClause)
            self.Operator = self.Clause(_Operator)

        def __repr__(self):
            #if Translator.translated:
            return self.Select.__repr__() + '\n' + self.Where.__repr__() + '\n' + self.From.__repr__()
            #else:
             #   if len(self.Order.tokens) > 0:
              #      return self.Select.__repr__() + '\n' + self.From.__repr__() + '\n' + self.Where.__repr__() + '\n' + self.Order.__repr__()
               # else:
                #    return self.Select.__repr__() + '\n' + self.From.__repr__() + '\n' + self.Where.__repr__()

        class Clause:
            def __init__(self, token_list):
                self.tokens = token_list

            def __repr__(self):
                return ' '.join(self.tokens)
