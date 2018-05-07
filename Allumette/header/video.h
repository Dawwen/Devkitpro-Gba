/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 20:50:21 by olivier           #+#    #+#             */
/*   Updated: 2018/05/07 19:12:49 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	VIDEO_H
# define VIDEO_H

#include "toolbox.h"
#include "list.h"
#include <stdlib.h>

#define OBJECT_ATTR0_Y_MASK 0x0FF
#define OBJECT_ATTR1_X_MASK 0x1FF

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
//#define bg0_palette_mem		((volatile rgb15 *)(MEM_PAL + 0x200))

// Set the position of an object to specified x and y coordinates
static inline void set_object_position(volatile obj_attrs *object, int x,
										int y)
{
	object->attr0 = (object->attr0 & ~OBJECT_ATTR0_Y_MASK) |
					(y & OBJECT_ATTR0_Y_MASK);
	object->attr1 = (object->attr1 & ~OBJECT_ATTR1_X_MASK) |
					(x & OBJECT_ATTR1_X_MASK);
}


#define PALETTE_SIZE 256

typedef uint16 rgb15;


struct s_sprite
{
	volatile obj_attrs *attribute;
};

typedef struct s_sprite t_sprite;

struct s_scoreboard
{
	t_sprite *first_digit;
	t_sprite *second_digit;
	t_sprite *third_digit;
};

typedef struct s_scoreboard t_scoreboard;

// Form a 16-bit BGR GBA colour from three component values
static inline rgb15 RGB15(int r, int g, int b)
{
	return r | (g << 5) | (b << 10);
}

void setup_sprite_att(volatile obj_attrs *attribute,uint16 start_tile,int palet,int size);
void setup_sprite(t_sprite **sprite,int x,int y, uint16 start_tile, int palet, int size, int *obj_used);
void set_compteur(t_scoreboard *compteur,int value);
void setup_scoreboard(t_scoreboard **score ,int x ,int y ,int *obj_used);
void wait_vblank(void);
void setup_background(void);
void setup_palet(vuint16* palet_memory, const vuint16* palet, int size, int start);
void list_shape(t_list *list, int x, int y);
t_list *list_line(t_list *list, int x, int y, int max);
void setup_game_palet(void);
void setup_VRAM(void);

#endif
