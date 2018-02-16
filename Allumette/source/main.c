/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:45:54 by olivier           #+#    #+#             */
/*   Updated: 2018/02/14 21:01:40 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toolbox.h"
#include "video.h"
#include "bot.h"

#include "diamond.data"

int main(int argc, char const *argv[])
{
	REG_DISPLAY = DISP_MODE_0 | DISP_OBJ_MEM | DISP_BG0 | DISP_1D_SPRITE ;


	t_scoreboard score;
	int obj_used= 0;
	int i;
	volatile uint16 *compteur_tile_mem   = (uint16 *)tile_mem[4][1];
	volatile uint16 *perso_tile_mem   = (uint16 *)tile_mem[4][11];


	setup_scoreboard(&score,0,0,&obj_used);
	setup_game_palet();

	for (i = 0; i < 10 * (sizeof(tile_4bpp) / 2); ++i)
		compteur_tile_mem[i] = num[i/16][i%16];

	while (42)
	{
		set_compteur(score, bot(43));
		wait_vblank();
	}
	return 0;
}
