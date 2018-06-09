/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 13:16:22 by olivier           #+#    #+#             */
/*   Updated: 2018/06/04 13:49:06 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include "video.h"
#include "list.h"
#include "stdlib.h"

struct s_game
{
	t_list *objects;
	int allumette;
	int turn;
	int ani;
};
typedef struct s_game t_game;

t_game *create_game(int allumette, int *obj_used);
void player_play(t_game *board, int play);
void bot_play(t_game *board);
void refresh_game(t_game *board);
#endif
