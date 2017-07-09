#include "toolbox.h"
#include "object.h"
#include "video.h"

#define REG_KEY_INPUT      (*((volatile uint32 *)(MEM_IO + 0x0130)))

#define KEY_UP   0x0040
#define KEY_DOWN 0x0080
#define KEY_ANY  0x03FF

void set_compteur(volatile obj_attrs **compteur,int value)
{
	compteur[0]->attr2 = 1 + value/10;
	compteur[1]->attr2 = 1 + value%10;
}

int main(void)
{
	// Write the tiles for our sprites into the fourth tile block in VRAM.
	// Four tiles for an 8x32 paddle sprite, and one tile for an 8x8 ball
	// sprite. Using 4bpp, 0x1111 is four pixels of colour index 1, and
	// 0x2222 is four pixels of colour index 2.
	//
	// NOTE: We're using our own memory writing code here to avoid the
	// byte-granular writes that something like 'memset' might make (GBA
	// VRAM doesn't support byte-granular writes).
	volatile uint16 *compteur_tile_mem   = (uint16 *)tile_mem[4][1];
	volatile uint16 *paddle_tile_mem = (uint16 *)tile_mem[4][11];
	int	i;

	#include "diamond.data"
	for (i = 0; i < 4 * (sizeof(tile_4bpp) / 2); ++i)
		paddle_tile_mem[i] = 0x2222; // 0b_0002_0001_0002_0001
	for (i = 0; i < 10 * (sizeof(tile_4bpp) / 2); ++i)
		compteur_tile_mem[i] = num[i/16][i%16];

	// Write the colour palette for our sprites into the first palette of
	// 16 colours in colour palette memory (this palette has index 0)
	object_palette_mem[1] = RGB15(0x00, 0x00, 0x1F); // Blue
	object_palette_mem[3] = RGB15(0x1F, 0x00, 0x00); // Red
	object_palette_mem[2] = RGB15(0x1F, 0x1F, 0x1F); // White
	object_palette_mem[4] = RGB15(0x01, 0x01, 0x01); // Black
	// Create our sprites by writing their object attributes into OAM
	// memory
	volatile obj_attrs *paddle_attrs = &oam_mem[0];
	paddle_attrs->attr0 = 0x8000; // 4bpp tiles, TALL shape
	paddle_attrs->attr1 = 0x4000; // 8x32 size when using the TALL shape
	paddle_attrs->attr2 = 11;      // Start at the first tile in tile
	                              // block four, use color palette zero
	volatile obj_attrs *compteur_1_attrs = &oam_mem[1];
	compteur_1_attrs->attr0 = 0; // 4bpp tiles, SQUARE shape
	compteur_1_attrs->attr1 = 0; // 8x8 size when using the SQUARE shape
	compteur_1_attrs->attr2 = 1; // Start at the fifth tile in tile block four,
	                       // use color palette zero

	volatile obj_attrs *compteur_2_attrs = &oam_mem[2];
   	compteur_2_attrs->attr0 = 0; // 4bpp tiles, SQUARE shape
   	compteur_2_attrs->attr1 = 0; // 8x8 size when using the SQUARE shape
   	compteur_2_attrs->attr2 = 1; // Start at the fifth tile in tile block four,
					   	                       // use color palette zero

	set_object_position(paddle_attrs, 64, 64);
	set_object_position(compteur_1_attrs, 0, 0);
	set_object_position(compteur_2_attrs, 8, 0);
	volatile obj_attrs *compteur[2] = {compteur_1_attrs,compteur_2_attrs};
	// Set the display parameters to enable objects, and use a 1D
	// object->tile mapping
	REG_DISPLAY = 0x1000 | 0x0040;

	// The main game loop
	uint32 key_states = 0;
	i = 1;
	while (1)
	{
		// Skip past the rest of any current V-Blank, then skip past
		// the V-Draw
		while(REG_DISPLAY_VCOUNT >= 160);
		while(REG_DISPLAY_VCOUNT <  160);

		// Get current key states (REG_KEY_INPUT stores the states
		// inverted)
		key_states = ~REG_KEY_INPUT & KEY_ANY;

		if (key_states & KEY_UP)
		{
			i++;
			if (i == 100)
			{
				i = 1;
			}
		}
		set_compteur(compteur, i);
	}
	return 0;
}
