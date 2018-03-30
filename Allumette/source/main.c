/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:45:54 by olivier           #+#    #+#             */
/*   Updated: 2018/03/24 11:28:38 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toolbox.h"
#include "video.h"
#include "bot.h"


int main(int argc, char const *argv[])
{
	REG_DISPLAY = DISP_MODE_0 | DISP_OBJ_MEM | DISP_BG0 | DISP_1D_SPRITE ;


	t_scoreboard *bo,*allu;
	t_sprite	*fiole,*test,*blank1,*blank2;
	int obj_used= 0;
	int x = 24;

	setup_sprite(&test,32,32,11,&obj_used);
	setup_sprite(&fiole,48,32,15,&obj_used);
	setup_sprite(&blank1,32,32,19,&obj_used);
	setup_sprite(&blank2,48,32,19,&obj_used);

	setup_scoreboard(&bo,0,0,&obj_used);
	setup_scoreboard(&allu,0,8,&obj_used);


	setup_game_palet();
	setup_VRAM();
	set_compteur(bo, 123);
	set_compteur(allu, 456);

	while (42)
	{
		set_object_position(fiole->attribute,32,32);
		set_object_position(test->attribute,48,32);
		wait_vblank();
		wait_vblank();
		set_object_position(fiole->attribute,48,32);
		set_object_position(test->attribute,32,32);
		wait_vblank();
	}
	return 0;
}
