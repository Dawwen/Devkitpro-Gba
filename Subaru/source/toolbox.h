#ifndef TOOLBOX_H
#define TOOLBOX_H


#define MEM_IO   0x04000000
#define MEM_PAL  0x05000000
#define MEM_VRAM 0x06000000
#define MEM_OAM  0x07000000

#define DISP_MODE_0		0x0000
#define DISP_OBJ_MEM	0x1000
#define DISP_1D_SPRITE	0x0040
#define DISP_BG0		0x0100
#define DISP_BG1		0x0200

#define REG_DISPLAY			(*((volatile uint32 *)(MEM_IO)))
#define REG_DISPLAY_VCOUNT	(*((volatile uint32 *)(MEM_IO + 0x0006)))
#define REG_KEY_INPUT		(*((volatile uint32 *)(MEM_IO + 0x0130)))
#define REG_BG0CNT      	(*((volatile uint16 *)(MEM_IO+0x0008)))
#define REG_TM0CNT			(*((volatile uint32 *)(0x04000102)))		//Counter registry
#define REG_TM0D			(*((volatile uint32 *)(0x04000100)))		//Counter data

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef volatile unsigned char  vuint8;
typedef volatile unsigned short vuint16;
typedef volatile unsigned int   vuint32;



#define OBJECT_TILE_MEMORY  ((volatile tile_block *)MEM_VRAM)
#define object_palet_mem ((volatile uint16 *)(MEM_PAL + 0x200))


typedef uint32    tile_4bpp[8];
typedef tile_4bpp tile_block[512];

#endif