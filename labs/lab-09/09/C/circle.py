from geometry import Point
from math import pi

class Circle:
	def __init__(self, center, radius):
		self.center = center
		self.radius = radius

	def __repr__(self):
		return f"Circle({self.center}, {self.radius})"

	def area(self):
		return pi * (self.radius ** 2)

	def parameter(self):
		return 2 * pi * self.radius

	def translate(self, dx, dy):
		return Circle(self.center.translate(dx,dy), radius)
		
