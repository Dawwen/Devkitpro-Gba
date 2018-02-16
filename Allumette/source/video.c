#include "toolbox.h"
#include "video.h"

//#include "background.h"
//#include "map.h"

volatile unsigned short* bg_palette = (volatile unsigned short*) 0x5000000;
volatile unsigned short* bg0_control = (volatile unsigned short*) 0x4000008;
volatile unsigned short* scanline_counter = (volatile unsigned short*) 0x4000006;

const vuint16 player_palet[15] =
{
		0x7fff,0x0000,
		0x3def,0x6318,
		0x107d,0x11ff,
		0x0f96,0x03df,
		0x26c4,0x001f,
		0x7c00,0x03e0,
		0x0000,0x0000,
		0x0000
};

void setup_digit_att(volatile obj_attrs *digit)
{
	//volatile obj_attrs *compteur_1_attrs = &oam_mem[1];
	digit->attr0 = 0; // 4bpp tiles, SQUARE shape
	digit->attr1 = 0; // 8x8 size when using the SQUARE shape
	digit->attr2 = 1; // Start at the fifth tile in tile block four,
					  // use color palette zero
}
void set_compteur(t_scoreboard compteur,int value)
{
	compteur.first_digit->attr2 = 1 + value/100;
	compteur.second_digit->attr2 = 1 + (value/10) % 10;
	compteur.third_digit->attr2 = 1 + value%10;
}

void setup_scoreboard(t_scoreboard *score ,int x ,int y ,int *obj_used)
{
	score->first_digit = &oam_mem[*obj_used + 0];
	score->second_digit = &oam_mem[*obj_used + 1];
	score->third_digit = &oam_mem[*obj_used + 2];

	setup_digit_att(score->first_digit);
	setup_digit_att(score->second_digit);
	setup_digit_att(score->third_digit);

	set_object_position(score->first_digit, x, y);
	set_object_position(score->second_digit, x + 8, y);
	set_object_position(score->third_digit, x + 16, y);
	*obj_used += 3;
}

/* wait for the screen to be fully drawn so we can do something during vblank */
void wait_vblank( ) {
    /* wait until all 160 lines have been updated */
	while (*scanline_counter >= 160);
    while (*scanline_counter < 160);
}

/* return a pointer to one of the 4 character blocks (0-3) */
volatile unsigned short* char_block(unsigned long block) {
    /* they are each 16K big */
    return (volatile unsigned short*) (0x6000000 + (block * 0x4000));
}

/* return a pointer to one of the 32 screen blocks (0-31) */
volatile unsigned short* screen_block(unsigned long block) {
    /* they are each 2K big */
    return (volatile unsigned short*) (0x6000000 + (block * 0x800));
}

// void setup_background() {
//     /* load the image into char block 0 (16 bits at a time) */
//     volatile unsigned short* dest = char_block(0);
//     unsigned short* image = (unsigned short*) background_data;
//     for (int i = 0; i < ((background_width * background_height) / 2); i++) {
//         dest[i] = image[i];
//     }
//
//     /* set all control the bits in this register */
//     *bg0_control = 0 |    /* priority, 0 is highest, 3 is lowest */
//         (0 << 2)  |       /* the char block the image data is stored in */
//         (0 << 6)  |       /* the mosaic flag */
//         (1 << 7)  |       /* color mode, 0 is 16 colors, 1 is 256 colors */
//         (16 << 8) |       /* the screen block the tile data is stored in */
//         (1 << 13) |       /* wrapping flag */
//         (0 << 14);        /* bg size, 0 is 256x256 */
//
//     /* load the tile data into screen block 16 */
//     dest = screen_block(16);
//     for (int i = 0; i < (map_width * map_height); i++) {
//         dest[i] = map[i];
//     }
// }

void setup_palet(vuint16* palet_memory, const vuint16* palet, int size, int start)
{
    /* load the palette from the image into palette memory*/
    for (int i = start; i < size + start; i++)
    {
        palet_memory[i] = palet[i-start];
    }
}

void setup_game_palet(void)
{
	setup_palet(object_palette_mem,player_palet,15,1);
	//setup_palet(bg_palette,background_palette,256,0);
}
