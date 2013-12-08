class StudentClass(object): 
 	def __init__(self,idNum):#refers to the object the constructor creates
		self.id = idNum
		self._totalcredits = 0
		self.gpa = 0.0

	def __str__(self):
		return "Student # %d " %self.id

	def addGrade(self,grade,credits):
		valpts = self.gpa * self._totalcredits
		valpts += grade*credits
		self._totalcredits += credits
		self.gpa += valpts/self._totalcredits
	def getGPA(self):
		return self.gpa #this is known as the getter method
