/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:23:46 by olivier           #+#    #+#             */
/*   Updated: 2018/08/29 19:41:39 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_H
#define BOT_H

int	rec(int allu, int* rules, int myTurn);
int	bot(int allu, int* rules);
void bot_clear(void);

#endif
