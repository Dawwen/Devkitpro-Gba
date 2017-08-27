
from PIL import Image
import glob

_2_5 = 2 ** 5
_2_8 = 2 ** 8

def conv_8_5( v ):
	return int( ( v * _2_5 ) / _2_8 )

def convert(pixel):
	return([int(pixel[0]*2**(5-8)),int(pixel[1]*2**(5-8)),int(pixel[2]*2**(5-8))])

class palet:
	"Une classe pour les palet de 16 couleur"

	def __init__(self):
		self.palet = [[0,0,0] for i in range(15)]
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

def convert_image( filename,test ):
	i = Image.open(filename).convert("RGB")
	width, height = i.size
	nb_tiles = (width*height)/8*8
	out = open( filename + ".bit", "w" )
	out.write("{")

	out.write("{0}, {1}".format(nb_tiles , height) )
	out.write("}\n{\n")

	for j in range(int(width / height)):
		out.write("\t{\n")
		for y_sq in range(height//8):
			for x_sq in range(height//8):
				for y in range(y_sq*8,(y_sq+1)*8):
					out.write("\t\t")
					for x in range(j*height + x_sq*8,j*height + (x_sq+1)*8, 4):
						out.write("0x")
						for k in range(3,-1,-1):
							pixel = test.pixel_to_palet(i.getpixel((x+k,y)))
							out.write(str(pixel+1))
						out.write(",")
					out.write("\n")
				if (y_sq != height/8-1 or x_sq != height/8-1):
					out.write("\n")
		out.write("\t}")
		if (j != width/height -1):
			out.write(",")
		out.write("\n")
	out.write("}")
	out.close()

def convert_rgb_to_hexa(RGB):
	r,g,b = RGB
	value = (b << 10) | (g << 5) | r
	return "%04x" % value;

def output_palet(test):
	out = open("palet.bit", "w")
	out.write("const vuint16 player_palet[13] = \n{")
	for i in range(15):
		if i%2 == 0:
			out.write("\n\t\t")
		out.write("0x")
		out.write(convert_rgb_to_hexa(test.palet[i]))
		if i != 14:
			out.write(",")
	out.write("\n}")

if __name__ == '__main__':
	test = palet()
	for f in glob.glob( "Sprite/*.bmp") :
		print(f)
		convert_image(f,test)
	output_palet(test)
