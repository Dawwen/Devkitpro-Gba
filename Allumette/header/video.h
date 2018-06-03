/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   video.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 20:50:21 by olivier           #+#    #+#             */
/*   Updated: 2018/06/03 12:50:17 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	VIDEO_H
# define VIDEO_H

#include "toolbox.h"
#include "list.h"
#include "object.h"
#include <stdlib.h>


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
