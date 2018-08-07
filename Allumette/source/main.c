/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:45:54 by olivier           #+#    #+#             */
/*   Updated: 2018/08/07 16:04:20 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video.h"
#include "game.h"

int main(int argc, char const *argv[])
{
	REG_DISPLAY = DISP_MODE_0 | DISP_OBJ_MEM | DISP_BG0 | DISP_1D_SPRITE ;

	//t_sprite *sp;
	int obj_used= 0;
	int i=0;
	t_game *board;
	int rules[3]={1,2,3};

	setup_game_palet();
	setup_VRAM();
	setup_background();


	board = create_game(6,rules,&obj_used);

	/*setup_sprite(&sp,172,28,24,1,1,&obj_used);	//Le nombre 1
	setup_sprite(&sp,204,28,32,1,1,&obj_used);	//Le nombre 2
	setup_sprite(&sp,188,60,28,1,1,&obj_used);	//Le nombre 3
	*/

	player_play(board,5);
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
