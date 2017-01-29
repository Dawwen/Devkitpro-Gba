
#ifndef bitmap_H

#define bitmap_H

#include "toolbox.h"

typedef struct {
	int width;
	int height;
	COLOR  table[];
} Bitmap ;




void draw_bitmap (Bitmap * bm, int x, int y);

#endif 