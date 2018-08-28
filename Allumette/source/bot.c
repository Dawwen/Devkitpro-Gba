/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 13:23:49 by olivier           #+#    #+#             */
/*   Updated: 2018/08/28 12:44:18 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dico.h"
#include <stdlib.h>

#define WIN 1
#define LOST -1

dico *result=NULL;

int	rec(int allu,int* rules, int myTurn)
{
	int i = 0;
	int check = get_data(&result,allu);
	int value;

	if (allu < rules[0])
		return((myTurn) ? LOST : WIN);

	if (check != 0)
	{
		if (myTurn)
			return(check);
		return(-check);
	}

	if (myTurn)
	{
		while (i < 3)
		{
			value =rec(allu-rules[i],rules,!myTurn);
			set_data(&result,allu-rules[i],-value);
			if (value == WIN)
				return(WIN);
			i++;
		}
		return(LOST);
	}
	else
	{
		while (i < 3)
		{
			value =rec(allu-rules[i],rules,!myTurn);
			set_data(&result,allu-rules[i],value);
			if (value == LOST)
				return(LOST);
			i++;
		}
		return(WIN);
	}
}

int	bot(int allu,int* rules)
{
	int i = 0;
	while (i < 3)
	{
		if (rec(allu - rules[i], rules, 0) == 1)
			return(i);
		i += 1;
	}
	return(0);
}
