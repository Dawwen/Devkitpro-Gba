
#ifndef OBJECT_H
#define OBJECT_H

typedef struct obj_attrs {
	uint16 attr0;
	uint16 attr1;
	uint16 attr2;
	uint16 pad;
} __attribute__((packed, aligned(4))) obj_attrs;

typedef uint32    tile_4bpp[8];
typedef tile_4bpp tile_block[512];

#define oam_mem            ((volatile obj_attrs *)MEM_OAM)
#define tile_mem           ((volatile tile_block *)MEM_VRAM)
#define object_palette_mem ((volatile rgb15 *)(MEM_PAL + 0x200))

#define OBJECT_ATTR0_Y_MASK		0x00FF
#define	OBJECT_ATTR0_SHAPE_MASK	0xC000
#define	OBJECT_ATTR0_MODE_MASK	0x0300
#define OBJECT_ATTR0_COLOR_MASK	0x2000

#define	OBJECT_ATTR1_SIZE_MASK	0xC000
#define OBJECT_ATTR1_X_MASK		0x01FF

#define OBJECT_ATTR2_TILE_MASK	0x03FF
#define	OBJECT_ATTR2_PALET_MASK	0xF000

// Set the position of an object to specified x and y coordinates
static inline void set_object_position(volatile obj_attrs *object, int x,
										int y)
{
	object->attr0 = (object->attr0 & ~OBJECT_ATTR0_Y_MASK) |
					(y & OBJECT_ATTR0_Y_MASK);
	object->attr1 = (object->attr1 & ~OBJECT_ATTR1_X_MASK) |
					(x & OBJECT_ATTR1_X_MASK);
}

// Set the starting tile of an object to t
static inline void set_object_tile(volatile obj_attrs *object, int t)
{
	object->attr2 = (object->attr2 & ~OBJECT_ATTR2_TILE_MASK) |
					(t & OBJECT_ATTR2_TILE_MASK);
}

// Set object palet in 4bpp
static inline void set_object_palet(volatile obj_attrs *object, int p)
{
	object->attr2 = (object->attr2 & ~OBJECT_ATTR2_PALET_MASK) |
					(p << 12 & OBJECT_ATTR2_PALET_MASK);
}

// Set object shape
static inline void set_object_shape(volatile obj_attrs *object, int sh)
{
	object->attr0 = (object->attr0 & ~OBJECT_ATTR0_SHAPE_MASK) |
					(sh << 14 & OBJECT_ATTR0_SHAPE_MASK);
}

// Set object size
static inline void set_object_size(volatile obj_attrs *object, int si)
{
	object->attr1 = (object->attr1 & ~OBJECT_ATTR1_SIZE_MASK) |
					(si << 14 & OBJECT_ATTR1_SIZE_MASK);
}

// Set mode
static inline void set_object_mode(volatile obj_attrs *object, int mode)
{
	object->attr0 = (object->attr0 & ~OBJECT_ATTR0_MODE_MASK) |
					(mode << 8 & OBJECT_ATTR0_MODE_MASK);
}

// Set color mode
static inline void set_object_bpp(volatile obj_attrs *object, int color)
{
	object->attr0 = (object->attr0 & ~OBJECT_ATTR0_COLOR_MASK) |
					(color << 13 & OBJECT_ATTR0_COLOR_MASK);
}

#endif