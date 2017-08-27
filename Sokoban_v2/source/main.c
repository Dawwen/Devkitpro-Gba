#include "toolbox.h"
#include "video.h"

#define REG_KEY_INPUT      (*((volatile uint32 *)(MEM_IO + 0x0130)))

#define KEY_UP   0x0040
#define KEY_DOWN 0x0080
#define KEY_ANY  0x03FF

void set_compteur(t_scoreboard compteur,int value)
{
	compteur.first_digit->attr2 = 1 + value/10;
	compteur.second_digit->attr2 = 1 + value%10;
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
	volatile uint16 *background_tile_mem = (uint16 *)tile_mem[0][1];

	int	i;

	t_scoreboard score;
	score.first_digit = &oam_mem[0];
	score.second_digit = &oam_mem[1];

	#include "diamond.data"

	for (i = 0; i < 356 * (sizeof(tile_4bpp) / 2); ++i)
		paddle_tile_mem[i] = perso[i/64][i%64];
	for (i = 0; i < 10 * (sizeof(tile_4bpp) / 2); ++i)
		compteur_tile_mem[i] = num[i/16][i%16];
	for (i = 0; i < 10 * (sizeof(tile_4bpp) / 2); ++i)
		background_tile_mem[i] = num[i/16][i%16];
	//for (i = 0; i < 1 * (sizeof(tile_4bpp) / 2); ++i)
	//	background_tile_mem[i] = diamond[i]

	// Create our sprites by writing their object attributes into OAM
	// memory

	//volatile obj_attrs *compteur_1_attrs = &oam_mem[1];
	score.first_digit->attr0 = 0; // 4bpp tiles, SQUARE shape
	score.first_digit->attr1 = 0; // 8x8 size when using the SQUARE shape
	score.first_digit->attr2 = 1; // Start at the fifth tile in tile block four,
	                       // use color palette zero

	//volatile obj_attrs *compteur_2_attrs = &oam_mem[2];
   	score.second_digit->attr0 = 0; // 4bpp tiles, SQUARE shape
   	score.second_digit->attr1 = 0; // 8x8 size when using the SQUARE shape
   	score.second_digit->attr2 = 1; // Start at the fifth tile in tile block four,
					   	                       // use color palette zero

	volatile obj_attrs *paddle_attrs = &oam_mem[2];
	paddle_attrs->attr0 = 0x0000; // 4bpp tiles, TALL shape
	paddle_attrs->attr1 = 0x4000; // 8x32 size when using the TALL shape
	paddle_attrs->attr2 = 11;      // Start at the first tile in tile
											   // block four, use color palette zero

	set_object_position(paddle_attrs, 64, 32);
	set_object_position(score.first_digit, 48, 32);
	set_object_position(score.second_digit, 56, 32);

	// Set the display parameters to enable objects, and use a 1D
	// object->tile mapping

	set_compteur(score, 2);
	//ajout
	setup_background();
	setup_game_palet();

	REG_DISPLAY = DISP_MODE_0 | DISP_OBJ_MEM | DISP_BG0 | DISP_1D_SPRITE ;
	//REG_BG0CNT = 0x0083;

	// The main game loop
	uint32 key_states = 0;
	i = 1;

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
		paddle_attrs->attr2 = 11 +(i%4)*4;
		if (key_states & KEY_UP)
		{
			i++;
			if (i == 100)
			{
				i = 0;
			}
		}
		//if (key_states & KEY_DOWN)

		set_compteur(score, i);
	}
	return 0;
}
