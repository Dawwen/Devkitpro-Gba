'''
Created on 9 aout 2015

@author: didier
'''

from PIL import Image
import glob

_2_5 = 2 ** 5
_2_8 = 2 ** 8

def conv_8_5( v ):
	return int( ( v * _2_5 ) / _2_8 )

def pixel_to_palet(pixel) :

	if pixel == (0,0,0):
		res = 1
	elif pixel == (255,255,255):
		res = 2
	elif pixel == (255,0,0):
		res = 3
	elif pixel == (0,0,255):
		res = 4
	elif pixel == (0,255,0):
		res = 5
	return res

def convert_image( filename ):
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
							pixel = pixel_to_palet(i.getpixel((x+k,y)))
							out.write(str(pixel))
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

if __name__ == '__main__':
	for f in glob.glob( "Sprite/*.bmp") :
		print(f)
		convert_image(f)
