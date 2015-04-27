# Athour: MATTHEW CARR
# Homework 2 - Recursive Descent Parser


import re, sys, fileinput

class Recursive_decent_parser():
	def __init__(self, _string_to_parse):

		# DEFINE TOKENS
		self.keywords = ('is', '+', '-', '*', '/', 'or', 'and', 
			'neg', '(', ')', 'lt', 'gt', 'eq' , '$', 
			'!', 'print', 'inc', 'ret', 'if', 'fi', 
			'ex', 'loop', 'pool', 'prog', 'blip', 'blorp')

		# regex strings for matching tokens
		self.identifier = r'^[a-zA-Z][a-zA-Z0-9]*$'
		self.integer = r'^[+-]?[0-9]+$'
		self.decimal = r'^[+-]?[0-9]+.[0-9]+$'
		self.string = r'^\"[a-zA-Z0-9]+\"$'

		# holds the current token through parsing
		self.token = ''

		# holds the part of our string that we have not parsed yet
		self.string_to_parse = _string_to_parse.split()  # split by all whitespace

		self.getToken()

		if self.parse_RoutineDeclaration():  # start
			print "CORRECT"
		else:
			print "INVALID!"

	def getToken(self):
		if self.string_to_parse:
			self.token = self.string_to_parse[0]
			self.string_to_parse = self.string_to_parse[1:]

	def parse_RoutineDeclaration(self):
		if self.token == 'prog':
			self.getToken()
			if re.match(self.identifier, self.token) != None and self.token not in self.keywords:  # if identifier
				self.getToken()
				if self.token == '(':
					self.getToken()
					self.parse_ParamSequence()
					if self.token == ')':
						self.getToken()
						if self.token == 'blip':  # start program body
							self.getToken()
							self.parse_StatementSequence()
							if self.token == 'blorp':  # end program body
								self.getToken()
								return True
							else:
								#sys.exit("expected blorp")
								return False
						else:
							#sys.exit("expected blip")
							return False
					else:
						#sys.exit("expected )")
						return False
				else:
					#sys.exit("expected (")
					return False
			else:
				#sys.exit("invalid identifier")
				return False
		else:
			#sys.exit("expected prog")
			return False

	def parse_ParamSequence(self):
		if re.match(self.identifier, self.token) != None and self.token not in self.keywords:  # if identifier
			self.getToken()
			if self.token == ',':  # if there are more parameters
				self.getToken()
				self.parse_ParamSequence()

	def parse_StatementSequence(self):
		if self.parse_Statement():
			if self.token != 'blorp':
				self.parse_StatementSequence()

	def parse_Statement(self):
		if self.parse_Assignment():
			#print "detected assignment", self.token, self.string_to_parse
			return True
		elif self.parse_IfStatement():
			#print "detected if-statement"
			return True
		elif self.parse_LoopStatement():
			#print "detected loop"
			return True
		elif self.parse_PrintStatement():
			#print "detected print-statement"
			return True
		elif self.parse_IncStatement():
			#print "detected Inc-statement"
			return True
		elif self.parse_RetStatement():
			#print "detected return-statement"
			return True
		else:
			#print "expected either Assignment, If , Loop, Print, Inc, or Ret statements"
			return False

	def parse_PrintStatement(self):
		if self.token == 'print':
			self.getToken()
			if re.match(self.identifier, self.token) != None and self.token not in self.keywords:  # if identifier
				self.getToken()
				if self.token == '!':
					self.getToken()
					return True
				else:
					#print "6 expected !"
					return False
			else:
				#print "6 expected identifier"
				return False
		else:
			return False

	def parse_LoopStatement(self):
		if self.token == 'loop':
			self.getToken()
			if self.token == '$':
				self.getToken()
				self.parse_Expression()
				if self.token == '$':
					self.getToken()
					self.parse_StatementSequence()
					if self.token == 'pool':
						self.getToken()
						return True
					else:
						#print "5 expected pool"
						return False
				else:
					#print "5 expected $"
					return False
			else:
				#print "5 expected $"
				return False
		else:
			return False

	def parse_IfStatement(self):
		if self.token == 'if':
			self.getToken()
			if self.token == '$':
				self.getToken()
				self.parse_Expression()
				if self.token == '$':
					self.getToken()
					self.parse_StatementSequence()
					if self.token == 'ex':  # else
						self.getToken()
						self.parse_StatementSequence()
						if self.token == 'fi':  # end the if statement
							self.getToken()
							return True
						else:
							#print "4 expected fi"
							return False
				else:
					#print "4 expected $"
					return False
			else:
				#print "4 expected $"
				return False
		else:
			return False

	def parse_RetStatement(self):
		if self.token == 'ret':
			self.getToken()
			if re.match(self.identifier, self.token) != None and self.token not in self.keywords:  # if identifier
				self.getToken()
				if self.token == '!':
					self.getToken()
					return True
				else:
					#print "3 expected !"
					return False
			else:
				#print "3 expected identifier"
				return False
		else:
			return False

	def parse_IncStatement(self):
		if self.token == 'inc':
			self.getToken()
			if re.match(self.identifier, self.token) != None and self.token not in self.keywords:  # if identifier
				self.getToken()
				if self.token == '!':
					self.getToken()
					return True
				else:
					#print "2 expected !"
					return False
			else:
				#print "2 expected identifier"
				return False
		else:
			return False

	def parse_Assignment(self):
		#print "test", self.token, self.token not in self.keywords
		if re.match(self.identifier, self.token) != None and self.token not in self.keywords:  # if identifier
			self.getToken()
			if self.token == 'is':
				self.getToken()
				self.parse_Expression()
				if self.token == '!':
					self.getToken()
					return True
				else:
					#print "1 expected !"
					return False
			else:
				#print "1 expected is"
				return False
		else:
			return False

	def parse_MulOperator(self):
		if self.token == '*' or self.token == '/' or self.token == 'and':
			self.getToken()
			return True

	def parse_AddOperator(self):
		if self.token == '+' or self.token == '-' or self.token == 'or':
			self.getToken()
			return True

	def parse_Relation(self):
		if self.token == 'lt' or self.token == 'gt' or self.token == 'eq':
			self.getToken()
			return True

	def parse_Factor(self):
		if re.match(self.integer, self.token) != None and self.token not in self.keywords:  # if integer
			self.getToken()
			#print "matched an int"
			return True
		elif re.match(self.decimal, self.token) != None and self.token not in self.keywords:  # if decimal
			self.getToken()
			#print "matched a decimal"
			return True
		elif re.match(self.string, self.token) != None and self.token not in self.keywords:  # if string
			self.getToken()
			#print "matched a string"
			return True
		elif re.match(self.identifier, self.token) != None and self.token not in self.keywords:  # if identifier
			self.getToken()
			#print "matched an identifier"
			return True
		elif self.token == '(':
			self.parse_Expression()
			if self.token == ')':
				self.getToken()
				return True
		elif self.token == 'neg':
			self.getToken()
			self.parse_Factor()
			return True
		else:
			#print "matched no factors"
			return False

	def parse_Term(self):
		self.parse_Factor()
		if self.parse_MulOperator():
			self.parse_Term()

	def parse_SimpleExpression(self):
		self.parse_Term()
		if self.parse_AddOperator():
			self.parse_SimpleExpression()

	def parse_Expression(self):
		self.parse_SimpleExpression()
		if self.parse_Relation():
			self.parse_SimpleExpression()

def main():
	for line in fileinput.input():
		if line != '\n':
			Recursive_decent_parser(line)

if __name__ == "__main__":
	main()