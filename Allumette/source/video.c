/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 20:49:19 by olivier           #+#    #+#             */
/*   Updated: 2018/03/24 11:35:45 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toolbox.h"
#include "video.h"
#include <stdlib.h>

//#include "background.h"
//#include "map.h"
#include "ressource/num.data"
#include "ressource/fiole_blue.data"
#include "ressource/fiole_red.data"
#include "ressource/blank.data"

volatile unsigned short* bg_palette = (volatile unsigned short*) 0x5000000;
volatile unsigned short* bg0_control = (volatile unsigned short*) 0x4000008;
volatile unsigned short* scanline_counter = (volatile unsigned short*) 0x4000006;

const vuint16 player_palet[15] =
{
		0x0000,0x463f,
		0x109f,0x085b,
		0x0430,0x042c,
		0x7fff,0x7ef1,
		0x7e04,0x6da2,
		0x4101,0x30c1,
		0x0000,0x0000,
		0x0000
};


void setup_VRAM(void)
{
	int i;
	volatile uint16 *start_tile_mem   = (uint16 *)tile_mem[4][1];

	for (i = 0; i < 10 * (sizeof(tile_4bpp) / 2); ++i)	//Numero, 10 = nb tiles
	{
		*start_tile_mem = num[i/16][i%16];
		start_tile_mem++;
	}
	for (i = 0; i < 4 * (sizeof(tile_4bpp) / 2); ++i)	//Fiole
	{
		*start_tile_mem = fiole_blue[i/16][i%16];
		start_tile_mem++;
	}
	for (i = 0; i < 4 * (sizeof(tile_4bpp) / 2); ++i)	//Fiole
	{
		*start_tile_mem = fiole_red[i/16][i%16];
		start_tile_mem++;
	}
	for (i = 0; i < 4 * (sizeof(tile_4bpp) / 2); ++i)	//Fiole
	{
		*start_tile_mem = blank[i/16][i%16];
		start_tile_mem++;
	}
}

void setup_digit_att(volatile obj_attrs *digit)
{
	//volatile obj_attrs *compteur_1_attrs = &oam_mem[1];
	digit->attr0 = 0; // 4bpp tiles, SQUARE shape
	digit->attr1 = 0; // 8x8 size when using the SQUARE shape
	digit->attr2 = 1; // Start at the fifth tile in tile block four,
	// use color palette zero
}

void setup_sprite_att(volatile obj_attrs *attribute,uint16 start_tile)
{
	//volatile obj_attrs *compteur_1_attrs = &oam_mem[1];
	attribute->attr0 = 0; // 4bpp tiles, SQUARE shape
	attribute->attr1 = 0x4000; // 8x8 size when using the SQUARE shape
	attribute->attr2 = start_tile; // Start at the fifth tile in tile block four,
	// use color palette zero
}

void set_compteur(t_scoreboard *compteur,int value)
{
	compteur->first_digit->attr2 = 1 + value/100;
	compteur->second_digit->attr2 = 1 + (value/10) % 10;
	compteur->third_digit->attr2 = 1 + value%10;
}


void setup_sprite(t_sprite **sprite,int x,int y, uint16 start_tile, int *obj_used)
{
	*sprite = (t_sprite*)malloc(sizeof(t_sprite));
	(*sprite)->attribute = &oam_mem[*obj_used + 0];

	setup_sprite_att((*sprite)->attribute,start_tile);
	set_object_position((*sprite)->attribute, x, y);
	*obj_used += 1;
}
void setup_scoreboard(t_scoreboard **score ,int x ,int y ,int *obj_used)
{
	*score = (t_scoreboard*)malloc(sizeof(t_scoreboard));

	(*score)->first_digit = &oam_mem[*obj_used + 0];
	(*score)->second_digit = &oam_mem[*obj_used + 1];
	(*score)->third_digit = &oam_mem[*obj_used + 2];

	setup_digit_att((*score)->first_digit);
	setup_digit_att((*score)->second_digit);
	setup_digit_att((*score)->third_digit);

	set_object_position((*score)->first_digit, x, y);
	set_object_position((*score)->second_digit, x + 8, y);
	set_object_position((*score)->third_digit, x + 16, y);
	*obj_used += 3;
}

/* wait for the screen to be fully drawn so we can do something during vblank */
void wait_vblank( )
{
	/* wait until all 160 lines have been updated */
	while (*scanline_counter >= 160);
	while (*scanline_counter < 160);
}

/* return a pointer to one of the 4 character blocks (0-3) */
volatile unsigned short* char_block(unsigned long block)
{
	/* they are each 16K big */
	return (volatile unsigned short*) (0x6000000 + (block * 0x4000));
}

/* return a pointer to one of the 32 screen blocks (0-31) */
volatile unsigned short* screen_block(unsigned long block)
{
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
