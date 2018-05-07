#!/usr/bin/python3

from PIL import Image
import glob

_2_5 = 2 ** 5
_2_8 = 2 ** 8

def conv_8_5( v ):
	return int( ( v * _2_5 ) / _2_8 )

def convert(pixel):
	return([int(pixel[0]*2**(5-8)),int(pixel[1]*2**(5-8)),int(pixel[2]*2**(5-8))])

class palets:
	"une palette contenant 16 palets de 16 couleurs"

	def __init__(self):
		self.palets = []
		for i in range(16):
			self.palets.append(palet())



class palet:
	"Une classe pour les palet de 16 couleur"

	def __init__(self):
		self.palet = [[0,0,0] for i in range(15)]
		self.used_color = 0

	def pixel_in_palet(self,pixel):
		for i in range(self.used_color):
			color = self.palet[i]
			if pixel[0] == 31 and pixel[1] == 0 and pixel[2] == 31 :
				return(0)
			if pixel[0] == color[0] and pixel[1] == color[1] and pixel[2] == color[2]:
				return(i+1)
		return(-1)
	def add_to_palet(self,pixel):

		value = []
		for i in range(3):
			value.append(pixel[i])
		self.palet[self.used_color] = value
		self.used_color += 1

	def pixel_to_palet(self, pixel):
		pixel = convert(pixel)
		if pixel[0] == 31 and pixel[1] == 0 and pixel[2] == 31 :		#pixel invisible violet
			return(0)
		for i in range(self.used_color):
			value = self.pixel_in_palet(pixel)
			if value >= 0 :
				return(value)
		if self.used_color < 15 :
			self.add_to_palet(pixel)
			return(self.used_color)
		else :
			return(-1)

	def copy(self,p):
		for i in range(len(p.palet)):
			self.palet[i] = p.palet[i]
		self.used_color = p.used_color



def convert_image(filename, p, i_palet):

	p_temp = palet()	#une palette tampon
	p_temp.copy(p)

	i = Image.open(filename).convert("RGB")
	width, height = i.size
	nb_tiles = (width*height)/8*8
	out = open( filename + ".bit", "w" )
	out.write("{")

	out.write("{0}, {1}".format(nb_tiles , i_palet) )
	out.write("}\t")
	out.write("//Palet {}".format(i_palet))
	out.write("\n{\n")
	for j in range(int(width / height)):
		for y_sq in range(height//8):
			for x_sq in range(height//8):
				out.write("\t{\n")
				for y in range(y_sq*8,(y_sq+1)*8):
					out.write("\t\t")
					for x in range(j*height + x_sq*8,j*height + (x_sq+1)*8, 4):
						out.write("0x")
						for k in range(3,-1,-1):
							pixel = p_temp.pixel_to_palet(i.getpixel((x+k,y)))
							if pixel >= 0:
								out.write("{0:x}".format(pixel))
							else :
								return(False)
						out.write(",")
					out.write("\n")
				out.write("\t},\n")
	out.write("};")
	out.close()

	p.copy(p_temp)	#on vide la palette tampon
	return(True)

def convert_rgb_to_hexa(RGB):
	r,g,b = RGB
	value = (b << 10) | (g << 5) | r
	return "%04x" % value;

def output_palet(test):
	out = open("palet.bit", "w")
	out.write("const vuint16 player_palet[15] = \n{")
	for i in range(15):
		if i%2 == 0:
			out.write("\n\t\t")
		out.write("0x")
		out.write(convert_rgb_to_hexa(test.palet[i]))
		if i != 14:
			out.write(",")
	out.write("\n}")
	print(test.palet)


if __name__ == '__main__':
	p = palets()
	for f in glob.glob( "Sprite_4bpp/*.bmp") :
		print(f)
		i = 0
		finish = False
		while not finish and i < 16:
			if convert_image(f,p.palets[i],i) :
				finish = True
			i += 1

	output_palet(p.palets[0])
	output_palet(p.palets[1])
