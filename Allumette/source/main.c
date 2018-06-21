/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:45:54 by olivier           #+#    #+#             */
/*   Updated: 2018/06/15 23:48:38 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video.h"
#include "game.h"

int main(int argc, char const *argv[])
{
	REG_DISPLAY = DISP_MODE_0 | DISP_OBJ_MEM | DISP_BG0 | DISP_1D_SPRITE ;

	int obj_used= 0;
	int i=0;
	setup_game_palet();
	setup_VRAM();
	t_game *board;

	board = create_game(32,&obj_used);
	player_play(board,28);
	while (42)
	{
		if (i%30 == 0)
			refresh_game(board);
		wait_vblank();
		i++;
		if (i == 10)
			i = 0;
	}
	return 0;
}
