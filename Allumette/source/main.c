/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:45:54 by olivier           #+#    #+#             */
/*   Updated: 2018/04/01 11:13:22 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toolbox.h"
#include "video.h"
#include "bot.h"
#include "list.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
	REG_DISPLAY = DISP_MODE_0 | DISP_OBJ_MEM | DISP_BG0 | DISP_1D_SPRITE ;


	t_scoreboard *bo,*allu;
	t_sprite	*fiole,*test,*blank1,*blank2;
	t_list	*sprites=NULL;
	int obj_used= 0;
	int i = 0;

	setup_game_palet();
	setup_VRAM();

	while (i < 15*16)
	{
		setup_sprite(&test,i,0,15,&obj_used);
		list_push_back(&sprites,test);
		i = i + 16;
	}


	i = 0;
	while (sprites)
	{
		fiole = sprites->data;
		set_object_position(fiole->attribute,i,16);
		sprites = sprites->next;
		i = i + 16;
	}

	/*
	set_compteur(bo, 123);
	set_compteur(allu, 456);
	*/
	while (42)
	{
		wait_vblank();
	}
	return 0;
}
