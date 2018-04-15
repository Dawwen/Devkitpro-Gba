/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:45:54 by olivier           #+#    #+#             */
/*   Updated: 2018/04/15 13:12:40 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video.h"
#include "bot.h"
#include "list.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
	REG_DISPLAY = DISP_MODE_0 | DISP_OBJ_MEM | DISP_BG0 | DISP_1D_SPRITE ;


	t_sprite	*test;
	t_list	*sprites=NULL;
	int obj_used= 0;
	int i = 0;

	setup_game_palet();
	setup_VRAM();

	while (i < 30*16)
	{
		setup_sprite(&test,i+16,0,15,&obj_used);
		list_push_back(&sprites,test);
		i = i + 16;
	}


	while (42)
	{
		list_shape(sprites,16,16);
		wait_vblank();
		list_shape(sprites,128,16);
		wait_vblank();
	}
	return 0;
}
