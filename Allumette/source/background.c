/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 20:18:51 by olivier           #+#    #+#             */
/*   Updated: 2018/06/21 21:57:01 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "background.h"

/* include the image we are using */
#include "ressource/background/background.h"

/* include the tile map we are using */
#include "ressource/background/map.h"

volatile unsigned short* bg0_control = (volatile unsigned short*) 0x4000008;
volatile unsigned short* bg1_control = (volatile unsigned short*) 0x400000a;
volatile unsigned short* bg2_control = (volatile unsigned short*) 0x400000c;
volatile unsigned short* bg3_control = (volatile unsigned short*) 0x400000e;

/* scrolling registers for backgrounds */
volatile short* bg0_x_scroll = (volatile short*) 0x4000010;
volatile short* bg0_y_scroll = (volatile short*) 0x4000012;
volatile short* bg1_x_scroll = (volatile short*) 0x4000014;
volatile short* bg1_y_scroll = (volatile short*) 0x4000016;
volatile short* bg2_x_scroll = (volatile short*) 0x4000018;
volatile short* bg2_y_scroll = (volatile short*) 0x400001a;
volatile short* bg3_x_scroll = (volatile short*) 0x400001c;
volatile short* bg3_y_scroll = (volatile short*) 0x400001e;

/* the address of the color palette */
volatile unsigned short* bg_palette = (volatile unsigned short*) 0x5000000;

/* function to setup background 0 for this program */
void setup_background() {

	/* load the palette from the image into palette memory*/
	for (int i = 0; i < PALETTE_SIZE; i++) {
		bg_palette[i] = background_palette[i];
	}

	/* load the image into char block 0 (16 bits at a time) */
	volatile unsigned short* dest = char_block(3);
	unsigned short* image = (unsigned short*) background_data;
	for (int i = 0; i < ((background_width * background_height) / 2); i++) {
		dest[i] = image[i];	//La tilesheet
	}

	/* set all control the bits in this register */
	*bg0_control = 0 |	/* priority, 0 is highest, 3 is lowest */
		(3 << 2)  |		/* the char block the image data is stored in */
		(0 << 6)  |		/* the mosaic flag */
		(1 << 7)  |		/* color mode, 0 is 16 colors, 1 is 256 colors */
		(0 << 8) |		/* the screen block the tile data is stored in */
		(1 << 13) |		/* wrapping flag */
		(0 << 14);		/* bg size, 0 is 256x256 */

	/* load the tile data into screen block 16 */
	dest = screen_block(0);	//La map
	for (int i = 0; i < (map_width * map_height); i++) {
		dest[i] = map[i];
	}
}/* the control registers for the four tile layers */
