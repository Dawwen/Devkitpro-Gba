#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 160

#define MEM_IO   0x04000000
#define MEM_PAL  0x05000000
#define MEM_VRAM 0x06000000
#define MEM_OAM  0x07000000

#define DISP_MODE_0		0x0000
#define DISP_OBJ_MEM	0x1000
#define DISP_1D_SPRITE	0x0040
#define DISP_BG0		0x0100

#define REG_DISPLAY			(*((volatile uint32 *)(MEM_IO)))
#define REG_DISPLAY_VCOUNT	(*((volatile uint32 *)(MEM_IO + 0x0006)))
#define REG_KEY_INPUT		(*((volatile uint32 *)(MEM_IO + 0x0130)))
#define REG_BG0CNT      	(*((volatile uint16 *)(MEM_IO+0x0008)))

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

// Clamp 'value' in the range 'min' to 'max' (inclusive)
static inline int clamp(int value, int min, int max)
{
	return (value < min ? min
	                    : (value > max ? max : value));
}
