#include "toolbox.h"
#include "video.h"

#define REG_KEY_INPUT      (*((volatile uint32 *)(MEM_IO + 0x0130)))

#define KEY_A       0x0001
#define KEY_B       0x0002
#define KEY_SELECT  0x0004
#define KEY_START   0x0008
#define KEY_RIGHT	0x0010
#define KEY_LEFT    0x0020
#define KEY_UP      0x0040
#define KEY_DOWN    0x0080
#define KEY_R       0x0100
#define KEY_L       0x0200
#define KEY_ANY  0x03FF

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
	volatile uint16 *background_tile_mem = (uint16 *)tile_mem[0][1];

	int	i;
	int obj_used;

	t_scoreboard x_coord, y_coord;

	obj_used = 0;
	setup_scoreboard(&x_coord,0,0,&obj_used);
	setup_scoreboard(&y_coord,0,16,&obj_used);

	#include "diamond.data"

	for (i = 0; i < 356 * (sizeof(tile_4bpp) / 2); ++i)
		paddle_tile_mem[i] = perso[i/64][i%64];
	for (i = 0; i < 10 * (sizeof(tile_4bpp) / 2); ++i)
		compteur_tile_mem[i] = num[i/16][i%16];
	for (i = 0; i < 10 * (sizeof(tile_4bpp) / 2); ++i)
		background_tile_mem[i] = num[i/16][i%16];
	//for (i = 0; i < 1 * (sizeof(tile_4bpp) / 2); ++i)
	//	background_tile_mem[i] = diamond[i]

	volatile obj_attrs *paddle_attrs = &oam_mem[6];
	paddle_attrs->attr0 = 0x0000; // 4bpp tiles, TALL shape
	paddle_attrs->attr1 = 0x4000; // 8x32 size when using the TALL shape
	paddle_attrs->attr2 = 11;      // Start at the first tile in tile
											   // block four, use color palette zero

	set_object_position(paddle_attrs, 8, 64);

	// Set the display parameters to enable objects, and use a 1D
	// object->tile mapping

	//ajout
	setup_background();
	setup_game_palet();

	REG_DISPLAY = DISP_MODE_0 | DISP_OBJ_MEM | DISP_BG0 | DISP_1D_SPRITE ;
	//REG_BG0CNT = 0x0083;

	// The main game loop
	uint32 key_states = 0;
	i = 1;
	int x,y;
	int c,d;

	c = 0;
	d = 0;
	x = 8;
	y = 64;

	while (1)
	{
		// Skip past the rest of any current V-Blank, then skip past
		// the V-Draw
		//while(REG_DISPLAY_VCOUNT >= 160);
		//while(REG_DISPLAY_VCOUNT <  160);
		wait_vblank();

		// Get current key states (REG_KEY_INPUT stores the states
		// inverted)
		key_states = ~REG_KEY_INPUT & KEY_ANY;
		//paddle_attrs->attr2 = 11 +(i%4)*4;
		if (key_states & KEY_UP)
		{
			i++;
			if (i == 100)
			{
				i = 0;
			}
		}
		if (key_states & KEY_LEFT)
		{
		d++;
		if (d >= 60)
			{
				d = 0;
				x--;
			}
		}
		if (key_states & KEY_RIGHT)
		{
			c++;
			if (c >= 10)
			{
				c = 0;
				x++;
			}
		}

		set_object_position(paddle_attrs, x, y);
		set_compteur(x_coord, x);
	}
	return 0;
}
