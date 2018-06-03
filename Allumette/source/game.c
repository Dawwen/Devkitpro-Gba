/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:03:41 by olivier           #+#    #+#             */
/*   Updated: 2018/06/03 14:36:08 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_game *create_game(int allumette, int *obj_used)
{
	t_sprite *test;
	t_list *fioles=NULL;
	int i=0;
	t_game *board= NULL;

	board = (t_game*)malloc(sizeof(t_game));
	while (i < allumette)
	{
		setup_sprite(&test,0,0,12,1,1,obj_used);
		list_push_back(&fioles,test);
		i = i + 1;
	}
	list_shape(fioles,16,16);

	return(board);
}
