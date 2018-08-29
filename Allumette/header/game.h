/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:16:22 by olivier           #+#    #+#             */
/*   Updated: 2018/08/29 16:35:47 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include "video.h"
#include "list.h"
#include "stdlib.h"

struct s_game
{
	t_list* 	objects;
	t_sprite** 	disp;
	t_sprite** 	score;
	t_sprite*	cursor;
	t_sprite*	player;
	t_sprite*	win;

	int			select;
	int 		allumette;
	int			*rules;
	int 		turn;
	int 		ani;
	int			end;
};
typedef struct s_game t_game;

t_game *create_game(int allumette,int *rules, int *obj_used);
void player_play(t_game *board);
void check_end(t_game *board);
void refresh_score(t_game *board);
void refresh_allumette(t_game *board);
void refresh_player(t_game *board);
void bot_play(t_game *board);
void refresh_game(t_game *board);
void select_num(t_game *board, int select);
void clear_board(t_game *board);

#endif
