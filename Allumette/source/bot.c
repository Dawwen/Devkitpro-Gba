/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:23:49 by olivier           #+#    #+#             */
/*   Updated: 2018/03/21 13:32:12 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dico.h"
#include <stdlib.h>

#define WIN 1
#define LOST -1

dico *result=NULL;

int	rec(int allu, int myTurn)
{
	int i = 1;
	int check = get_data(&result,allu);
	int value;

	if (allu <= 0)
		return((myTurn) ? LOST : WIN);

	if (check != 0)
	{
		if (myTurn)
			return(check);
		return(-check);
	}

	if (myTurn)
	{
		while (i < 4)
		{
			value =rec(allu-i,!myTurn);
			set_data(&result,allu-i,-value);
			if (value == WIN)
				return(WIN);
			i++;
		}
		return(LOST);
	}
	else
	{
		while (i < 4)
		{
			value =rec(allu-i,!myTurn);
			set_data(&result,allu-i,value);
			if (value == LOST)
				return(LOST);
			i++;
		}
		return(WIN);
	}
}

int	bot(int allu)
{
	int i = 1;
	while (i < 4)
	{
		if (rec(allu - i, 0) == 1)
			return(i);
		i += 1;
	}
	return(1);
}
