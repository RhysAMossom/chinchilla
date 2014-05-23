import random
import sys
import csv

class method0():
	"""
	Bet on two columns.
	"""
	def __init__(self,name,bet,group1,group2):
		self.name = name
		self.balance = 0
		self.bet = bet
		self.group1 = group1
		self.group2 = group2

	def spin(self,number,color):
		# assume bets are all lost
		self.balance -= 2 * self.bet
		if number in self.group1 or number in self.group2:
			self.balance += 3 * self.bet
		return self.balance

class method1():
	"""
	Bet on two columns and one color same amount on all.
	"""
	def __init__(self,name,bet,color,group1,group2):
		self.name = name
		self.balance = 0
		self.bet = bet
		self.color = color
		self.group1 = group1
		self.group2 = group2

	def spin(self,number,color):
		# assume bets are all lost
		self.balance -= 3 * self.bet
		if color == self.color:
			self.balance += 2 * self.bet
		if number in self.group1 or number in self.group2:
			self.balance += 3 * self.bet
		return self.balance

class method2():
	"""
	Bet on two row groups ([1,12],[13,24],[25,36])
	"""
	def __init__(self,name,bet,group1,group2):
		self.name = name
		self.balance = 0
		self.bet = bet
		self.group1 = group1
		self.group2 = group2

	def spin(self,number,color):
		# assume bets are all lost
		self.balance -= 2 * self.bet
		if number in self.group1 or number in self.group2:
			self.balance += 3 * self.bet
		return self.balance

class method3():
	"""
	Bet on two row groups ([1,12],[13,24],[25,36])
	and smaller bet spread on third group
	"""
	def __init__(self,name,bet_l,bet_h,group1,group2,spread1,spread2,spread3):
		self.name = name
		self.balance = 0
		self.bet_l = bet_l
		self.bet_h = bet_h
		self.group1 = group1
		self.group2 = group2
		self.spread1 = spread1
		self.spread2 = spread2
		self.spread3 = spread3

	def spin(self,number,color):
		# assume bets are all lost
		self.balance -= 2 * self.bet_h + 3 * self.bet_l
		if number in self.group1 or number in self.group2:
			self.balance += 3 * self.bet_h
		if number in self.spread1:
			self.balance += 8 * self.bet_l
		if number in self.spread2:
			self.balance += 8 * self.bet_l
		if number in self.spread3:
			self.balance += 8 * self.bet_l
		return self.balance

def get_color(number):
	if number in [37,38]:
		return 'g' # green
	if number in [1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36]:
		return 'r' # red
	else:
		return 'b' # black

if __name__ == "__main__":
	methods = [ method0('2Cols',15,range(3,37,3),range(1,35,3)),
		method1('2Cols_black',15,'r',range(3,37,3),range(1,35,3)),
		method1('2Cols_red',15,'b',range(3,37,3),range(1,35,3)),
		method2('2Outer_15',15,range(13,25),range(25,37)),
		method3('2Outer3Inner_25_5',15,25,range(13,25),range(25,37),[1,2,4,5],[2,3,5,6],[7,8,10,11])
		]
	file_name = 'roulette_simulated_results.csv'
	with open(file_name,'w') as f:
		print('Welcome to roulette simulator')
		print('results saved to %s' % file_name)

		# create data results buffer
		results = {'play':None, 'number':None, 'color':None}
		for m in methods:
			results[m.name] = None
		
		results_file = csv.DictWriter(f, results.keys(), extrasaction='ignore')
		results_file.writeheader()

		for play in range(int(sys.argv[1])):
			# Spin roulette
			number = random.randint(1,36+2)
			color = get_color(number)

			# get stats
			results['play'] = play
			results['color'] = color
			results['number'] = number
			for m in methods:
				results[m.name] = m.spin(number,color)
			# log stats
			results_file.writerow(results)
			print(results)
	print("done gambling. You have a problem")
	print('results saved to %s' % file_name)