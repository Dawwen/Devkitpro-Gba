/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:03:41 by olivier           #+#    #+#             */
/*   Updated: 2018/06/04 14:32:07 by olivier          ###   ########.fr       */
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
		setup_sprite(&test,0,0,2,0,2,obj_used);
		list_push_back(&fioles,test);
		i = i + 1;
	}
	list_shape(fioles,16,16);

	board->objects = fioles;
	board->allumette = allumette;
	board->turn = 1;
	return(board);
}

void refresh_game(t_game *board)
{
	t_list *list;
	t_sprite *tmp;

	int i=0;

	list = board->objects;
	while (list)
	{
		tmp = list->data;
		if (i < board->allumette)
			set_object_mode(tmp->attribute,0);
		else
			set_object_mode(tmp->attribute,10);
		list = list->next;
		i++;
	}
}

void player_play(t_game *board, int play)
{
	if (board->turn > 0)
	{
		board->allumette = board->allumette - play;
		board->turn = - board->turn;
		refresh_game(board);
	}
}
