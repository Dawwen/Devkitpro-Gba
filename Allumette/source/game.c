/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:03:41 by olivier           #+#    #+#             */
/*   Updated: 2018/08/29 19:41:50 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "bot.h"
#include "input.h"

t_game *create_game(int allumette,int *rules, int *obj_used)
{
	t_sprite *test;

	t_list *fioles=NULL;
	int i=0;
	int* temp;
	t_game *board= NULL;


	board = (t_game*)malloc(sizeof(t_game));
	while (i < allumette)
	{
		if (i%2)
			setup_sprite(&test,0,0,12,2,1,obj_used);
		else
			setup_sprite(&test,0,0,16,0,1,obj_used);
		list_push_back(&fioles,test);
		i = i + 1;
	}
	list_shape(fioles,24,24);

	board->disp = (t_sprite**)malloc(3*sizeof(t_sprite*));
	setup_sprite(&(board->disp[0]),172,28,20,1,1,obj_used);
	setup_sprite(&(board->disp[1]),188,60,20,1,1,obj_used);
	setup_sprite(&(board->disp[2]),204,28,20,1,1,obj_used);

	i = 0;
	temp = (int*)malloc(3*sizeof(int));
	while (i < 3)
	{
		temp[i] = rules[i];
		set_object_tile((board->disp[i])->attribute,20 + 4 * rules[i]);
		i++;
	}

	setup_sprite(&(board->cursor),168,24,92,0,2,obj_used);

	setup_sprite(&(board->player),16,112,108,0,2,obj_used);
	set_object_shape((board->player)->attribute,1);

	board->score = (t_sprite**)malloc(2*sizeof(t_sprite*));
	setup_sprite(&(board->score[0]),16,138,20,1,1,obj_used);
	setup_sprite(&(board->score[1]),32,138,20,1,1,obj_used);

	setup_sprite(&(board->win),64,48,132,0,2,obj_used);
	set_object_shape((board->win)->attribute,1);
	set_object_mode((board->win)->attribute,2);

	board->select = 0;
	board->rules = temp;
	board->objects = fioles;
	board->allumette = allumette;
	board->turn = 1;
	board->ani = -1;
	board->end = 0;
	return(board);
}

void refresh_game(t_game *board)
{
	refresh_score(board);
	if (board->end == 0)
	{
	refresh_player(board);
	refresh_allumette(board);
	check_end(board);

	if (board->ani > -3)
		board->ani--;
	}
}

void check_end(t_game *board)
{
	if (board->ani == -2 && board->allumette < (board->rules)[0] && board->end == 0)
	{
		board->end = -board->turn;
		if (board->end == 1)
			set_object_tile((board->win)->attribute,124);
		else
			set_object_tile((board->win)->attribute,132);
		set_object_mode((board->win)->attribute,0);
	}
}


void refresh_score(t_game *board)
{
	int temp = board->allumette;
	if (board->ani >= 0)
		temp = temp + board->ani;

	set_object_tile((board->score[0])->attribute,20 + 4*(temp/10));
	set_object_tile((board->score[1])->attribute,20 + 4*(temp%10));
}

void refresh_allumette(t_game *board)
{
	t_list *list;
	t_sprite *tmp;
	int i=0, temp=0;

	if (board->ani >= 0)	//Pour evite probleme d'animation au changement de tour
		temp = board->ani;

	list = board->objects;
	while (list)
	{
		tmp = list->data;
		if (i < board->allumette + temp)
			set_object_mode(tmp->attribute,0);
		else
			set_object_mode(tmp->attribute,2);
		list = list->next;
		i++;
	}
}

void refresh_player(t_game *board)
{
	if (board->ani == -2)
	{
		if (board->turn == 1)
			set_object_tile(board->player->attribute,108);
		else
			set_object_tile(board->player->attribute,116);
	}
}

void player_play(t_game *board)
{
	int play = (board->rules)[board->select];
	if (board->turn > 0 && board->ani < -2 && board->allumette >= play )
	{
		board->allumette = board->allumette - play;
		board->turn = - board->turn;
		board->ani = (board->rules)[board->select];
	}
}

void bot_play(t_game *board)
{
	int play;

	if (board->turn < 0 && board->ani < -2)
	{
		play = (board->rules)[bot(board->allumette,board->rules)];
		if (board->allumette >= play)
		{
			board->allumette = board->allumette - play;
			board->turn = - board->turn;
			board->ani = play;
		}
	}
}


void select_num(t_game *board, int select)
{
	board->select = select;
	if (select == 0)
		set_object_position((board->cursor)->attribute,168,24);
	else if (select == 1)
		set_object_position((board->cursor)->attribute,184,56);
	else
		set_object_position((board->cursor)->attribute,200,24);
}

void clear_board(t_game *board)
{
	clear_list(board->objects,clear_sprite);
	clear_sprite(board->cursor);
	clear_sprite(board->player);
	clear_sprite(board->win);

	clear_sprite((board->score)[0]);
	clear_sprite((board->score)[1]);
	free(board->score);

	clear_sprite((board->disp)[0]);
	clear_sprite((board->disp)[1]);
	clear_sprite((board->disp)[2]);
	free(board->disp);

	bot_clear();

	free(board);
}

void game_main(int allumette, int *rules, int *obj_used)
{
	int i=0;
	t_game *board;

	board = create_game(allumette,rules,obj_used);
	while (board->end != 2)
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
			player_play(board);

		if (key_hit(KEY_SELECT) && board->end != 0)
			board->end = 2;

		if (i == 60)
			i = 0;
		if (i%15 == 0)
			refresh_game(board);
		i++;
		wait_vblank();
		key_poll();
	}
	clear_board(board);
}
