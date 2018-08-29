/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dico.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olivier <olivier@doussaud.org>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 19:47:57 by olivier           #+#    #+#             */
/*   Updated: 2018/08/29 19:40:40 by olivier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "dico.h"

dico* create_node(void* data,int lenght)
{
	dico *list;
	list = NULL;
	list = malloc(sizeof(dico));
	if (list)
	{
		list->lenght = lenght;
		list->data = data;
		list->next = NULL;
	}
	return list;
}

void push_back(dico **begin_list, void *data, int lenght)
{
	dico	*list;

	list = *begin_list;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = create_node(data,lenght);
	}
	else
		*begin_list = create_node(data,lenght);
}

void push_front(dico **begin_list, void *data, int lenght)
{
	dico	*list;

	list = create_node(data,lenght);
	if (*begin_list)
		list->next = *begin_list;
	*begin_list = list;
}

int get_data(dico **begin, int global_index)
{
	dico *list = *begin;
	int index = global_index;

	while (list != NULL && index - list->lenght >= 0)
	{
		index = index - list->lenght;
		list = list->next;
	}

	if (list == NULL || index - list->lenght >= 0)
	{
		add_empty_node(begin,index+1);
		return get_data(begin,global_index);
	}
	int *data = list->data;
	return data[index];
}

void set_data(dico **begin, int global_index, int value)
{
	dico *list = *begin;
	int index = global_index;

	while (list != NULL && index - list->lenght >= 0)
	{
		index = index - list->lenght;
		list = list->next;
	}

	if (list == NULL || index - list->lenght >= 0)
	{
		add_empty_node(begin,index+1);
		set_data(begin,global_index,value);
		return ;
	}
	int *data = list->data;
	data[index] = value;
}

void add_empty_node(dico** list, int lenght)
{
	int i;
	int *data;
	data = malloc((lenght)*sizeof(int));
	i = 0;
	while (i < lenght)
	{
		data[i] = 0;
		i++;
	}
	push_back(list,data,lenght);
}

void clear_dico(dico *lst)
{
	dico *tmp;
	while (lst)
	{
		tmp = lst->next;
		free(lst->data);
		free(lst);
		lst = tmp;
	}
}
