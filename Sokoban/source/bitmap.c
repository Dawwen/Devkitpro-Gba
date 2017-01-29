#include "bitmap.h"
#include "affichage.h"


void draw_bitmap (Bitmap * bm, int x, int y) 
{

	int xx,yy;
	for (yy = 0; yy < bm->height; ++yy)
	{
		for (xx = 0; xx < bm->width; ++xx)
		{
			m3_plot( x + xx , y + yy, bm->table[ yy * bm->width + xx ]) ;
		}
	}
}


