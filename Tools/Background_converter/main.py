from PIL import Image
import glob

def convert(pixel):
	return([int(pixel[0]*2**(5-8)),int(pixel[1]*2**(5-8)),int(pixel[2]*2**(5-8))])

class palet:
	"Une classe pour les palet de 16 couleur"

	def __init__(self):
		self.palet = [[0,0,0] for i in range(16)]
		self.used_color = 0

	def pixel_in_palet(self,pixel):
		for i in range(self.used_color):
			color = self.palet[i]
			if pixel[0] == color[0] and pixel[1] == color[1] and pixel[2] == color[2]:
				return(i)
		return(-1)

	def add_to_palet(self,pixel):
		value = []
		for i in range(3):
			value.append(pixel[i])
		self.palet[self.used_color] = value
		self.used_color += 1

	def pixel_to_palet(self, pixel):
		pixel = convert(pixel)
		for i in range(self.used_color):
			value = self.pixel_in_palet(pixel)
			if value >= 0 :
				return(value)
		self.add_to_palet(pixel)
		return(self.used_color)

i = Image.open("background.png").convert("RGB")
width, height = i.size
test = palet()

for y in range(height):
	for x in range(width):
		pixel = i.getpixel((x,y))
		test.pixel_to_palet(pixel)
print(test.palet)
