/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:45:54 by olivier           #+#    #+#             */
/*   Updated: 2018/06/01 22:59:59 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "video.h"
#include "bot.h"
#include "list.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
	REG_DISPLAY = DISP_MODE_0 | DISP_OBJ_MEM | DISP_BG0 | DISP_1D_SPRITE ;


	t_sprite *test;
	t_list *fioles=NULL;
	t_list *temp=NULL;
	int obj_used= 0;
	int i = 0, n = 26, c = 26;

	setup_game_palet();
	setup_VRAM();

	while (i < n)
	{
		setup_sprite(&test,i*16+16,0,20,-1,2,&obj_used);
		list_push_back(&fioles,test);
		i = i + 1;
	}

	list_shape(fioles,16,16);

	while (42)
	{
		i = 0;
		while (i < 60)
		{
			wait_vblank();
			i++;
		}
		test = fioles->data;
		set_object_mode(test->attribute, 10);
	}
	return 0;
}
