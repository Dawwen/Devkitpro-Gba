/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:16:22 by olivier           #+#    #+#             */
/*   Updated: 2018/08/08 22:48:31 by olivier          ###   ########.fr       */
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
	t_sprite*	cursor;

	int			select;
	int 		allumette;
	int			*rules;
	int 		turn;
	int 		ani;
};
typedef struct s_game t_game;

t_game *create_game(int allumette,int *rules, int *obj_used);
void player_play(t_game *board, int play);
void bot_play(t_game *board);
void refresh_game(t_game *board);
void select_num(t_game *board, int select);
#endif
