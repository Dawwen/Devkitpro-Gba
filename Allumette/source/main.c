/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:45:54 by olivier           #+#    #+#             */
/*   Updated: 2018/08/25 19:52:50 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video.h"
#include "game.h"
#include "input.h"

int main(int argc, char const *argv[])
{
	REG_DISPLAY = DISP_MODE_0 | DISP_OBJ_MEM | DISP_BG0 | DISP_1D_SPRITE ;

	int obj_used= 0;
	int i=0;
	t_game *board;
	int rules[3]={3,5,7};

	setup_game_palet();
	setup_VRAM();
	setup_background();


	board = create_game(15,rules,&obj_used);

	while (42)
	{
		bot_play(board);

		if (key_hit(KEY_RIGHT) && board->select != 2)
		{
			board->select = board->select + 1;
			select_num(board,board->select);
		}
		if (key_hit(KEY_LEFT) && board->select != 0)
		{
			board->select = board->select - 1;
			select_num(board,board->select);
		}
		if (key_hit(KEY_A))
		{
			player_play(board);
		}

		if (i == 60)
			i = 0;
		if (i%30 == 0)
			refresh_game(board);
		i++;
		wait_vblank();
		key_poll();
	}
	return 0;
}
