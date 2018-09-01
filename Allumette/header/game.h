/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:16:22 by olivier           #+#    #+#             */
/*   Updated: 2018/09/01 18:12:54 by olivier          ###   ########.fr       */
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
	int			start_obj;
};
typedef struct s_game t_game;

struct s_menu
{
	t_sprite** 	disp;
	t_sprite** 	score;
	t_sprite*	cursor;

	int			select;
	int*		rules;
	int			start_obj;
};
typedef struct s_menu t_menu;

t_game *create_game(int allumette,int *rules, int *obj_used);
void player_play(t_game *board);
void check_end(t_game *board);
void refresh_score(t_game *board);
void set_score_disp(t_sprite **disp, int score);
void refresh_allumette(t_game *board);
void refresh_player(t_game *board);
void bot_play(t_game *board);
void refresh_game(t_game *board);
void select_num_game(t_game *board, int select);
void select_num_menu(t_menu *menu);
void clear_board(t_game *board, int *obj_used);
t_menu* setup_menu_screen(int *allumette, int* rules, int* obj_used);
void menu_main(int *allumette, int* rules, int* obj_used);
void clear_menu(t_menu *menu, int *obj_used);
void set_rules_menu(t_menu *menu);
void order_rules(int *rules);

#endif
