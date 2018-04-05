/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 11:40:10 by olivier           #+#    #+#             */
/*   Updated: 2018/04/01 10:55:39 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include <stdlib.h>

t_list	*create_elem(void *data)
{
	t_list	*list;

	list = NULL;
	list = malloc(sizeof(t_list));
	if (list)
	{
		list->data = data;
		list->next = NULL;
	}
	return (list);
}

void	list_push_back(t_list **begin_list, void *data)
{
	t_list	*list;

	list = *begin_list;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = create_elem(data);
	}
	else
		*begin_list = create_elem(data);
}

void	list_push_front(t_list **begin_list, void *data)
{
	t_list	*list;

	if (*begin_list)
	{
		list = create_elem(data);
		list->next = *begin_list;
		*begin_list = list;
	}
	else
		*begin_list = create_elem(data);
}

int	list_size(t_list *begin_list)
{
	t_list	*list;
	int		i;

	i = 0;
	list = begin_list;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}
